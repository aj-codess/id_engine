#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;

struct session_data{
    std::string server_name,last_signed;
};


class server_session{
    public:
    server_session()=default;
    bool token_validity(std::string id);

    private:

};


bool server_session::token_validity(std::string id){



};