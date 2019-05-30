#include <string>

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include "server.h"

namespace gdax {

typedef websocketpp::client<websocketpp::config::asio_client> WebsocketClient;
typedef websocketpp::connection_hdl WebsocketHandle;
typedef websocketpp::config::asio_client::message_type::ptr WebsocketMessagePtr;

// Gdax Client.
class Client {
 public:
  Client(const Server* server);
  bool start(const std::string& uri, WebsocketErrorCode* ec) noexcept;

 private:
  void onOpen(WebsocketHandle handle);
  void onFail(WebsocketHandle handle);
  void onClose(WebsocketHandle handle);
  void onMessage(WebsocketHandle handle, WebsocketMessagePtr message);

 private:
  WebsocketClient c_;
};

} // namespace gdax
