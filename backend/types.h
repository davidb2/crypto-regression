#include <boost/asio/ssl/context.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef boost::asio::ssl::context WebsocketContext;
typedef websocketpp::connection_hdl WebsocketHandle;
typedef websocketpp::lib::error_code WebsocketErrorCode;
typedef websocketpp::lib::shared_ptr<WebsocketContext> WebsocketContextPtr;
