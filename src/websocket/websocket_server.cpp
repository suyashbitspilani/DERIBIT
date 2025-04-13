#include "websocket_server.h"
#include "../utils/logger.h"

WebSocketServer::WebSocketServer(int port, OrderManager* om)
    : port_(port), orderManager_(om) {
    server_.init_asio();
    server_.set_open_handler([this](ConnectionHandle hdl) { onOpen(hdl); });
    server_.set_close_handler([this](ConnectionHandle hdl) { onClose(hdl); });
    server_.set_message_handler([this](ConnectionHandle hdl, WebSocketServerBase::message_ptr msg) { onMessage(hdl, msg); });
}

void WebSocketServer::start() {
    server_.listen(port_);
    server_.start_accept();
    broadcastThread_ = std::thread(&WebSocketServer::broadcastLoop, this);
    server_.run();
}

void WebSocketServer::onOpen(ConnectionHandle hdl) {
    std::lock_guard<std::mutex> lock(clientsMutex_);
    clients_.insert(hdl);
    Logger::info("🔌 WebSocket client connected.");
}

void WebSocketServer::onClose(ConnectionHandle hdl) {
    std::lock_guard<std::mutex> lock(clientsMutex_);
    clients_.erase(hdl);
    subscriptions_.erase(hdl);
    Logger::info("❌ WebSocket client disconnected.");
}

void WebSocketServer::onMessage(ConnectionHandle hdl, WebSocketServerBase::message_ptr msg) {
    std::lock_guard<std::mutex> lock(clientsMutex_);
    std::string payload = msg->get_payload();

    if (payload.rfind("SUBSCRIBE:", 0) == 0) {
        std::string instrument = payload.substr(10);  // after "SUBSCRIBE:"
        subscriptions_[hdl] = instrument;
        Logger::info("📩 Client subscribed to " + instrument);
        server_.send(hdl, "Subscribed to " + instrument, websocketpp::frame::opcode::text);
    } else {
        Logger::debug("Received unknown message: " + payload);
    }
}

void WebSocketServer::broadcastLoop() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(clientsMutex_);

        for (auto& [hdl, instrument] : subscriptions_) {
            try {
                auto book = orderManager_->getOrderBook(instrument);
                std::string bookStr = book.dump();
                server_.send(hdl, bookStr, websocketpp::frame::opcode::text);
            } catch (...) {
                Logger::error("Failed to send market data to a client.");
            }
        }
    }
}
// Placeholder for src/ws/websocket_server.cpp
