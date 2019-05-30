#include "client.h"
#include "types.h"

namespace gdax {

void Client::onOpen(WebsocketClient* c, WebsocketHandle hdl) {
  std::string msg = "Hello";
  c->send(hdl, msg, websocketpp::frame::opcode::text);
  c->get_alog().write(websocketpp::log::alevel::app, "Sent Message: " + msg);
}

void Client::onFail(WebsocketClient* c) {
  c->get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
}

void Client::onMessage(
  WebsocketClient* c,
  WebsocketHandle hdl,
  WebsocketMessagePtr msg)
{
  c->get_alog().write(
    websocketpp::log::alevel::app,
    "Received Reply: " + msg->get_payload());

  WebsocketErrorCode ec;
  c->send(hdl, "hi" + msg->get_payload(), msg->get_opcode(), ec);

  if (ec) {
    c->get_alog().write(
      websocketpp::log::alevel::app,
      "Error: " + ec.message());

    // c->close(hdl,websocketpp::close::status::normal, "");
  }
}

void Client::onClose(WebsocketClient* c, WebsocketHandle hdl) {
  c->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
}

} // namespace gdax
