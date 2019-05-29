#include <iostream>

#include <nlohmann/json.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>


typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

// Handlers
void on_open(client* c, websocketpp::connection_hdl hdl) {
  std::string msg = "Hello";
  c->send(hdl, msg,websocketpp::frame::opcode::text);
  c->get_alog().write(websocketpp::log::alevel::app, "Sent Message: "+msg);
}

void on_fail(client* c, websocketpp::connection_hdl hdl) {
  c->get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
}

void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
  c->get_alog().write(websocketpp::log::alevel::app, "Received Reply: "+msg->get_payload());
  websocketpp::lib::error_code ec;
  c->send(hdl, "hi" + msg->get_payload(), msg->get_opcode(), ec);
  if (ec) {
    c->get_alog().write(websocketpp::log::alevel::app, "Error: " + ec.message());
    // c->close(hdl,websocketpp::close::status::normal, "");
  }
}

void on_close(client* c, websocketpp::connection_hdl hdl) {
  c->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
}

int main(int argc, char* argv[]) {
  // Create a client endpoint
  client c;

  std::string uri = "ws://demos.kaazing.com/echo";

  if (argc == 2) {
    uri = argv[1];
  }

  try {
    // Set logging to be pretty verbose (everything except message payloads)
    c.clear_access_channels(websocketpp::log::alevel::frame_header);
    c.clear_access_channels(websocketpp::log::alevel::frame_payload);

    // Initialize ASIO
    c.init_asio();

    // Register our message handler
    c.set_open_handler(bind(&on_open,&c,::_1));
    c.set_fail_handler(bind(&on_fail,&c,::_1));
    c.set_message_handler(bind(&on_message,&c,::_1,::_2));
    c.set_close_handler(bind(&on_close,&c,::_1));

    websocketpp::lib::error_code ec;
    client::connection_ptr con = c.get_connection(uri, ec);
    if (ec) {
      std::cout << "could not create connection because: " << ec.message() << std::endl;
      return 0;
    }

    // Note that connect here only requests a connection. No network messages are
    // exchanged until the event loop starts running in the next line.
    c.connect(con);

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    c.run();
  } catch (websocketpp::exception const & e) {
    std::cout << e.what() << std::endl;
  }
}
