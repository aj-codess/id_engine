#pragma once

#include <iostream>
#include <string>

#include <memory>

#include <caller.h>
#include <connection.h>
#include <jsonScript.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/beast.hpp>
#include <boost/url.hpp>
#include <nlohmann/json.hpp>


class req_res_handler{
    private:
    caller piper;
    jsonScript json;
    bool path_finder(boost::beast::http::request<boost::beast::http::string_body>& req,std::string path);

    public:
    void request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res);
};




void req_res_handler::request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res){

    std::string data_2_send;

    res.version(req.version());
    
    res.set(boost::beast::http::field::server, "Beryl ID Server");

    res.set(boost::beast::http::field::content_type, "application/json");

    switch (req.method()) {

        case boost::beast::http::verb::get:
            if (this->path_finder(req,"/beryl/id")){
            
                res.result(boost::beast::http::status::ok);

                this->piper.url_2_body_gen(req,data_2_send);
            
                res.body() = (json.id_2_json(data_2_send)).dump();
            
            } else if(this->path_finder(req,"/beryl/persistent_data")){

                res.result(boost::beast::http::status::ok);

                res.body() = (json.convert_persistent(this->piper.get_persistent())).dump();

            } else {

                res.result(boost::beast::http::status::not_found);
            
                res.body() = "The resource was not found.";
            
            }
            break;

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

            }

        default:
            res.result(boost::beast::http::status::bad_request);
            
            res.body() = "Invalid request method.";
            
            break;
    };

    res.keep_alive(req.keep_alive());

    res.prepare_payload();  // Prepare the payload before sending the response

};



bool req_res_handler::path_finder(boost::beast::http::request<boost::beast::http::string_body>& req,std::string path_condition){
    
    boost::urls::url_view url(req.target());

    std::string url_path=std::string(url.encoded_path());

    return (url_path==path_condition);
};