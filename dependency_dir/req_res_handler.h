#pragma once

#include <iostream>
#include <string>

#include <memory>

#include <logic.h>
#include <connection.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>


class req_res_handler{
    private:
    id_schema generator;
    nlohmann::json make_json(std::string id);

    public:
    void request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res);
};



nlohmann::json req_res_handler::make_json(std::string id){

    nlohmann::json cast{"id",id};

    return cast;

};



void req_res_handler::request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res){

    res.version(req.version());
    
    res.set(boost::beast::http::field::server, "Beast");

    res.set(boost::beast::http::field::content_type, "text/html");

    switch (req.method()) {

        case boost::beast::http::verb::get:
            if (req.target() == "/beryl/id") {
            
                res.result(boost::beast::http::status::ok);
            
                res.body() = generator.generate_id("0", "0", "0");
            
            } else {
            
                res.result(boost::beast::http::status::not_found);
            
                res.body() = "The resource was not found.";
            
            }
            break;
        default:
            res.result(boost::beast::http::status::bad_request);
            
            res.body() = "Invalid request method.";
            
            break;
    }

    res.prepare_payload();  // Prepare the payload before sending the response

};