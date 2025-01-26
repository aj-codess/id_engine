#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/url.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>

class url_dep{
    public:
    url_dep()=default;
    bool path_finder(boost::beast::http::request<boost::beast::http::string_body>& req,std::string path_condition);

    private:

};


bool url_dep::path_finder(boost::beast::http::request<boost::beast::http::string_body>& req,std::string path_condition){
    
    boost::urls::url_view url(req.target());

    std::string url_path=std::string(url.encoded_path());

    return (url_path==path_condition);

}