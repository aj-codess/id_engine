#pragma once

#include <iostream>
#include <string>

using namespace std;

class global_dcl{
    private:
    const std::string server_name="BERYL_ENGINE";

    public:
    global_dcl()=default;
    std::string get_server_name();
};


std::string global_dcl::get_server_name(){
    return this->server_name;
};