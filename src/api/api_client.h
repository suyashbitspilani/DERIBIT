#pragma once

#include <string>
#include <nlohmann/json.hpp>

class APIClient {
public:
    APIClient(const std::string& clientId, const std::string& clientSecret);
    bool authenticate();
    nlohmann::json placeOrder(const std::string& instrument, double amount, double price, const std::string& type);
    nlohmann::json cancelOrder(const std::string& orderId);
    nlohmann::json getOrderBook(const std::string& instrument);
    nlohmann::json getPositions();

private:
    std::string clientId_;
    std::string clientSecret_;
    std::string accessToken_;
    std::string request(const std::string& endpoint, const std::string& method, const nlohmann::json& payload = {});
};
// Placeholder for src/api/api_client.h
