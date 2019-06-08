#include <functional>
#include <string>

#include <nlohmann/json.hpp>

#include "server.h"
#include "types.h"

using json = nlohmann::json;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;

namespace gdax {

void Server::onOpen(WebsocketHandle hdl) {
  subscribers_.push_back(hdl);
  // s_.send(hdl, msg, websocketpp::frame::opcode::text);
}

void Server::onFail(WebsocketHandle hdl) {
  s_.get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
}

void Server::onMessage(WebsocketHandle hdl, WebsocketMessagePtr msg)
{
  s_.get_alog().write(
    websocketpp::log::alevel::app,
    "Received Reply: " + msg->get_payload());

  const json message = json::parse(msg->get_payload(), nullptr, false);
  if (message == json::value_t::discarded) return;

  WebsocketErrorCode ec;
  s_.send(hdl, "hi" + msg->get_payload(), msg->get_opcode(), ec);

  if (ec) {
    s_.get_alog().write(
      websocketpp::log::alevel::app,
      "Error: " + ec.message());

    // c->close(hdl,websocketpp::close::status::normal, "");
  }
}

void Server::onClose(WebsocketHandle hdl) {
  s_.get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
}

Server::Server(boost::asio::io_service* ios) {
  // Initialize Asio
  s_.init_asio(ios);

  // Register our message handler
  s_.set_message_handler(bind(&Server::onMessage, this, ::_1, ::_2));
  s_.set_open_handler(bind(&Server::onOpen, this, ::_1));
  s_.set_fail_handler(bind(&Server::onFail, this, ::_1));
  s_.set_close_handler(bind(&Server::onClose, this, ::_1));
}

bool Server::setUp(const unsigned port, WebsocketErrorCode* ec) noexcept {
  try {
    s_.listen(port);
    s_.start_accept();
  } catch (websocketpp::exception const& e) {
    std::cout << e.what() << std::endl;
    return false;
  } catch (...) {
    std::cout << "other exception" << std::endl;
    return false;
  }
  return true;
}

} // namespace gdax
