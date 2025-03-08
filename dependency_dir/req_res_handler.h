#pragma once

#include <iostream>
#include <string>

#include <memory>

#include <caller.h>
#include <connection.h>
#include <jsonScript.h>
#include <auth.h>
#include <url_dep.h>

#include <getter_routes.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/beast.hpp>
#include <boost/url.hpp>
#include <nlohmann/json.hpp>


class req_res_handler{
    private:
        get_router getter;
        auth_middleware middle_verify;

    public:
        void request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res);
};




void req_res_handler::request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res){

    std::string data_2_send;

    res.version(req.version());
    
    res.set(boost::beast::http::field::server, "Beryl ID Server");

    res.set(boost::beast::http::field::content_type, "application/json");

    if(!middle_verify.entry(req,res)){
        return;
    };

    switch(req.method()) {

        case boost::beast::http::verb::get:

            this->getter.route_controller(req,res);
            
            break;
///write a router for the rest of the methods
        case boost::beast::http::verb::delete_:
            if(this->path_finder(req,"/beryl/del_user_id")){

                res.result(boost::beast::http::status::ok);

                res.body() = (json.delete_bool(this->piper.global_del(req))).dump();

            } else if(this->path_finder(req,"/beryl/del_space_id")){
                
                res.result(boost::beast::http::status::ok);

                res.body() = (json.delete_bool(this->piper.global_del(req))).dump();

            } else if(this->path_finder(req,"beryl/del_ugc")){

                res.result(boost::beast::http::status::ok);

                res.body() = (json.delete_bool(this->piper.global_del(req))).dump();

            } else{

                res.result(boost::beast::http::status::not_found);
            
                res.body() = "The resource was not found.";

            };

            break;

        default:
            res.result(boost::beast::http::status::bad_request);
            
            res.body() = "Invalid request method.";
            
            break;
    };

    res.keep_alive(req.keep_alive());

    res.prepare_payload();  // Prepare the payload before sending the response

};