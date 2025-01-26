#pragma once

#include <iostream>
#include <string>
#include <functional>

#include <boost/asio.hpp>
#include <boost/beast.hpp>

using namespace std;

class auth_middleware{
    public:
    auth_middleware()=default;
    bool entry(boost::beast::http::request<boost::beast::http::string_body>& req);

    private:

};



bool auth_middleware::entry(boost::beast::http::request<boost::beast::http::string_body>& req){

};