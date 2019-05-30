#include "server.h"
#include "types.h"

namespace gdax {

void Server::onOpen(WebsocketServer* s, WebsocketHandle hdl) {
  std::string msg = "Hello";
  s->send(hdl, msg, websocketpp::frame::opcode::text);
  s->get_alog().write(websocketpp::log::alevel::app, "Sent Message: " + msg);
}

void Server::onFail(WebsocketServer* s) {
  s->get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
}

void Server::onMessage(
  WebsocketServer* s,
  WebsocketHandle hdl,
  WebsocketMessagePtr msg)
{
  s->get_alog().write(
    websocketpp::log::alevel::app,
    "Received Reply: " + msg->get_payload());

  WebsocketErrorCode ec;
  s->send(hdl, "hi" + msg->get_payload(), msg->get_opcode(), ec);

  if (ec) {
    s->get_alog().write(
      websocketpp::log::alevel::app,
      "Error: " + ec.message());

    // c->close(hdl,websocketpp::close::status::normal, "");
  }
}

void Server::onClose(WebsocketServer* s, WebsocketHandle hdl) {
  s->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
}

} // namespace gdax
