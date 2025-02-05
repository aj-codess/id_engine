#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <memory>

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <url_dep.h>
#include <session_manager.h>
#include <token_dep.h>
#include <timer.h>

using namespace std;

class auth_middleware{
    public:
    auth_middleware()=default;
    bool entry(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res);

    private:
    url_dep url;
    server_session session;
    token_dep token_handler;
    timer pulse;
};



bool auth_middleware::entry(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res){

    auto auth_header=req[boost::beast::http::field::authorization];

    if(this->url.sniff(req,"beryl")==true && !auth_header.empty()){

        std::string auth_value(auth_header.data(), auth_header.size());

        const std::string prefix = "Bearer ";

        if (auth_value.rfind(prefix, 0) == 0) {

            std::string token = auth_value.substr(prefix.size());

            std::string id;

            bool token_isValid=this->token_handler.token_validity(token,[&](std::string server_id){

                id=server_id;

            });

            if(token_isValid==true){

                req.set("id",id);

                return true;

            };
            
        };

    } else if(auth_header.empty()){

        std::string server_name = std::string(req[boost::beast::http::field::user_agent]);

        time_t time;

        std::string new_id=this->pulse.gen_id([&](time_t gen_time){

            time=gen_time;

        });

        const std::string token=this->token_handler.token_signer(new_id);

        if(token.length()>0){

            this->session.create_session(new_id,server_name,time);

        };

        res.set(boost::beast::http::field::authorization,"Bearer "+token);

        return true;

    } else{

        return false;

    };

};