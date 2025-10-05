#include "matching_engine.hpp"
#include "utils.hpp"
#include <iostream>

int main() {
    MatchingEngine engine;

    engine.submitOrder(Order(1,"BTC-USDT",Side::BUY,OrderType::LIMIT,30000,0.5));
    engine.submitOrder(Order(2,"BTC-USDT",Side::SELL,OrderType::LIMIT,30010,0.5));
    engine.submitOrder(Order(3,"BTC-USDT",Side::BUY,OrderType::MARKET,0,0.2));

    engine.printOrderBook("BTC-USDT");

    auto trades = engine.getRecentTrades("BTC-USDT");
    std::cout<<"\nTrades executed:\n";
    for(auto& t: trades){
        std::cout<<currentTimestamp()<<" "<<t.trade_id<<" "<<t.symbol<<" "<<t.price<<" "<<t.quantity<<"\n";
    }
    return 0;
}
