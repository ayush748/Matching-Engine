# ⚡ Multi-Language Matching Engine

The **Multi-Language Matching Engine** is a high-performance trading system that simulates the internal operations of a modern financial exchange. It processes buy and sell orders in real time using a powerful hybrid stack of **C++**, **Python**, and **JavaScript**.

Each component is written in the language best suited for its role. **C++** handles performance-critical logic, including the matching algorithm, trade persistence, and authentication. **Python** acts as a WebSocket bridge between the backend and frontend, enabling real-time data streaming. **JavaScript and HTML** provide a clean, interactive web interface for users to submit and monitor orders.  

The primary goal of this project is to demonstrate how multiple languages can form a cohesive architecture that achieves both high speed and user interactivity. It makes the complex reality of financial trading systems accessible, educational, and modular for future development.

---

## 🧠 System Overview

The system follows a **three-layer architecture**: the frontend, a Python WebSocket bridge, and a C++ backend.  
The **frontend** serves as the user’s entry point with an order form to place buy or sell orders, specifying price, quantity, and order type.  

The **Python layer**, built with **FastAPI** and **asyncio**, serves as the communication hub. It manages client connections, validates incoming JSON orders, and relays them to the C++ engine. When the engine processes an order, this layer broadcasts the result (like trade confirmations and order book updates) to all connected clients.  

The **C++ Core Matching Engine** is the computational heart of the system. It maintains bid and ask books for active buy and sell orders. Orders are matched using strict price-time priority—better prices and earlier timestamps execute first. The entire loop, from order submission to confirmation, occurs in milliseconds.


---

## ⚙️ Core Functionality

### 🧩 C++ Core Engine  
The **C++ core** processes all orders and maintains the order book. When buy and sell orders match, a trade is generated and executed immediately. All activity is logged via `logger.hpp`, and state changes are saved by `persistence.hpp` to preserve data consistency. The authentication module ensures that users are validated before interacting with the market.

### 🐍 Python WebSocket Server  
The **Python server** acts as a real-time data bridge. Built with **FastAPI** and **asyncio**, it can handle multiple concurrent clients simultaneously. It receives JSON orders, forwards them to the C++ engine, and pushes updates like executed trades, bid/ask changes, and user confirmations back to clients instantly.

### 💻 Frontend Dashboard  
The **frontend** (HTML + JS) provides an interactive, responsive dashboard. It connects automatically to the WebSocket endpoint, allowing users to submit buy/sell orders, view live trades, and monitor the current market depth. The interface updates in real time, mirroring professional trading platforms.

---

## 🚀 Getting Started

### Prerequisites
You’ll need the following tools installed:
- A C++ compiler (e.g., GCC or Clang)
- CMake (v3.10+)
- Python 3.8+ and Pip
- Node.js and NPM (for optional Node server)

### Installation Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/your-username/matching-engine.git
   cd matching-engine
# 🚀 Build the C++ Core Engine
mkdir build
cd build
cmake ..
make
cd ..

# 🧠 Set up the Python WebSocket Server
cd python_server
pip install -r requirements.txt

# ⚙️ Run the Application

# 1️⃣ Start the C++ Engine
./build/matching_engine

# 2️⃣ Start the Python Server
python python_server/server.py

# 3️⃣ Launch the Frontend
# Open the following file in your web browser:
node_server/public/index.html



## 🧩 System Architecture

This ASCII-style diagram shows the real-time data flow across the system, representing how frontend actions reach the backend engine and return live updates.

