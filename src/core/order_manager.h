#pragma once

#include <mutex>
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include "../api/api_client.h"

class OrderManager {
public:
    OrderManager();
    bool placeOrder(const std::string& instrument, double amount, double price, const std::string& type);
    bool cancelOrder(const std::string& orderId);
    nlohmann::json getOrderBook(const std::string& instrument);
    nlohmann::json getPositions();

private:
    std::mutex mutex_;
    APIClient apiClient_;
    std::unordered_map<std::string, nlohmann::json> activeOrders_;
    void storeOrder(const std::string& id, const nlohmann::json& data);
};
// Placeholder for src/core/order_manager.h
