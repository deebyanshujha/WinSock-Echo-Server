# EchoNet – TCP Socket Server in C++

A simple TCP-based Echo Server built using the Windows WinSock API in C++.

The server accepts client connections, receives messages from clients, and sends the same message back in real time.

---

## Features

- TCP socket communication
- Real-time message handling
- Echoes client messages back
- Displays connected client IP and port
- Handles client disconnection
- Built completely in C++

---

## Technologies Used

- C++
- WinSock2
- TCP/IP Networking
- Windows Socket API

---

## How It Works

```text
CLIENT → SERVER
        recv()

SERVER → CLIENT
        send()
```

The server:
1. Creates a socket
2. Binds it to a port
3. Listens for incoming connections
4. Accepts client connections
5. Receives data using `recv()`
6. Sends the same data back using `send()`

---

## Project Structure

```text
EchoNet/
│
├── server.cpp
└── README.md
```

---

## Requirements

- Windows OS
- MinGW / g++
- WinSock Library

---

## Compile

```bash
g++ server.cpp -o server -lws2_32
```

---

## Run

```bash
./server
```

The server runs on:

```text
Port: 54000
```

---

## Example Output

```text
192.168.1.5 connected on port 54000

Hello Server
Hello Server

Client disconnected
```

---

## Concepts Learned

- Socket Programming
- TCP/IP Communication
- Client-Server Architecture
- Data Transmission using `send()` and `recv()`
- Winsock Initialization
- Network Byte Order
- Buffer Management

---

## Future Improvements

- Multi-client support
- Chat application
- GUI client
- File transfer support
- WebSocket implementation
- SSL/TLS encryption

---

## Author

Deebyanshu Jha  
B.Tech CSE (IoT) – VIT Vellore
