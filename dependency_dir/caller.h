#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <logic.h>
#include <req_res_handler.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/beast.hpp>
#include <boost/url.hpp>
#include <nlohmann/json.hpp>


class caller{
    private:
    id_schema generator;
    std::string cast(boost::urls::params_view::iterator value_2_cast);
    std::string string_cast(nlohmann::json value);

    public:
    void url_2_body_gen(boost::beast::http::request<boost::beast::http::string_body>& req,std::string& body_2_send);
    persist get_persistent();
    bool global_del(boost::beast::http::request<boost::beast::http::string_body>& req);
};



void caller::url_2_body_gen(boost::beast::http::request<boost::beast::http::string_body>& req,std::string& body_2_send){

    boost::urls::url_view url(req.target());

    auto option=url.params().find("option");

    auto user_id_f_ugc=url.params().find("user_id");

    auto space_id_f_ugc=url.params().find("space_id");

    if(option != url.params().end() && (user_id_f_ugc !=url.params().end() || space_id_f_ugc!=url.params().end())){

        body_2_send=this->generator.generate_id(cast(option),cast(user_id_f_ugc),cast(space_id_f_ugc));

    };

};


//make a json to string cast
std::string caller::cast(boost::urls::params_view::iterator value_2_cast) {
    // Access the value from the iterator by dereferencing it first
    const auto& param = *value_2_cast;  // Dereference to get the key-value pair

    return std::string(param.value.data(), param.value.size());  // Convert the value to std::string

};



persist caller::get_persistent(){

    return this->generator.get_persistent();

};



bool caller::global_del(boost::beast::http::request<boost::beast::http::string_body>& req){
    bool isDeleted;

    nlohmann::json json_body=nlohmann::json::parse(req.body());

    auto user_id=json_body.find("user_id");

    auto user_pos=json_body.find("user_pos");

    auto space_id=json_body.find("space_id");

    auto space_pos=json_body.find("space_pos");

    auto ugc_id=json_body.find("ugc_id");

    if( user_id != json_body.end() && user_pos != json_body.end()){
        
        isDeleted=this->generator.del_user(string_cast(json_body["user_id"]),string_cast(json_body["user_pos"]));

    } else if(space_id != json_body.end() && space_pos != json_body.end()){

        isDeleted=this->generator.del_space(string_cast(json_body["space_id"]),string_cast(json_body["space_pos"]));

    } else if(user_id != json_body.end() && ugc_id != json_body.end()){

        isDeleted=this->generator.del_ugc(string_cast(json_body["user_id"]),string_cast(json_body["ugc_id"]));

    };

    return isDeleted;

};



std::string caller::string_cast(nlohmann::json value){
    std::string cast;

    try{

        cast=value.get<std::string>();

    } catch(const std::exception& e){

        cout<<"unable to cast data - "<<e.what()<<endl;

    };

    return cast;
};