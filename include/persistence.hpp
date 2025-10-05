#pragma once
#include <string>
#include "order_book.hpp"

namespace Persistence {
    void saveOrderBook(const OrderBook& ob, const std::string& filename);
    bool loadOrderBook(OrderBook& ob, const std::string& filename);
}
