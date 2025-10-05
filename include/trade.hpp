#pragma once
#include <string>
#include "order.hpp"

struct Trade {
    std::string trade_id;
    std::string maker_order_id;
    std::string taker_order_id;
    std::string symbol;
    double price;
    double quantity;
    Side aggressor_side;
};
