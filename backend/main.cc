#include <string>

#include <gflags/gflags.h>

#include "client.h"
#include "types.h"

DEFINE_string(
  gdaxUri,
  "wss://ws-feed.pro.coinbase.com/",
  "websocket uri for the gdax exchange"
);

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  gdax::Client client{nullptr};

  WebsocketErrorCode ec;
  client.start(FLAGS_gdaxUri, &ec);
}
