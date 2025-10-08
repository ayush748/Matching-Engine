# ⚡ Multi-Language Matching Engine

The **Multi-Language Matching Engine** is a high-performance trading system that simulates the internal operations of a modern financial exchange. It processes buy and sell orders in real time using a powerful hybrid stack of **C++**, **Python**, and **JavaScript**.

Each component is written in the language best suited for its role:  
- **C++** handles performance-critical logic — the matching algorithm, trade persistence, and authentication.  
- **Python** acts as a **WebSocket bridge** between the backend and frontend, enabling real-time data streaming.  
- **JavaScript + HTML** provide an interactive web interface for users to submit and monitor orders.  

The primary goal of this project is to demonstrate how multiple languages can form a cohesive architecture that achieves both **high speed** and **user interactivity** — making the complex reality of financial trading systems **accessible**, **educational**, and **modular**.

---

## 🧠 System Overview

The system follows a **three-layer architecture**: the **Frontend**, **Python WebSocket Bridge**, and **C++ Core Engine**.

- 🖥️ **Frontend** — Provides an order form to place buy/sell orders, specifying price, quantity, and order type.  
- 🧩 **Python Layer (FastAPI + asyncio)** — Manages client connections, validates incoming JSON orders, and relays them to the C++ engine. It also broadcasts trade confirmations and order book updates to all connected clients.  
- ⚙️ **C++ Core Matching Engine** — Maintains bid and ask books for active orders. Orders are matched using strict **price-time priority** (better price and earlier timestamp get executed first). The entire loop from submission to confirmation occurs within milliseconds.

---

## ⚙️ Core Functionality

### 🧩 C++ Core Engine
The **C++ Core** processes all orders and maintains the order book. When buy and sell orders match, a trade is generated and executed immediately.  
- Logging handled via `logger.hpp`  
- State persistence handled by `persistence.hpp`  
- Secure authentication for users before interaction with the market  

### 🐍 Python WebSocket Server
Built using **FastAPI** and **asyncio**, the Python layer serves as a **real-time data bridge**.  
It:
- Accepts JSON orders from clients  
- Forwards them to the C++ core  
- Sends real-time updates (trades, bids, asks, confirmations) to all connected clients  

### 💻 Frontend Dashboard
The **HTML + JS dashboard** provides a clean and responsive interface:  
- Submit buy/sell orders  
- View live trades and market depth  
- Updates automatically in real-time through WebSocket connections  

---

## 🚀 Getting Started

### 🧰 Prerequisites
Ensure the following are installed:
- A **C++ compiler** (e.g., GCC or Clang)  
- **CMake** (v3.10 or higher)  
- **Python 3.8+** and **Pip**  
- **Node.js** and **NPM** *(optional for Node server)*  

---

### 🏗️ Installation Steps

#### 1️⃣ Clone the Repository
```bash
git clone https://github.com/your-username/matching-engine.git
cd matching-engine

```

### 🏗️ Build the C++ Core Engine
```bash
mkdir build
cd build
cmake ..
make
cd ..
```



### 🏗️ Set up the Python WebSocket Server
```bash
cd python_server
pip install -r requirements.txt
```


### 🏗️ Set up the Python WebSocket Server
```bash
- Start the C++ Engine:

./build/matching_engine


- Start the Python Server:

python python_server/server.py
```

### 📈 Usage
 #### 1. Frontend Dashboard

The index.html dashboard provides an interactive UI for placing and tracking orders.
It includes:

- BBO (Best Bid Offer): Shows the best buy/sell prices in real time.

- Place Order: Submit buy or sell orders with price and quantity inputs.

- Recent Trades: Displays executed trade history with price, volume, and direction.

(You can include a screenshot here, e.g.:)


#### 2. Python WebSocket Server Logs

The server console shows all incoming WebSocket events and responses, confirming successful connections and order submissions. Each log line includes order details like side, type, and execution results.

(You can include a sample image, e.g.:)


### 3. API Submission (via Postman)

Orders can also be placed directly via HTTP POST requests.
Example endpoint:

```bash

POST http://127.0.0.1:5600/submit_order
```

``` bash
Payload:

{
  "symbol": "AAPL",
  "side": "BUY",
  "price": 150.25,
  "quantity": 100
}

```
(Sample image placeholder:)


### 🧱 File Structure
```bash
📦 matching-engine/

📁 build

📁 include
├─ 📄 json.hpp
├─ 📄 logger.hpp
├─ 📄 matching_engine.hpp
├─ 📄 order_book.hpp
├─ 📄 order.hpp
├─ 📄 persistence.hpp
├─ 📄 trade.hpp
└─ 📄 utils.hpp

📁 node_server
├─ 📁 build
├─ 📁 node_modules
├─ 📁 public
│  └─ 📄 index.html
├─ 📄 binding.ccp
├─ 📄 binding.gyp
├─ 📄 index.js
├─ 📄 package-lock.json
├─ 📄 package.json
├─ 📄 README.md
├─ 📄 server-err.log
└─ 📄 server-out.log

📁 python_server
├─ 📁 __pycache__
├─ 📁 static
├─ 📄 requirements.txt
└─ 📄 server.py

📁 src
├─ 📄 main.cpp
├─ 📄 matching_engine.cpp
├─ 📄 order_book.cpp
├─ 📄 order.cpp
├─ 📄 persistence.cpp
├─ 📄 trade.cpp

📄 CMakeLists.txt
📄 matching_engine.exe
📄 package-lock.json


```
### ⚡ Performance and Design Philosophy

This matching engine is designed for low latency, modularity, and real-time responsiveness. The C++ core ensures lightning-fast trade matching, while Python manages scalability and concurrent data flow. The web interface offers accessibility and live visualization.

By combining C++ for performance, Python for orchestration, and JavaScript for user experience, this project achieves the same architectural balance used in professional trading systems. Every component can evolve independently, allowing future developers to extend it into production-scale systems.

### 🧭 Future Vision

Expand into a multi-threaded distributed engine.

Integrate database persistence for order and trade history.

Add graphical analytics (candlestick charts, market depth graphs).

Support advanced order types (Iceberg, Trailing Stop, Conditional Orders).

Upgrade Python into a hybrid REST + WebSocket API system.


