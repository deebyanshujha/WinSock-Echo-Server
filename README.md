EchoNet – TCP Socket Server in C++

A simple TCP-based Echo Server built using the Windows WinSock API in C++.
The server accepts client connections, receives messages from clients, and sends the same message back in real time.

This project was created to learn:

Socket Programming
TCP/IP Networking
Client-Server Architecture
Real-time Communication
WinSock API in C++
Features
TCP socket communication
Real-time message handling
Echoes client messages back
Displays connected client IP and port
Handles client disconnection
Built completely in C++
Technologies Used
C++
WinSock2
TCP/IP Networking
Windows Socket API
How It Works
CLIENT → SERVER
        recv()

SERVER → CLIENT
        send()

The server:

Creates a socket
Binds it to a port
Listens for incoming connections
Accepts a client connection
Receives data using recv()
Sends the same data back using send()
Project Structure
EchoNet/
│
├── server.cpp
└── README.md
Setup & Run
Requirements
Windows OS
g++ / MinGW compiler
WinSock library
Compile
g++ server.cpp -o server -lws2_32
Run
./server

The server starts listening on:

Port: 54000
Example Output
192.168.1.5 connected on port 54000

Hello Server
Hello Server

Client disconnected
Concepts Learned
Socket creation
Binding IP and ports
TCP connections
Client-server communication
Data transmission
Buffer handling
Network byte order
WinSock initialization and cleanup
Future Improvements
Multi-client support using threads
Chat server functionality
GUI client application
File transfer support
WebSocket implementation
Encryption using SSL/TLS
Author

Deebyanshu Jha
