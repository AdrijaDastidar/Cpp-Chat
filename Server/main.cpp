#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <windows.h> 
#include <thread>
#include <vector>
#include <algorithm>


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

void chat(SOCKET clientSocket, vector<SOCKET>& client) {
    char buffer[1024] = {0};
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cout << "Client disconnected." << endl;
            break;
        }
        string receivedData(buffer, bytesReceived);
        cout << "Received data: " << receivedData << endl;

        for(auto& c : client) {
            if (c != clientSocket) {
                send(c, receivedData.c_str(), receivedData.size(), 0);
            }
        }
    }
    auto it = find(client.begin(), client.end(), clientSocket);
    if (it != client.end()) {
        client.erase(it);
    }
    closesocket(clientSocket);
    cout << "Client socket closed." << endl;
    WSACleanup();
}

int main() {
    initializeWinsock();
    cout << "Winsock initialized successfully." << endl;
    
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        cout << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup(); 
        return 1;
    }
    cout << "Socket created successfully." << endl;

    // Set up the server address structure
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1000);

    serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0"); // simpler and compatible
    
    // bind
    if (bind(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Bind failed: " << WSAGetLastError() << endl;
        closesocket(sock); 
        WSACleanup(); 
        return 1;
    }

    cout << "Bind successful." << endl;

    // Listen 
    if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Listen failed: " << WSAGetLastError() << endl;
        closesocket(sock); 
        WSACleanup(); 
        return 1;
    }
    cout << "Listening on port 1000." << endl;

    vector<SOCKET> client; 


    while(1) {
        cout << "Waiting for a client to connect..." << endl;
        // Accept 
        SOCKET clientSocket = accept(sock, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            cout << "Accept failed: " << WSAGetLastError() << endl;
            closesocket(sock); 
            WSACleanup(); 
            return 1;
        }
        cout << "Client connected." << endl;
        client.push_back(clientSocket);

        thread t(chat, clientSocket, std::ref(client));
        t.detach(); 
    }
    
    // Close the client socket
    closesocket(sock);
    cout << "Client socket closed." << endl;
    WSACleanup(); 
    return 0;
}
