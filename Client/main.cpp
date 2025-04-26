#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <thread>

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

void sent(SOCKET s) {
    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    string msg;
    while(1){
        cout << "Enter message: ";
        getline(cin, msg);
        if (msg == "exit") {
            break;
        }
        string sendData = name + ": " + msg;
        send(s, sendData.c_str(), sendData.size(), 0);
        cout << "Sent data: " << sendData << endl;
    }
    closesocket(s);
    WSACleanup();
    cout << "Socket closed." << endl;
}
void rec(SOCKET s) {
    char buffer[1024] = {0};
    while (true) {
        int bytesReceived = recv(s, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cout << "Server disconnected." << endl;
            break;
        }
        string receivedData(buffer, bytesReceived);
        cout << "Received data: " << receivedData << endl;
    }
    closesocket(s); 
    WSACleanup();
    cout << "Socket closed." << endl;
}

int main() {
    initializeWinsock();
    cout << "Winsock initialized successfully." << endl;

    SOCKET s;
    string serverIP = "127.0.0.1";
    int serverPort = 1000; 
    
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        cout << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup(); 
        return 1;
    }
    cout << "Socket created successfully." << endl;

    // Set up the server address structure
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);

    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    
    connect(s, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    cout << "Connected to server at " << serverIP << ":" << serverPort << endl;
    
    thread sender(sent);
    thread receiver(rec);
    sender.detach();
    receiver.detach();
    return 0;
}