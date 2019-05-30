#include <functional>
#include <string>

#include "client.h"
#include "types.h"

using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;

namespace gdax {


void Client::onOpen(WebsocketHandle hdl) {
  std::string msg = "Hello";
  c_.send(hdl, msg, websocketpp::frame::opcode::text);
  c_.get_alog().write(websocketpp::log::alevel::app, "Sent Message: " + msg);
}

void Client::onFail(WebsocketHandle hdl) {
  c_.get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
}

void Client::onMessage(WebsocketHandle hdl, WebsocketMessagePtr msg) {
  c_.get_alog().write(
    websocketpp::log::alevel::app,
    "Received Reply: " + msg->get_payload());

  WebsocketErrorCode ec;
  c_.send(hdl, "hi" + msg->get_payload(), msg->get_opcode(), ec);

  if (ec) {
    c_.get_alog().write(
      websocketpp::log::alevel::app,
      "Error: " + ec.message());

    // c_->close(hdl,websocketpp::close::status::normal, "");
  }
}

void Client::onClose(WebsocketHandle hdl) {
  c_.get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
}

Client::Client(const Server* server) {
  // Set logging to be pretty verbose (everything except message payloads)
  c_.clear_access_channels(websocketpp::log::alevel::frame_header);
  c_.clear_access_channels(websocketpp::log::alevel::frame_payload);

  // Initialize ASIO
  c_.init_asio();

  // Register our message handler
  c_.set_open_handler(bind(&Client::onOpen, this, ::_1));
  c_.set_fail_handler(bind(&Client::onFail, this, ::_1));
  c_.set_message_handler(bind(&Client::onMessage, this, ::_1, ::_2));
  c_.set_close_handler(bind(&Client::onClose, this, ::_1));
}

bool Client::start(const std::string& uri, WebsocketErrorCode* eOut) noexcept {
  WebsocketErrorCode ec;
  try {
    WebsocketClient::connection_ptr con = c_.get_connection(uri, ec);

    if (ec) {
      std::cout << "could not create connection because: " << ec.message() << std::endl;
      if (eOut) *eOut = ec;
      return false;
    }

    // Note that connect here only requests a connection. No network messages are
    // exchanged until the event loop starts running in the next line.
    c_.connect(con);

    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    c_.run();
  } catch (const websocketpp::exception& e) {
    std::cout << e.what() << std::endl;
    if (eOut) *eOut = ec;
    return false;
  }
  return true;
}

} // namespace gdax
