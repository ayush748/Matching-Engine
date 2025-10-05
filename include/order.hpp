#pragma once
#include <string>
#include <cstdint>

enum class Side { BUY, SELL };
enum class OrderType { LIMIT, MARKET, IOC, FOK, STOP_LIMIT, STOP_LOSS, TAKE_PROFIT };

struct Order {
    uint64_t id;
    std::string id_str;
    std::string symbol;
    Side side;
    OrderType type;
    double price;
    double quantity;
    double remaining;
    double stop_price;
    double take_profit;

    Order(uint64_t id_, const std::string& symbol_, Side side_, OrderType type_, 
          double price_, double qty_, double stop_price_ = 0, double take_profit_ = 0)
        : id(id_), id_str("O" + std::to_string(id_)), symbol(symbol_), side(side_), type(type_), 
          price(price_), quantity(qty_), remaining(qty_), stop_price(stop_price_), take_profit(take_profit_) {}
};
