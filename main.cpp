#include <iostream>
#include <string>
#include <memory>

#include <connection.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/coroutine/all.hpp>
#include <nlohmann/json.hpp>

using namespace std;

class conn {
public:
    void start_server();
    bool get_server_status();

    conn(boost::asio::io_context& ctx, domain end_p_url)
        : server(ctx, end_p_url) {

        cout << "loading server " << endl;

    }

private:
    connections server;
};




void conn::start_server() {


    server.start_server();

}




bool conn::get_server_status() {

    return server.get_status();

};




int main() {

    domain url{"localhost", "8080"};

    boost::asio::io_context context;

    conn server(context, url);

    server.start_server();

    context.run();

    return 0;
}
