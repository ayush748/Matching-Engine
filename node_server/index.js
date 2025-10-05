// node_server/index.js
const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const cors = require('cors');
const path = require('path');

const app = express();
app.use(cors());
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

let bestBid = 0;
let bestAsk = 0;
let trades = [];

// --- REST endpoint to submit orders ---
app.post('/submit_order', (req, res) => {
    const order = req.body;
    console.log('📥 Received order:', order);

    // Update best bid/ask logic
    if (order.side === 'BUY') {
        if (order.price > bestBid) bestBid = order.price;
    } else if (order.side === 'SELL') {
        if (bestAsk === 0 || order.price < bestAsk) bestAsk = order.price;
    }

    // Generate fake trade event (for demo)
    const trade = {
        trade_id: Date.now(),
        symbol: order.symbol,
        price: order.price,
        quantity: order.quantity,
        aggressor_side: order.side
    };
    trades.unshift(trade);

    broadcast({
        type: 'bbo',
        symbol: order.symbol,
        bestBid,
        bestAsk
    });

    broadcast({
        type: 'trades',
        trades: [trade]
    });

    res.json({ status: 'success', order });
});

// --- WebSocket setup ---
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

wss.on('connection', ws => {
    console.log('✅ WebSocket client connected');
    ws.send(JSON.stringify({
        msg: 'Connected to Matching Engine Feed',
        symbol: 'BTC-USDT',
        bestBid,
        bestAsk
    }));
});

function broadcast(data) {
    wss.clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(data));
        }
    });
}

const PORT = 5500;
server.listen(PORT, () => console.log(`🚀 Node server running at http://localhost:${PORT}`));
