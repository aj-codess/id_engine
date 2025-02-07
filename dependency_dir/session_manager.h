#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include <global_dcl.h>
#include <timer.h>

using namespace std;

struct session_data{
    std::string server_name;
    time_t last_signed;
};


class server_session{
    public:
    server_session()=default;
    bool isInSession(std::string id);
    bool create_session(std::string id,std::string name,time_t time);
    bool update_session(std::string id,std::string new_id,time_t assigned_time);
    bool name_check(std::string id,std::string server_name);
    bool check_expiry(std::string id);

    private:
    map<std::string,session_data> session_container;
    global_dcl global;
    timer pulse;
    void session_delete(std::string id);
};



bool server_session::name_check(std::string id,std::string server_name){

        if(session_container[id].server_name==server_name){
            
            return true;

        };

        return false;

};



bool server_session::isInSession(std::string id){

    for(const auto& [key,value] : session_container){

        if(id.find(this->global.get_server_name()) !=std::string::npos && key==id){

            return true;

        };

    };

    return false;

};


bool server_session::create_session(std::string id,std::string name,time_t time){

    bool status;

    try{

        session_container[id]=session_data();

        session_container[id].server_name=name;

        session_container[id].last_signed=time;

        status=true;

    } catch(const std::exception& e){

        std::cerr<<" Failed to create Session: "<<e.what()<<std::endl;

        status=false;

    };

    return status;

};



bool server_session::update_session(std::string id,std::string new_id,time_t assigned_time){

    try{

        if(this->isInSession(id)==true){

                this->session_container[id].last_signed=assigned_time;

                auto it=this->session_container.find(id);

                this->session_container[new_id]=it->second;

                this->session_delete(id);

                if(this->isInSession(id)==false){
                    return true;
                };

        } else{

            return false;

        };

    } catch(const std::exception& e){

        std::cerr<<"Error updating Session: "<<e.what()<<endl;

        return false;

    };

};



void server_session::session_delete(std::string id){

    this->session_container.erase(id);

}


bool server_session::check_expiry(std::string id){

    auto it=this->session_container.find(id);

    if((this->pulse.get_timeOnly() - it->second.last_signed) >= 300000){

        return true;

    };

    return false;

};