#1. 基础文本文件读取
#方法 1：一次性读取全部内容
#python
#复制
with open('example.txt', 'r', encoding='utf-8') as file:
    content = file.read()  # 读取全部内容为字符串
print(content)
#方法 2：逐行读取（推荐大文件）
#python
#复制
with open('example.txt', 'r', encoding='utf-8') as file:
    for line in file:      # 逐行迭代，内存友好
        print(line.strip())  # strip() 去除行尾换行符
#方法 3：读取所有行到列表
#python
#复制
with open('example.txt', 'r', encoding='utf-8') as file:
    lines = file.readlines()  # 返回列表，每行一个元素
print(lines)
#2. 二进制文件读取
#python
#复制
with open('image.png', 'rb') as file:  # 'rb' 表示二进制模式
    binary_data = file.read()
    # 处理二进制数据（如图片、音频等）
#3. 高级文件操作
#按指定编码读取（解决乱码问题）
#python
#复制
with open('example.txt', 'r', encoding='gbk') as file:  # 中文编码
    content = file.read()
#读取特定字节数
#python
#复制
with open('example.txt', 'r') as file:
    chunk = file.read(1024)  # 读取前1024个字符
#使用 seek 和 tell 控制读取位置
#python
#复制
with open('example.txt', 'r') as file:
    file.seek(10)  # 跳过前10个字节
    print(file.tell())  # 输出当前指针位置
    data = file.read(5)  # 读取接下来的5个字符
#4. 异常处理
#python
#复制
try:
    with open('nonexistent.txt', 'r') as file:
        content = file.read()
except FileNotFoundError:
    print("文件不存在！")
except UnicodeDecodeError:
    print("文件编码错误！")
except Exception as e:
    print(f"未知错误: {e}")
#5. 大文件高效读取
#分块读取（内存优化）
#python
#复制
chunk_size = 1024 * 1024  # 每次读取1MB
with open('large_file.txt', 'r') as file:
    while True:
        chunk = file.read(chunk_size)
        if not chunk:  # 读取结束
            break
        process(chunk)  # 处理每一块数据
#使用 iter 优化逐行读取
#python
#复制
with open('large_file.txt', 'r') as file:
    for line in iter(file.readline, ''):  # 更高效的逐行
        process(line)
#6. 实际应用示例
#统计文件行数
#python
#复制
with open('data.txt', 'r') as file:
    line_count = sum(1 for _ in file)
print(f"总行数: {line_count}")
#读取 CSV 文件（无需第三方库）
#python
#复制
with open('data.csv', 'r') as file:
    for line in file:
        row = line.strip().split(',')  # 简单分割
        print(row)
#读取 JSON 文件
#python
#复制
import json
with open('data.json', 'r') as file:
    data = json.load(file)  # 直接解析为字典/列表
print(data)