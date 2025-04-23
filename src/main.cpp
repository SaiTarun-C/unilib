#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using namespace std;

// Define a WebSocket++ server
typedef websocketpp::server<websocketpp::config::asio> server;

// Define the message handler
void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
    cout << "Received message: " << msg->get_payload() << endl;
    // Send the same message back to the client
    msg->get_server().send(hdl, msg->get_payload(), websocketpp::frame::opcode::text);
}

int main() {
    server echo_server;

    try {
        // Initialize WebSocket++ server
        echo_server.init_asio();
        echo_server.set_reuse_addr(true);
        
        // Register the message handler
        echo_server.set_message_handler(&on_message);

        // Set the server to listen on port 9002
        echo_server.listen(9002);
        echo_server.start_accept();

        cout << "WebSocket server running on ws://localhost:9002" << endl;

        // Start the WebSocket++ server
        echo_server.run();
    } catch (websocketpp::exception const &e) {
        cerr << "WebSocket++ exception: " << e.what() << endl;
        return 1;
    } catch (std::exception const &e) {
        cerr << "Standard exception: " << e.what() << endl;
        return 2;
    }

    return 0;
}
