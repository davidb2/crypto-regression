#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

#include "types.h"

namespace gdax {

typedef websocketpp::server<websocketpp::config::asio> WebsocketServer;
typedef websocketpp::connection_hdl WebsocketHandle;
typedef WebsocketServer::message_ptr WebsocketMessagePtr;

// Dashboard Server.
class Server {
 public:
  Server(const std::string& uri);
  void onOpen(WebsocketServer* server, WebsocketHandle handle);
  void onFail(WebsocketServer* server);
  void onClose(WebsocketServer* server, WebsocketHandle handle);
  void onMessage(
    WebsocketServer* server,
    WebsocketHandle handle,
    WebsocketMessagePtr message
  );

 private:
};

} // namespace gdax
