// Client.cpp
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

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    cout << "Socket created successfully." << endl;

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Connection failed: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    cout << "Connected to server." << endl;

    char buffer[1024];
    while (true) {
        cout << "You: ";
        string message;
        getline(cin, message);
        if (message == "exit") {
            break;
        }
        send(clientSocket, message.c_str(), message.size(), 0);

        ZeroMemory(buffer, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cout << "Server disconnected." << endl;
            break;
        }
        cout << "Server: " << string(buffer, bytesReceived) << endl;
    }

    closesocket(clientSocket);
    WSACleanup();
    cout << "Client shutdown." << endl;
    return 0;
}
