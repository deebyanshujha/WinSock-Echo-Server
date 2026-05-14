#define _WIN32_WINNT 0x0601

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstring>

/*
ws2tcpip.h provides declarations for modern TCP/IP networking
functions and structures used in socket programming.
*/

// Links the Winsock networking library
#pragma comment(lib, "ws2_32.lib")

using namespace std;

// CLIENT ←→ SOCKET ←→ NETWORK ←→ SOCKET ←→ SERVER
//
// Example:
// 192.168.1.10 : 8080
//
// 192.168.1.10 → IP Address
// 8080         → Port Number
//
// Together they form a socket endpoint.

int main()
{
    // =========================
    // INITIALIZE WINSOCK
    // =========================

    WSADATA wsData;

    // MAKEWORD(2,2) requests Winsock version 2.2
    WORD ver = MAKEWORD(2, 2);

    // WSAStartup() initializes Winsock library for socket usage
    int wsOk = WSAStartup(ver, &wsData);

    if(wsOk != 0)
    {
        cerr << "Can't initialize Winsock! Quitting" << endl;
        return 0;
    }

    // =========================
    // CREATE SOCKET
    // =========================

    /*
    socket()

    AF_INET     -> IPv4 addressing
    SOCK_STREAM -> TCP protocol
    0           -> Automatically choose TCP
    */

    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

    // INVALID_SOCKET means socket creation failed
    if(listening == INVALID_SOCKET)
    {
        cerr << "Can't create socket! Quitting" << endl;
        return 0;
    }

    // =========================
    // BIND IP ADDRESS & PORT
    // =========================

    sockaddr_in hint;

    // AF_INET specifies IPv4
    hint.sin_family = AF_INET;

    // htons() converts port number into network byte order
    hint.sin_port = htons(54000);

    /*
    INADDR_ANY allows server to accept connections
    from any available network interface
    */
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    /*
    bind()

    Attaches IP address and port number
    to the socket
    */

    if(bind(listening, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
    {
        cerr << "Bind failed!" << endl;
        return 0;
    }

    // =========================
    // START LISTENING
    // =========================

    /*
    listen()

    Marks socket as a listening socket
    waiting for incoming client connections

    SOMAXCONN -> maximum allowed waiting connections
    */
    listen(listening, SOMAXCONN);

    // =========================
    // WAIT FOR CLIENT CONNECTION
    // =========================

    sockaddr_in client;
    int clientSize = sizeof(client);

    /*
    accept()

    Waits for a client to connect and creates
    a new socket dedicated to that client
    */
    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    // =========================
    // GET CLIENT INFORMATION
    // =========================

    // Stores client's hostname/IP
    char host[NI_MAXHOST];

    // Stores client's port/service
    char service[NI_MAXSERV];

    // ZeroMemory() clears memory by filling with zeros
    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXSERV);

    /*
    getnameinfo()

    Converts client's raw socket address
    into readable hostname/IP and port number
    */
    if(getnameinfo((sockaddr*)&client,
                   sizeof(client),
                   host,
                   NI_MAXHOST,
                   service,
                   NI_MAXSERV,
                   0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        /*
        inet_ntoa()

        Converts binary IP address into
        readable string format
        */
        strcpy(host, inet_ntoa(client.sin_addr));

        cout << host << " connected" << endl;
    }

    // =========================
    // CLOSE LISTENING SOCKET
    // =========================

    /*
    closesocket()

    Closes the listening socket because
    we already accepted one client
    */
    closesocket(listening);

    // =========================
    // RECEIVE & SEND DATA
    // =========================

    char buf[4096];

    while(true)
    {
        // Clear buffer memory
        ZeroMemory(buf, 4096);

        /*
        recv()

        Waits for client to send data
        and stores it inside buffer
        */
        int bytesReceived = recv(clientSocket, buf, 4096, 0);

        // SOCKET_ERROR means recv() failed
        if(bytesReceived == SOCKET_ERROR)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }

        // recv() returns 0 when client disconnects
        if(bytesReceived == 0)
        {
            cout << "Client disconnected" << endl;
            break;
        }

        /*
        send()

        Sends data back to the connected client

        This creates an ECHO SERVER because
        server sends back the same message received
        */
        send(clientSocket, buf, bytesReceived, 0);
    }

    // =========================
    // CLEANUP
    // =========================

    // Close client socket
    closesocket(clientSocket);

    // Shutdown Winsock library
    WSACleanup();

    return 0;
}