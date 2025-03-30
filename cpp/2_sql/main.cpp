//C++链接MySQL需要使用Connector/C++
// #include <mysql/mysql.h> // Linux
// #include <mysql.h>    // Windows
#include <iostream>

int main() {
    MYSQL *conn;          // MySQL 连接句柄
    MYSQL_RES *res;       // 查询结果集
    MYSQL_ROW row;        // 行数据

    // 初始化连接
    conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "MySQL 初始化失败" << std::endl;
        return 1;
    }

    // 连接数据库（参数：主机, 用户名, 密码, 数据库名, 端口, Unix套接字, 标志）
    if (!mysql_real_connect(conn, "localhost", "root", "password", "testdb", 3306, nullptr, 0)) {
        std::cerr << "连接失败: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 执行查询
    if (mysql_query(conn, "SELECT * FROM users")) {
        std::cerr << "查询失败: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 获取结果集
    res = mysql_use_result(conn);

    // 遍历结果
    while ((row = mysql_fetch_row(res)) != nullptr) {
        std::cout << "ID: " << row[0] << ", Name: " << row[1] << std::endl;
    }

    // 释放资源
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

/*
1.链接失败
检查MySQL服务是否运行
2.找不到头文件
确认是否正确配置路径
3.字符编码问题
连接时指定编码
mysql_options(conn, MYSQL_SET_CHARSET_NAME, "utf8mb4");
 */