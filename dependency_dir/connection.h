// connection.h
#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/beast.hpp>

using namespace std;


struct domain {
    std::string host_url;
    std::string port;
};



class connections {
private:
    bool status;
    boost::asio::io_context& ioc;
    domain end_p_details;
    boost::asio::ip::tcp::acceptor con_acceptor;
    boost::asio::ip::tcp::resolver endpoint_resolver;
    boost::asio::ip::tcp::endpoint server_endpoint;
    void start_listener();
    void start_acceptor();
    void r_w_handler(std::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::asio::yield_context yield);
    void request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>&  res)

public:
    bool get_status() const {

        return this->status;

    }

    void start_server();

    connections(boost::asio::io_context& io_ctx, domain end_p_url)
        : status(false), ioc(io_ctx), end_p_details(end_p_url), endpoint_resolver(io_ctx), con_acceptor(io_ctx) {

        cout << "ready with socket connection handler...." << endl;

    }

};



void connections::start_server() {

try{

        boost::asio::ip::tcp::resolver::results_type endpoints = endpoint_resolver.resolve(end_p_details.host_url, end_p_details.port);

        server_endpoint = *endpoints.begin();

        this->start_listener();


} catch(const exception& e){

    cout<<"Error making connection - "<<e.what()<<endl;
    

}

};




void connections::start_listener(){

    con_acceptor.open(server_endpoint.protocol());

    con_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));

    con_acceptor.bind(server_endpoint);

    con_acceptor.listen();

    cout<<"server endpoint is - "<<server_endpoint<<endl;

    this->start_acceptor();
};




void connections::start_acceptor(){

    auto socket=std::make_shared<boost::asio::ip::tcp::socket>(ioc);

    con_acceptor.async_accept(*socket,[this,socket](const boost::system::error_code ec){

        if(!ec){

            this->status=true;

            if(socket->is_open()){

                cout<<"client connection Acknoledged with ip - "<<socket->remote_endpoint()<<endl;

                boost::asio::spawn(con_acceptor.get_executor(), [this,socket](boost::asio::yield_context yield) {

                    r_w_handler(socket, yield);

                });

            };

            this->start_acceptor();

        } else{

            cout<<"Error Accepting - "<<ec.message()<<endl;

            this->status=false;

            this->start_listener();

        }

    });


};





void connections::r_w_handler(std::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::asio::yield_context yield) {

        try {

            for (;;) {

                // std::size_t length = socket->async_read_some(boost::asio::buffer(data), yield);

                // boost::asio::async_write(*socket, boost::asio::buffer(data, length), yield);


            boost::beast::tcp_stream stream_socket(std::move(*socket));

            boost::beast::flat_buffer buffer;

            boost::beast::http::request<boost::beast::http::string_body> req;

            boost::beast::http::response<boost::beast::http::string_body> res;

            boost::beast::http::async_read(stream_socket,buffer,req);

            request_handler(req,res);

            boost::beast::http::async_write(stream_socket,res,yield);

            stream_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
3

            };

        } catch (const std::exception& e) {

            std::cerr <<" Error with session " << e.what() << std::endl;

        }

};




void connection::request_handler(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body> res){

    

}