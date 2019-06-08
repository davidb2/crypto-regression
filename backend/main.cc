#include <string>

#include <gflags/gflags.h>

#include "manager.h"
#include "types.h"

DEFINE_string(
  gdaxUri,
  "wss://ws-feed.pro.coinbase.com/",
  "websocket uri for the gdax exchange"
);

DEFINE_uint32(
  serverPort,
  3000,
  "server port number"
);

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  gdax::Manager manager{FLAGS_gdaxUri, FLAGS_serverPort};

  WebsocketErrorCode ec;
  manager.setUp(&ec);
  manager.start();
}
