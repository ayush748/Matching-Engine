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

## 🧩 System Architecture

This ASCII-style diagram shows the real-time data flow across the system, representing how frontend actions reach the backend engine and return live updates.

