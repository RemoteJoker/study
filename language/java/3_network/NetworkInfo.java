import java.net.InetAddress;

public class NetworkInfo {
    public static void main(String[] args) throws Exception {
        InetAddress localHost = InetAddress.getLocalHost();
        System.out.println("本机IP: " + localHost.getHostAddress());
        System.out.println("主机名: " + localHost.getHostName());

        InetAddress google = InetAddress.getByName("www.google.com");
        System.out.println("Google IP: " + google.getHostAddress());
    }
}

//TCP Socket 通信
// 服务端（Server）
// java
// 复制
import java.net.*;
import java.io.*;

public class TCPServer {
    public static void main(String[] args) throws IOException {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("服务器启动，等待连接...");
            Socket clientSocket = serverSocket.accept(); // 阻塞等待客户端连接

            BufferedReader in = new BufferedReader(
                new InputStreamReader(clientSocket.getInputStream())
            );
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println("客户端: " + inputLine);
                out.println("服务器回复: " + inputLine); // 回传数据
            }
        }
    }
}
// 客户端（Client）
// java
// 复制
import java.net.*;
import java.io.*;

public class TCPClient {
    public static void main(String[] args) throws IOException {
        try (Socket socket = new Socket("localhost", 8080)) {
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(
                new InputStreamReader(socket.getInputStream())
            );

            out.println("Hello, Server!"); // 发送消息
            System.out.println("服务器回复: " + in.readLine()); // 接收回复
        }
    }
}

// UDP 通信
// 服务端（接收端）
// java
// 复制
import java.net.*;

public class UDPServer {
    public static void main(String[] args) throws Exception {
        DatagramSocket socket = new DatagramSocket(9090);
        byte[] buffer = new byte[1024];

        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        socket.receive(packet); // 阻塞等待数据

        String received = new String(packet.getData(), 0, packet.getLength());
        System.out.println("收到UDP消息: " + received);
        socket.close();
    }
}
// 客户端（发送端）
// java
// 复制
import java.net.*;

public class UDPClient {
    public static void main(String[] args) throws Exception {
        DatagramSocket socket = new DatagramSocket();
        String message = "Hello, UDP Server!";
        byte[] data = message.getBytes();

        DatagramPacket packet = new DatagramPacket(
            data, data.length,
            InetAddress.getByName("localhost"), 9090
        );
        socket.send(packet);
        System.out.println("UDP消息已发送");
        socket.close();
    }
}

// 2. HTTP 请求
// (1) 使用 HttpURLConnection（Java 原生）
// java
// 复制
import java.net.*;
import java.io.*;

public class HttpRequestExample {
    public static void main(String[] args) throws Exception {
        URL url = new URL("https://jsonplaceholder.typicode.com/posts/1");
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");

        BufferedReader in = new BufferedReader(
            new InputStreamReader(conn.getInputStream())
        );
        String line;
        StringBuilder response = new StringBuilder();
        while ((line = in.readLine()) != null) {
            response.append(line);
        }
        in.close();

        System.out.println("HTTP 响应: " + response);
    }
}
// (2) 使用 HttpClient（Java 11+ 推荐）
// java
// 复制
import java.net.http.*;
import java.net.URI;

public class HttpClientExample {
    public static void main(String[] args) throws Exception {
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder()
            .uri(URI.create("https://jsonplaceholder.typicode.com/posts/1"))
            .GET()
            .build();

        HttpResponse<String> response = client.send(
            request, HttpResponse.BodyHandlers.ofString()
        );
        System.out.println("HTTP 响应: " + response.body());
    }
}

// 3. 多线程网络编程
// 多线程 TCP 服务器（支持多个客户端）
// java
// 复制
import java.net.*;
import java.io.*;

public class MultiThreadedServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("服务器启动，等待连接...");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(() -> handleClient(clientSocket)).start();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (
            BufferedReader in = new BufferedReader(
                new InputStreamReader(clientSocket.getInputStream())
            );
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)
        ) {
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println("客户端[" + clientSocket + "]: " + inputLine);
                out.println("服务器回复: " + inputLine);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}