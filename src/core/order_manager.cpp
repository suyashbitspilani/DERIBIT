#include "order_manager.h"
#include "../utils/logger.h"
#include <fstream>

OrderManager::OrderManager()
    : apiClient_("khGedTfe", "0weEB1tYmLiAA1LLw_16redLFxVT6-6sDYP93BfwH28") {
    if (!apiClient_.authenticate()) {
        Logger::error("Failed to authenticate API Client");
    } else {
        Logger::info("✅ API Client authenticated successfully");
    }
}

bool OrderManager::placeOrder(const std::string& instrument, double amount, double price, const std::string& type) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto response = apiClient_.placeOrder(instrument, amount, price, type);
    if (!response.empty() && response.contains("result")) {
        std::string orderId = response["result"]["order"]["order_id"];
        storeOrder(orderId, response["result"]["order"]);
        Logger::info("🟢 Order placed: " + orderId);
        return true;
    }

    Logger::error("❌ Failed to place order.");
    return false;
}

bool OrderManager::cancelOrder(const std::string& orderId) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto response = apiClient_.cancelOrder(orderId);
    if (!response.empty() && response.contains("result")) {
        activeOrders_.erase(orderId);
        Logger::info("🟠 Order cancelled: " + orderId);
        return true;
    }

    Logger::error("❌ Failed to cancel order.");
    return false;
}

nlohmann::json OrderManager::getOrderBook(const std::string& instrument) {
    return apiClient_.getOrderBook(instrument);
}

nlohmann::json OrderManager::getPositions() {
    return apiClient_.getPositions();
}

void OrderManager::storeOrder(const std::string& id, const nlohmann::json& data) {
    activeOrders_[id] = data;
    Logger::info("📦 Order stored: " + id);
}

