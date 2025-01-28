#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;

struct session_data{
    std::string server_name,last_signed;
};


class server_session{
    public:
    server_session()=default;
    bool isInSession(std::string id);

    private:
    map<std::string,session_data> session_container;
};


bool server_session::isInSession(std::string id){

    for(const auto& [key,value] : session_container){

        

    };

};