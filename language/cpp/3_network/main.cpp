#include <winsock2.h>  // Winsock 主头文件
#include <ws2tcpip.h>  // 用于 IPv6 和现代地址结构
#pragma comment(lib, "ws2_32.lib")  // 链接 Winsock 库

WSADATA wsaData;
if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
    return 1;
}

//=================
//TCP服务端
SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (serverSocket == INVALID_SOCKET) {
    std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
    WSACleanup();
    return 1;
}

// 绑定地址和端口
sockaddr_in serverAddr;
serverAddr.sin_family = AF_INET;
serverAddr.sin_addr.s_addr = INADDR_ANY;  // 监听所有网卡
serverAddr.sin_port = htons(8080);        // 端口号

if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
    std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
    closesocket(serverSocket);
    WSACleanup();
    return 1;
}

// 开始监听
listen(serverSocket, SOMAXCONN);

// 接受客户端连接
sockaddr_in clientAddr;
int clientAddrLen = sizeof(clientAddr);
SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
if (clientSocket == INVALID_SOCKET) {
    std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
    closesocket(serverSocket);
    WSACleanup();
    return 1;
}

// 接收和发送数据
char buffer[1024];
int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
if (bytesReceived > 0) {
    send(clientSocket, buffer, bytesReceived, 0);
}

// 关闭连接
closesocket(clientSocket);
closesocket(serverSocket);


//=================
//TCP客户端
SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (clientSocket == INVALID_SOCKET) {
    std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
    WSACleanup();
    return 1;
}

// 连接服务器
sockaddr_in serverAddr;
serverAddr.sin_family = AF_INET;
inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);  // 服务器 IP
serverAddr.sin_port = htons(8080);                      // 服务器端口

if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
    std::cerr << "Connect failed: " << WSAGetLastError() << std::endl;
    closesocket(clientSocket);
    WSACleanup();
    return 1;
}

// 发送和接收数据
const char* message = "Hello, Server!";
send(clientSocket, message, strlen(message), 0);

char buffer[1024];
recv(clientSocket, buffer, sizeof(buffer), 0);
std::cout << "Server reply: " << buffer << std::endl;

closesocket(clientSocket);


//=============
//UDP 服务器端
SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
if (udpSocket == INVALID_SOCKET) {
    std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
    WSACleanup();
    return 1;
}

// 绑定地址和端口
sockaddr_in serverAddr;
serverAddr.sin_family = AF_INET;
serverAddr.sin_addr.s_addr = INADDR_ANY;
serverAddr.sin_port = htons(8080);

if (bind(udpSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
    std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
    closesocket(udpSocket);
    WSACleanup();
    return 1;
}

// 接收和发送数据
char buffer[1024];
sockaddr_in clientAddr;
int clientAddrLen = sizeof(clientAddr);

int bytesReceived = recvfrom(udpSocket, buffer, sizeof(buffer), 0,
                            (sockaddr*)&clientAddr, &clientAddrLen);
if (bytesReceived > 0) {
    sendto(udpSocket, buffer, bytesReceived, 0,
           (sockaddr*)&clientAddr, clientAddrLen);
}

closesocket(udpSocket);


//=============
//UDP 客户端
SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
if (udpSocket == INVALID_SOCKET) {
    std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
    WSACleanup();
    return 1;
}

// 目标服务器地址
sockaddr_in serverAddr;
serverAddr.sin_family = AF_INET;
inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
serverAddr.sin_port = htons(8080);

// 发送和接收数据
const char* message = "Hello, UDP Server!";
sendto(udpSocket, message, strlen(message), 0,
       (sockaddr*)&serverAddr, sizeof(serverAddr));

char buffer[1024];
int bytesReceived = recvfrom(udpSocket, buffer, sizeof(buffer), 0, nullptr, nullptr);
if (bytesReceived > 0) {
    std::cout << "Server reply: " << buffer << std::endl;
}

closesocket(udpSocket);