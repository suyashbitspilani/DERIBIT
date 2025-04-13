# 🚀 DeriBot C++ — High-Performance Order Management System

This is a C++-based, low-latency Order Execution and Management System built to trade on the [Deribit Testnet](https://test.deribit.com).  
It supports Spot, Futures, and Options trading, with real-time WebSocket streaming and a client subscription mechanism.

---

## 🎯 Assignment Objectives

- ✅ Place, modify, cancel orders
- ✅ Real-time market data via WebSocket
- ✅ Orderbook fetching
- ✅ Current position tracking
- ✅ Client subscription via WebSocket server
- ✅ Low-latency design with multithreading & performance in mind

---

## ⚙️ Tech Stack

- C++17
- Deribit REST & WebSocket APIs
- WebSocket++ (server)
- Boost, Asio, OpenSSL
- nlohmann::json
- Dockerized for easy deploy

---

## 📦 Project Structure


## 🚀 How to Run

### 1. Deribit Test Setup
- Create a test account: [test.deribit.com](https://test.deribit.com)
- Go to My Account > API > Create New Key
- Replace your API credentials in:  
  `src/core/order_manager.cpp`
  ```cpp
  : apiClient_("your_client_id", "your_client_secret")
2. Build (Locally with CMake)
bash
Copy
Edit
mkdir build
cd build
cmake ..
make -j$(nproc)
./deribot
3. Run with Docker 🐳
bash
Copy
Edit
docker build -t deribot .
docker run -p 9002:9002 deribot
4. Test WebSocket Server
bash
Copy
Edit
pip install websocket-client
python client.py
✅ Output will show real-time market data from Deribit streamed via your C++ WebSocket server.

🧠 Bonus Section (Performance & Optimization)
🔍 Custom mutex-based logger (thread-safe)

🧵 Multithreaded architecture: dedicated thread for broadcast

📉 Low-latency goals via:

Preallocated data structures

Minimal JSON parsing

No blocking I/O

⏱️ Future additions:

Latency benchmarking tools

Order loop time profiler

High-performance queues

🎥 Deliverables
✅ Full source code

✅ Dockerfile

✅ Working WebSocket demo (client.py)

🎥 You should record a demo video covering:

App flow (start → stream → client subscribe)

Code structure walkthrough

Order placement/cancellation

👨‍💻 Author
Suyash// Placeholder for README.md
