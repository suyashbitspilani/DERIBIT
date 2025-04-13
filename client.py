import websocket
import threading
import time
import json

SERVER_URL = "ws://localhost:9002"  

def on_message(ws, message):
    try:
        data = json.loads(message)
        print("📥 Market Data:", json.dumps(data, indent=2))
    except json.JSONDecodeError:
        print("📨 Message:", message)

def on_error(ws, error):
    print("❌ Error:", error)

def on_close(ws, close_status_code, close_msg):
    print("🔌 Disconnected")

def on_open(ws):
    def run():
        print("✅ Connected to WebSocket Server")
        symbol = "BTC-PERPETUAL"
        print(f"📤 Subscribing to {symbol}")
        ws.send(f"SUBSCRIBE:{symbol}")
    threading.Thread(target=run).start()

if __name__ == "__main__":
    websocket.enableTrace(True)
    ws = websocket.WebSocketApp(SERVER_URL,
                                on_open=on_open,
                                on_message=on_message,
                                on_error=on_error,
                                on_close=on_close)
    ws.run_forever()

