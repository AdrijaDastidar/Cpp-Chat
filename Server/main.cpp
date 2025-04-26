// Server.cpp
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <windows.h>

using namespace std;

bool initializeWinsock() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData); 
    if (result != 0) {
        cout << "WSAStartup failed: " << result << endl;
        return false;
    }
    return true;
}

int main() {
    initializeWinsock();
    cout << "Winsock initialized successfully." << endl;

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    cout << "Socket created successfully." << endl;

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1000);
    serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Bind failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Bind successful." << endl;

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        cout << "Listen failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    cout << "Listening on port 1000." << endl;

    cout << "Waiting for a client to connect..." << endl;
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Accept failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    cout << "Client connected." << endl;

    char buffer[1024];
    while (true) {
        ZeroMemory(buffer, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cout << "Client disconnected." << endl;
            break;
        }
        cout << "Client: " << string(buffer, bytesReceived) << endl;

        cout << "You: ";
        string message;
        getline(cin, message);
        if (message == "exit") {
            break;
        }
        send(clientSocket, message.c_str(), message.size(), 0);
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    cout << "Server shutdown." << endl;
    return 0;
}
