from fastapi import FastAPI, WebSocket
from fastapi.responses import JSONResponse, FileResponse
from fastapi.staticfiles import StaticFiles
import asyncio
import os

app = FastAPI()
clients = set()

# Shared state
bestBid = 0
bestAsk = 0
trades = []

# Serve static files at /static
app.mount("/static", StaticFiles(directory="static"), name="static")

# Serve index.html at root
@app.get("/")
async def root():
    return FileResponse(os.path.join("static", "index.html"))

@app.post("/submit_order")
async def submit_order(order: dict):
    global bestBid, bestAsk, trades

    print("📥 Received order:", order)
    side = order["side"]
    price = order["price"]

    if side == "BUY":
        if price > bestBid:
            bestBid = price
    elif side == "SELL":
        if bestAsk == 0 or bestAsk == 0 or price < bestAsk:
            bestAsk = price

    trade = {
        "trade_id": len(trades) + 1,
        "symbol": order["symbol"],
        "price": price,
        "quantity": order["quantity"],
        "aggressor_side": side
    }
    trades.insert(0, trade)

    # Broadcast updates
    await broadcast({
        "type": "bbo",
        "symbol": order["symbol"],
        "bestBid": bestBid,
        "bestAsk": bestAsk
    })
    await broadcast({
        "type": "trades",
        "trades": [trade]
    })

    return JSONResponse({"status": "success", "order": order})

@app.websocket("/ws")
async def websocket_endpoint(ws: WebSocket):
    await ws.accept()
    clients.add(ws)
    await ws.send_json({
        "type": "info",
        "msg": "Connected to Matching Engine Feed",
        "symbol": "BTC-USDT",
        "bestBid": bestBid,
        "bestAsk": bestAsk
    })

    try:
        while True:
            await ws.receive_text()  # keep alive
    except Exception:
        clients.remove(ws)

async def broadcast(data):
    for ws in list(clients):
        try:
            await ws.send_json(data)
        except:
            clients.remove(ws)

if __name__ == "__main__":
    import uvicorn
    uvicorn.run("server:app", host="0.0.0.0", port=5600)
