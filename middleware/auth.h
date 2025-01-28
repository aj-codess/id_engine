#pragma once

#include <iostream>
#include <string>
#include <functional>

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <url_dep.h>
#include <global_dcl.h>

using namespace std;

class auth_middleware{
    public:
    auth_middleware()=default;
    bool entry(boost::beast::http::request<boost::beast::http::string_body>& req);

    private:
    url_dep url;
    server_session session;
};



bool auth_middleware::entry(boost::beast::http::request<boost::beast::http::string_body>& req){

    auto auth_header=req[boost::beast::http::field::authorization];

    if(this->url.sniff(req,"beryl")==true && !auth_header.empty()){

        std::string auth_value(auth_header.data(), auth_header.size());

        const std::string prefix = "Bearer ";

        if (auth_value.rfind(prefix, 0) == 0) {

            std::string token = auth_value.substr(prefix.size());

            bool token_isValid=
            
        };

    } else if(auth_header.empty()){

        //get a new id and make it a token and set as a header

    } else{

        return false;

    };

};