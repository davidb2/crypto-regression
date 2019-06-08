#ifndef BACKEND_CLIENT_H_
#define BACKEND_CLIENT_H_

#include <string>

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

#include "server.h"

namespace gdax {

typedef websocketpp::client<websocketpp::config::asio_tls_client> WebsocketClient;
typedef websocketpp::config::asio_tls_client::message_type::ptr WebsocketMessagePtr;

// Gdax Client.
class Client {
 public:
  Client(boost::asio::io_service* ios);
  bool setUp(const std::string& uri, WebsocketErrorCode* ec) noexcept;

 private:
  void onOpen(WebsocketHandle handle);
  void onFail(WebsocketHandle handle);
  void onClose(WebsocketHandle handle);
  void onMessage(WebsocketHandle handle, WebsocketMessagePtr message);

  // Source: https://github.com/zaphoyd/websocketpp/blob/master/examples/debug_client/debug_client.cpp#L95
  WebsocketContextPtr onTlsInit(WebsocketHandle hdl);

 private:
  WebsocketClient c_;
};

} // namespace gdax

#endif // BACKEND_CLIENT_H_
