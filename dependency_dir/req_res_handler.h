#pragma once

#include <iostream>
#include <string>

#include <memory>

#include <connection.h>
#include <auth.h>


#include <getter_routes.h>
#include <deleter_routes.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>


class req_res_handler{
    public:
        req_res_handler()=default;
        void request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res);


    private:
        get_router getter;
        delete_routes delete_;
        auth_middleware middle_verify;
        url_dep url;

    };




void req_res_handler::request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res){

    res.version(req.version());
    
    res.set(boost::beast::http::field::server, "Beryl ID Server");

    res.set(boost::beast::http::field::content_type, "application/json");

    if(!middle_verify.entry(req,res)){
        return;
    };

    switch(req.method()) {

        case boost::beast::http::verb::get:

            this->getter.route(req,res);
            
            break;

        case boost::beast::http::verb::delete_:

            this->delete_.route(req,res);

            break;

        default:
            res.result(boost::beast::http::status::bad_request);
            
            res.body() = "Invalid request method.";
            
            break;
    };

    res.keep_alive(req.keep_alive());

    res.prepare_payload();  // Prepare the payload before sending the response

};