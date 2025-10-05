#include "persistence.hpp"
#include "json.hpp"
#include <fstream>

namespace Persistence {
    void saveOrderBook(const OrderBook& ob, const std::string& filename) {
        SimpleJSON j;
        j.add("symbol", ob.symbol);

        std::ostringstream bidsStream;
        bidsStream << "[";
        for (size_t i=0;i<ob.bids.size();++i){
            bidsStream << "{\"id\":\""<<ob.bids[i].id_str<<"\",\"price\":\""<<ob.bids[i].price
                       <<"\",\"remaining\":\""<<ob.bids[i].remaining<<"\"}";
            if (i+1<ob.bids.size()) bidsStream << ",";
        }
        bidsStream << "]";
        j.add("bids", bidsStream.str());

        std::ostringstream asksStream;
        asksStream << "[";
        for (size_t i=0;i<ob.asks.size();++i){
            asksStream << "{\"id\":\""<<ob.asks[i].id_str<<"\",\"price\":\""<<ob.asks[i].price
                       <<"\",\"remaining\":\""<<ob.asks[i].remaining<<"\"}";
            if (i+1<ob.asks.size()) asksStream << ",";
        }
        asksStream << "]";
        j.add("asks", asksStream.str());

        std::ofstream f(filename);
        f << j.str();
    }

    bool loadOrderBook(OrderBook& ob, const std::string& filename) {
        // Implement if needed
        return false;
    }
}
