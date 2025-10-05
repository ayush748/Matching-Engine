#include "order_book.hpp"
#include <algorithm>
#include <iostream>

void OrderBook::addOrder(const Order& o) {
    std::lock_guard<std::mutex> lock(mtx);
    if (o.side == Side::BUY) bids.push_back(o);
    else asks.push_back(o);

    std::sort(bids.begin(), bids.end(), [](const Order& a, const Order& b){ return a.price > b.price; });
    std::sort(asks.begin(), asks.end(), [](const Order& a, const Order& b){ return a.price < b.price; });

    // Debug print
    std::cout << "[OrderBook::addOrder] symbol=" << symbol
              << " bids=" << bids.size() << " asks=" << asks.size()
              << " bestBid=" << (bids.empty()?0:bids.front().price)
              << " bestAsk=" << (asks.empty()?0:asks.front().price) << std::endl;
}

void OrderBook::cancelOrder(uint64_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto eraseOrder = [id](std::vector<Order>& v){
        v.erase(std::remove_if(v.begin(), v.end(), [id](const Order& o){ return o.id == id; }), v.end());
    };
    eraseOrder(bids);
    eraseOrder(asks);
}

void OrderBook::matchOrder(Order& incoming, std::vector<Trade>& tradesVec) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& opposite = (incoming.side == Side::BUY) ? asks : bids;

    for (auto it = opposite.begin(); it != opposite.end() && incoming.remaining > 0;) {
        bool match = (incoming.type == OrderType::MARKET) ||
                     ((incoming.side == Side::BUY) ? (incoming.price >= it->price) : (incoming.price <= it->price));

        if (match) {
            double qty = std::min(incoming.remaining, it->remaining);
            Trade t{ "T" + std::to_string(tradesVec.size() + 1), it->id_str, incoming.id_str,
                     incoming.symbol, it->price, qty, incoming.side };
            tradesVec.push_back(t);
            incoming.remaining -= qty;
            it->remaining -= qty;
            if (it->remaining <= 0) it = opposite.erase(it);
            else ++it;
        } else break;
    }

    if ((incoming.type == OrderType::IOC || incoming.type == OrderType::FOK) && incoming.remaining > 0)
        incoming.remaining = 0;

    // Debug after matching
    std::cout << "[OrderBook::matchOrder] symbol=" << symbol
              << " incoming_remaining=" << incoming.remaining
              << " bids=" << bids.size() << " asks=" << asks.size()
              << " bestBid=" << (bids.empty()?0:bids.front().price)
              << " bestAsk=" << (asks.empty()?0:asks.front().price) << std::endl;
}

void OrderBook::checkStopOrders(std::vector<Trade>& tradesVec) {
    // Placeholder
}

BBO OrderBook::getBBO() const {
    BBO bbo;
    std::lock_guard<std::mutex> lock(mtx);
    if (!bids.empty()) bbo.bestBid = bids.front().price;
    if (!asks.empty()) bbo.bestAsk = asks.front().price;
    return bbo;
}

std::vector<std::array<double,2>> OrderBook::getTopN(int n) const {
    std::vector<std::array<double,2>> out;
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < n; ++i) {
        double price=0, qty=0;
        if ((size_t)i < bids.size()) { price=bids[i].price; qty=bids[i].remaining; }
        out.push_back({price, qty});
    }
    for (int i = 0; i < n; ++i) {
        double price=0, qty=0;
        if ((size_t)i < asks.size()) { price=asks[i].price; qty=asks[i].remaining; }
        out.push_back({price, qty});
    }
    return out;
}
