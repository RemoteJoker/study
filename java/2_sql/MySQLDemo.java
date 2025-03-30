import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class MySQLDemo {
    public static void main(String[] args) {
        // JDBC 连接信息
        String url = "jdbc:mysql://localhost:3306/testdb?useSSL=false&serverTimezone=UTC";
        String username = "root";
        String password = "yourpassword";

        try {
            // 1. 注册驱动（MySQL 8.0+ 可省略，通过 SPI 自动加载）
            Class.forName("com.mysql.cj.jdbc.Driver");

            // 2. 建立连接
            Connection connection = DriverManager.getConnection(url, username, password);
            System.out.println("连接成功！");

            // 3. 关闭连接
            connection.close();
        } catch (ClassNotFoundException e) {
            System.err.println("找不到驱动类：" + e.getMessage());
        } catch (SQLException e) {
            System.err.println("数据库连接失败：" + e.getMessage());
        }
    }
}

import java.sql.*;

public class QueryDemo {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/testdb";
        String username = "root";
        String password = "yourpassword";

        try (Connection conn = DriverManager.getConnection(url, username, password);
             Statement stmt = conn.createStatement()) {

            // 执行查询
            ResultSet rs = stmt.executeQuery("SELECT id, name FROM users");

            // 遍历结果集
            while (rs.next()) {
                int id = rs.getInt("id");
                String name = rs.getString("name");
                System.out.println("ID: " + id + ", Name: " + name);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}