#include <iostream>
#include <string>

#include "manager.h"

namespace gdax {

Manager::Manager(const std::string& gdaxEndpointUri, const unsigned serverPort)
  : ios_{}
  , client_{&ios_}
  , gdaxUri_{gdaxEndpointUri}
  , server_{&ios_}
  , serverPort_{serverPort}
{

}

bool Manager::setUp(WebsocketErrorCode* ec) noexcept {
  return !client_.setUp(gdaxUri_, ec) || !server_.setUp(serverPort_, ec);
}

void Manager::start() {
  std::cout << "Listening on port " << serverPort_ << "." << std::endl;
  ios_.run();
}

} // namespace gdax
