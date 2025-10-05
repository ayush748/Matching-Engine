#include <napi.h>
#include "../include/matching_engine.hpp"

// Global engine instance
static MatchingEngine engine;

// Submit an order from Node.js
Napi::Value SubmitOrder(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsObject())
        return Napi::Boolean::New(env, false);

    Napi::Object obj = info[0].As<Napi::Object>();

    uint64_t id = obj.Get("id").As<Napi::Number>().Int64Value();
    std::string symbol = obj.Get("symbol").As<Napi::String>();
    std::string sideStr = obj.Get("side").As<Napi::String>();
    std::string typeStr = obj.Get("type").As<Napi::String>();
    double price = obj.Get("price").As<Napi::Number>().DoubleValue();
    double quantity = obj.Get("quantity").As<Napi::Number>().DoubleValue();

    Side side = (sideStr == "BUY") ? Side::BUY : Side::SELL;

    OrderType type = OrderType::LIMIT;
    if (typeStr == "MARKET") type = OrderType::MARKET;
    else if (typeStr == "IOC") type = OrderType::IOC;
    else if (typeStr == "FOK") type = OrderType::FOK;
    else if (typeStr == "STOP_LIMIT") type = OrderType::STOP_LIMIT;

    engine.submitOrder(Order(id, symbol, side, type, price, quantity));
    return Napi::Boolean::New(env, true);
}

// Convert a Trade to Napi::Object
Napi::Object TradeToObject(Napi::Env env, const Trade& t) {
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("trade_id", Napi::String::New(env, t.trade_id));
    obj.Set("maker_order_id", Napi::String::New(env, t.maker_order_id));
    obj.Set("taker_order_id", Napi::String::New(env, t.taker_order_id));
    obj.Set("symbol", Napi::String::New(env, t.symbol));
    obj.Set("price", Napi::Number::New(env, t.price));
    obj.Set("quantity", Napi::Number::New(env, t.quantity));
    obj.Set("aggressor_side", Napi::String::New(env, t.aggressor_side == Side::BUY ? "BUY" : "SELL"));
    return obj;
}

// Get BBO for a symbol
Napi::Value GetBBO(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string symbol = info[0].As<Napi::String>();
    BBO bbo = engine.getBBO(symbol);
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("bestBid", bbo.bestBid);
    obj.Set("bestAsk", bbo.bestAsk);
    return obj;
}

// Get recent trades and clear them
Napi::Value GetAndClearTrades(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString())
        return Napi::Array::New(env, 0);

    std::string symbol = info[0].As<Napi::String>();
    auto trades = engine.fetchAndClearTrades(symbol);
    Napi::Array arr = Napi::Array::New(env, trades.size());

    for (size_t i = 0; i < trades.size(); ++i)
        arr.Set(i, TradeToObject(env, trades[i]));

    return arr;
}

// Initialize module
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("submitOrder", Napi::Function::New(env, SubmitOrder));
    exports.Set("getBBO", Napi::Function::New(env, GetBBO));
    exports.Set("getAndClearTrades", Napi::Function::New(env, GetAndClearTrades));
    return exports;
}

NODE_API_MODULE(binding, Init)
