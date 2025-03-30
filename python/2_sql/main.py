#pip install mysql-connector-python

import mysql.connector

# 1. 建立连接
conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="yourpassword",
    database="testdb"
)

# 2. 创建游标
cursor = conn.cursor()

# 3. 执行查询
cursor.execute("SELECT * FROM users")

# 4. 获取结果
for row in cursor.fetchall():
    print(f"ID: {row[0]}, Name: {row[1]}")

# 5. 关闭连接
cursor.close()
conn.close()