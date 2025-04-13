#pragma once

#include <thread>
#include <set>
#include <string>
#include <mutex>
#include <map>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "../core/order_manager.h"

typedef websocketpp::server<websocketpp::config::asio> WebSocketServerBase;
typedef websocketpp::connection_hdl ConnectionHandle;

class WebSocketServer {
public:
    WebSocketServer(int port, OrderManager* om);
    void start();

private:
    void onOpen(ConnectionHandle hdl);
    void onClose(ConnectionHandle hdl);
    void onMessage(ConnectionHandle hdl, WebSocketServerBase::message_ptr msg);
    void broadcastLoop();

    WebSocketServerBase server_;
    int port_;
    std::set<ConnectionHandle, std::owner_less<ConnectionHandle>> clients_;
    std::mutex clientsMutex_;
    std::map<ConnectionHandle, std::string, std::owner_less<ConnectionHandle>> subscriptions_;
    OrderManager* orderManager_;
    std::thread broadcastThread_;
};
// Placeholder for src/ws/websocket_server.h
