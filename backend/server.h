#include <string>
#include <vector>

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
  Server();
  bool start(const unsigned port, WebsocketErrorCode* ec) noexcept;

 private:
  void onOpen(WebsocketHandle handle);
  void onFail(WebsocketHandle handle);
  void onClose(WebsocketHandle handle);
  void onMessage(WebsocketHandle handle, WebsocketMessagePtr message);

 private:
  WebsocketServer s_;
  std::vector<WebsocketHandle> subscribers_;
};

} // namespace gdax
