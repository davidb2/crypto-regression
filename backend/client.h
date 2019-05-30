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
  Client(const std::string& uri, const Server* server);
  void onOpen(WebsocketClient* client, WebsocketHandle handle);
  void onFail(WebsocketClient* client);
  void onClose(WebsocketClient* client, WebsocketHandle handle);
  void onMessage(
    WebsocketClient* client,
    WebsocketHandle handle,
    WebsocketMessagePtr message
  );

 private:
};

} // namespace gdax
