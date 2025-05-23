# 🌐 **C++ TCP Chat Application** 💬

This project demonstrates a simple chat application using **TCP sockets** in **C++** with the **Windows Socket API (Winsock)**. The application consists of two components: the **Client** and the **Server**. The client connects to the server, and both parties can send and receive messages in real-time.

---

## 🖥️ **Requirements**

- **Windows OS**: The application uses the Winsock API, which is specific to Windows.
- **Microsoft Visual Studio** or any C++ compiler that supports Winsock (e.g., MinGW with the necessary libraries).
- **Port 1000** must be open for both client and server communication.

---

## 🚀 **Project Files**

- `Client.cpp`: A console-based client application that connects to the server.
- `Server.cpp`: A console-based server application that listens for incoming connections and communicates with the client.

---

## ✨ **Features**

- 🖧 **Server**: Listens for incoming connections on port 1000 and can handle one client at a time.
- 💻 **Client**: Connects to the server on `127.0.0.1` (localhost) and allows the user to send and receive messages.
- 💬 **Communication**: Uses a simple text-based communication where the user can send a message and receive a response in real-time.
- 🚪 **Exit Command**: Both client and server can close the connection and shut down the application by typing `exit`.

---

## 🛠️ **Setup**

1. **Compile and Build:**
   - Open both `Client.cpp` and `Server.cpp` in your preferred C++ IDE (e.g., Microsoft Visual Studio) or compiler.
   - Make sure that you link against `ws2_32.lib` (the Winsock library) to use the Winsock functions.
   - Ensure that your compiler supports Winsock (typically available on Windows platforms).
   
2. **Run the Server:**
   - Compile and run the `Server.cpp` file first.
   - The server will start listening on port 1000 and will wait for a connection.

3. **Run the Client:**
   - Compile and run the `Client.cpp` file after the server is running.
   - The client will connect to the server, and both parties can start chatting.

---

## 🔧 **How It Works**

### **Server Side:**
1. Initializes Winsock. 🛠️
2. Creates a TCP socket using `socket()`. 🌐
3. Binds the socket to port 1000 and starts listening for incoming connections. 🔊
4. When a client connects, it accepts the connection and enters a loop to send/receive messages. 📨
5. Shuts down when the user types `exit`. 🚪

### **Client Side:**
1. Initializes Winsock. 🛠️
2. Creates a TCP socket using `socket()`. 🌐
3. Connects to the server at `127.0.0.1` on port 1000. 🔗
4. Enters a loop to send messages to the server and receive responses. 📝
5. Shuts down when the user types `exit`. 🚪

---

## ✨ **Concluding Notes**

* This application only supports communication between **one client** and **one server**.
* To extend it, you could add:

  * 🌍 **Multi-client support**.
  * 📁 **File transfers**.
  * 🔒 **Encryption** for secure communication.
* You can change the **port number** or **IP address** to connect over a network.

---
