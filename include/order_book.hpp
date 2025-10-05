#pragma once
#include "order.hpp"
#include "trade.hpp"
#include <vector>
#include <string>
#include <mutex>
#include <array>

struct BBO {
    double bestBid = 0.0;
    double bestAsk = 0.0;
};

struct OrderBook {
    std::string symbol;
    std::vector<Order> bids;
    std::vector<Order> asks;
    std::vector<Order> stop_orders;
    mutable std::mutex mtx;

    OrderBook() = default;
    explicit OrderBook(const std::string& sym) : symbol(sym) {}
    OrderBook(const OrderBook&) = delete;
    OrderBook& operator=(const OrderBook&) = delete;

    void addOrder(const Order& o);
    void cancelOrder(uint64_t id);
    void matchOrder(Order& incoming, std::vector<Trade>& trades);
    void checkStopOrders(std::vector<Trade>& trades);
    BBO getBBO() const;
    std::vector<std::array<double,2>> getTopN(int n=10) const;
};
