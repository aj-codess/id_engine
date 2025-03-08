#pragma once

#include <iostream>
#include <string>

#include <logic.h>
#include <jsonScript.h>

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/url.hpp>
#include <nlohmann/json.hpp>

using namespace std;

class getId_controller{
    private:
    getId_controller()=default;
    id_schema engine;
    jsonScript json;
    void url_2_body_gen(boost::beast::http::request<boost::beast::http::string_body>& req,std::string& body_2_send);
    std::string cast(boost::urls::params_view::iterator value_2_cast);

    public:
    void get_indi_id(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res);
};



//make a json to string cast
std::string getId_controller::cast(boost::urls::params_view::iterator value_2_cast) {
    // Access the value from the iterator by dereferencing it first
    const auto& param = *value_2_cast;  // Dereference to get the key-value pair

    return std::string(param.value.data(), param.value.size());  // Convert the value to std::string

};


void getId_controller::url_2_body_gen(boost::beast::http::request<boost::beast::http::string_body>& req,std::string& payload_){

    boost::urls::url_view url(req.target());

    auto option=url.params().find("option");

    auto user_id_f_ugc=url.params().find("user_id");

    auto space_id_f_ugc=url.params().find("space_id");

    if(option != url.params().end() && (user_id_f_ugc !=url.params().end() || space_id_f_ugc!=url.params().end())){

        payload_=this->engine.generate_id(cast(option),cast(user_id_f_ugc),cast(space_id_f_ugc));

    };

};



void getId_controller::get_indi_id(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res){
    
    std::string payload;

    this->url_2_body_gen(req,payload);

    res.body()=(json.id_2_json(payload)).dump();

    res.result(boost::beast::http::status::ok);
};