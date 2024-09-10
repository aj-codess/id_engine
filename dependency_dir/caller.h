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


class caller{
    private:
    id_schema generator;
    std::string cast(boost::urls::params_view::iterator value_2_cast);

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

    }

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

    boost::urls::url_view url(req.target());

    auto user_id=url.params().find("user_id");

    auto user_pos=url.params().find("user_pos");

    auto space_id=url.params().find("space_id");

    auto space_pos=url.params().find("space_pos");

    auto ugc_id=url.params().find("ugc_id");

    if( user_id != url.params().end() && user_pos != url.params().end()){

        isDeleted=this->generator.del_user(cast(user_id),cast(user_pos));

    } else if(space_id != url.params().end() && space_pos != url.params().end()){

        isDeleted=this->generator.del_space(cast(space_id),cast(space_pos));

    } else if(user_id != url.params().end() && ugc_id != url.params().end()){

        isDeleted=this->generator.del_ugc(cast(user_id),cast(ugc_id));

    };

    return isDeleted;

};