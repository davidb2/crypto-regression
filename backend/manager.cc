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
  ios_.run();
}

} // namespace gdax
