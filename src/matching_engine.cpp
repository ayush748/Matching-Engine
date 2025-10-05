#include "matching_engine.hpp"
#include <iostream>

void MatchingEngine::submitOrder(const Order& order) {
    books.try_emplace(order.symbol);
    auto& ob = books[order.symbol];
    auto& tradeList = trades[order.symbol];

    Order newOrder = order;
    ob.checkStopOrders(tradeList);
    ob.matchOrder(newOrder, tradeList);

    if (newOrder.remaining > 0 && (order.type == OrderType::LIMIT || order.type == OrderType::STOP_LIMIT))
        ob.addOrder(newOrder);

    // Debug: print BBO and trade count after submission
    auto bbo = ob.getBBO();
    std::cout << "[MatchingEngine::submitOrder] symbol=" << order.symbol
              << " trades=" << tradeList.size()
              << " bestBid=" << bbo.bestBid << " bestAsk=" << bbo.bestAsk << std::endl;
}

BBO MatchingEngine::getBBO(const std::string& symbol) {
    if (books.find(symbol) != books.end()) return books[symbol].getBBO();
    return BBO{};
}

std::vector<Trade> MatchingEngine::getRecentTrades(const std::string& symbol) {
    if (trades.find(symbol) != trades.end()) return trades[symbol];
    return {};
}

std::vector<Trade> MatchingEngine::fetchAndClearTrades(const std::string& symbol) {
    if (trades.find(symbol) == trades.end()) return {};
    auto copy = trades[symbol];
    trades[symbol].clear();
    return copy;
}

void MatchingEngine::printOrderBook(const std::string& symbol) {
    if (books.find(symbol) != books.end()) {
        auto& ob = books[symbol];
        auto bbo = ob.getBBO();
        std::cout << "OrderBook " << symbol << " | BestBid: " << bbo.bestBid << " BestAsk: " << bbo.bestAsk << "\n";
    } else std::cout << "No orders for symbol " << symbol << "\n";
}

std::vector<std::array<double,4>> MatchingEngine::getTopN(const std::string& symbol, int n) {
    std::vector<std::array<double,4>> out;
    if (books.find(symbol) == books.end()) return out;
    auto& ob = books[symbol];
    std::lock_guard<std::mutex> lock(ob.mtx);
    for (int i=0;i<n;++i){
        double bidPrice=0,bidQty=0,askPrice=0,askQty=0;
        if ((size_t)i<ob.bids.size()){ bidPrice=ob.bids[i].price; bidQty=ob.bids[i].remaining; }
        if ((size_t)i<ob.asks.size()){ askPrice=ob.asks[i].price; askQty=ob.asks[i].remaining; }
        out.push_back({bidPrice,bidQty,askPrice,askQty});
    }
    return out;
}
