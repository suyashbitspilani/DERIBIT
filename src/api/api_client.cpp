#include "api_client.h"
#include <iostream>
#include <cpr/cpr.h>

using json = nlohmann::json;

APIClient::APIClient(const std::string& clientId, const std::string& clientSecret)
    : clientId_(clientId), clientSecret_(clientSecret) {}

bool APIClient::authenticate() {
    std::string url = "https://test.deribit.com/api/v2/public/auth";
    std::string fullUrl = url + "?grant_type=client_credentials&client_id=" + clientId_ + "&client_secret=" + clientSecret_;

    auto response = cpr::Get(cpr::Url{fullUrl});
    if (response.status_code == 200) {
        auto jsonResp = json::parse(response.text);
        accessToken_ = jsonResp["result"]["access_token"];
        return true;
    }
    return false;
}

json APIClient::request(const std::string& endpoint, const std::string& method, const json& payload) {
    std::string url = "https://test.deribit.com/api/v2/" + endpoint;

    cpr::Header headers = {
        {"Authorization", "Bearer " + accessToken_},
        {"Content-Type", "application/json"}
    };

    cpr::Response response;
    if (method == "GET") {
        response = cpr::Get(cpr::Url{url}, headers);
    } else if (method == "POST") {
        response = cpr::Post(cpr::Url{url}, headers, cpr::Body{payload.dump()});
    }

    if (response.status_code == 200) {
        return json::parse(response.text);
    } else {
        std::cerr << "❌ API Error: " << response.status_code << " - " << response.text << std::endl;
        return {};
    }
}

json APIClient::placeOrder(const std::string& instrument, double amount, double price, const std::string& type) {
    json payload = {
        {"instrument_name", instrument},
        {"amount", amount},
        {"type", type},
        {"price", price}
    };
    return request("private/buy", "POST", payload);
}

json APIClient::cancelOrder(const std::string& orderId) {
    json payload = {
        {"order_id", orderId}
    };
    return request("private/cancel", "POST", payload);
}

json APIClient::getOrderBook(const std::string& instrument) {
    return request("public/get_order_book?instrument_name=" + instrument, "GET");
}

json APIClient::getPositions() {
    return request("private/get_positions?currency=BTC", "GET");
}
// Placeholder for src/api/api_client.cpp
