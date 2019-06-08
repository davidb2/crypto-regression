#ifndef BACKEND_MANAGER_H_
#define BACKEND_MANAGER_H_

#include <string>

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

#include "client.h"
#include "server.h"

namespace gdax {

// Gdax Manager.
class Manager {
 public:
  Manager(const std::string& gdaxEndpointUri, const unsigned serverPort);
  bool setUp(WebsocketErrorCode* ec) noexcept;
  void start();

 private:
  boost::asio::io_service ios_;

  Client client_;
  const std::string gdaxUri_;

  Server server_;
  const unsigned serverPort_;
};

} // namespace gdax

#endif // BACKEND_MANAGER_H_
