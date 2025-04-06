#include <iostream>
#include <fstream>  // 文件流操作
#include <string>   // 用于处理字符串

//1字节对齐
#pragma pack(1)
struct Data {
    int id;
    double value;
};
#pragma pack()

int main() {
    //文本文件读取
    std::ifstream file("example.txt");  // 打开文件

    if (!file.is_open()) {
        std::cerr << "无法打开文件！" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {  // 逐行读取
        std::cout << line << std::endl;
    }

    file.close();  // 显式关闭文件（析构函数也会自动关闭）
    //二进制文件读取
    std::ifstream bin_file("data.bin", std::ios::binary);
    Data data;
    
    if (bin_file.read(reinterpret_cast<char*>(&data), sizeof(data))) {
        std::cout << "ID: " << data.id << ", Value: " << data.value;
    } else {
        std::cerr << "二进制读取失败！";
    }

    bin_file.close();
    return 0;
}