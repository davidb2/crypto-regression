#include <functional>
#include <string>

#include "server.h"
#include "types.h"

using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;

namespace gdax {

void Server::onOpen(WebsocketHandle hdl) {
  subscribers_.push_back(hdl);
  // s_->send(hdl, msg, websocketpp::frame::opcode::text);
}

void Server::onFail(WebsocketHandle hdl) {
  s_->get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
}

void Server::onMessage(WebsocketHandle hdl, WebsocketMessagePtr msg)
{
  s_->get_alog().write(
    websocketpp::log::alevel::app,
    "Received Reply: " + msg->get_payload());


  const json message = json::parse(msg->get_payload(), nullptr, false);
  if (message == json::value_t::discarded) return;

  WebsocketErrorCode ec;
  s_->send(hdl, "hi" + msg->get_payload(), msg->get_opcode(), ec);

  if (ec) {
    s_->get_alog().write(
      websocketpp::log::alevel::app,
      "Error: " + ec.message());

    // c->close(hdl,websocketpp::close::status::normal, "");
  }
}

void Server::onClose(WebsocketHandle hdl) {
  s_->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
}

bool start(const unsigned port, WebsocketErrorCode* ec) noexcept {
  try {
    // Initialize Asio
    s_.init_asio();

    // Register our message handler
    s_.set_message_handler(bind(&Server::onMessage, this, ::_1, ::_2));

    s_.listen(port);
    s_.start_accept();
    s_.run();
  } catch (websocketpp::exception const& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "other exception" << std::endl;
  }
}

} // namespace gdax
