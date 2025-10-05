#pragma once
#include "order_book.hpp"
#include <unordered_map>
#include <vector>
#include <array>
#include <string>

class MatchingEngine {
private:
    std::unordered_map<std::string, OrderBook> books;
    std::unordered_map<std::string, std::vector<Trade>> trades;

public:
    void submitOrder(const Order& order);
    BBO getBBO(const std::string& symbol);
    std::vector<Trade> getRecentTrades(const std::string& symbol);
    std::vector<Trade> fetchAndClearTrades(const std::string& symbol);
    std::vector<std::array<double,4>> getTopN(const std::string& symbol, int n=10);
    void printOrderBook(const std::string& symbol);
};
