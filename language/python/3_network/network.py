import socket

# 创建 TCP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # 避免端口占用

# 绑定地址和端口
server_socket.bind(('0.0.0.0', 8080))  # 监听所有网卡
server_socket.listen(5)  # 开始监听，允许5个连接排队
print("TCP Server listening on port 8080...")

# 接受客户端连接
client_socket, client_addr = server_socket.accept()
print(f"Client connected from {client_addr}")

# 接收和发送数据
data = client_socket.recv(1024)  # 最多接收1024字节
print(f"Received: {data.decode('utf-8')}")
client_socket.send(b"Hello from TCP Server!")

# 关闭连接
client_socket.close()
server_socket.close()

#========================
# TCP客户端
import socket

# 创建 TCP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 连接服务器
client_socket.connect(('127.0.0.1', 8080))  # 服务器IP和端口

# 发送和接收数据
client_socket.send(b"Hello from TCP Client!")
data = client_socket.recv(1024)
print(f"Server reply: {data.decode('utf-8')}")

# 关闭连接
client_socket.close()


#========================
# 创建 UDP socket
import socket

udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_socket.bind(('0.0.0.0', 8080))  # 绑定端口
print("UDP Server listening on port 8080...")

# 接收和发送数据
data, client_addr = udp_socket.recvfrom(1024)  # 返回数据和客户端地址
print(f"Received from {client_addr}: {data.decode('utf-8')}")
udp_socket.sendto(b"Hello from UDP Server!", client_addr)  # 发送到指定地址

# 关闭socket (UDP无需显式关闭连接)
udp_socket.close()


#========================
# 创建 UDP socket
import socket

udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 发送和接收数据
server_addr = ('127.0.0.1', 8080)
udp_socket.sendto(b"Hello from UDP Client!", server_addr)
data, _ = udp_socket.recvfrom(1024)  # 忽略返回的地址
print(f"Server reply: {data.decode('utf-8')}")

# 关闭socket
udp_socket.close()