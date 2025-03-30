#include <iostream>//C++标准头文件

// 检测编译器类型
#ifdef __GNUC__

#elif defined(_MSC_VER)

#elif defined(__clang__)

#elif defined(__INTEL_COMPILER)

#else

#endif

//检测操作系统
#ifdef _WIN32

#elif __linux__

#elif __APPLE__

#else

#endif

//检测当前版本
#if __STDC_VERSION__ >= 201710L

#elif __STDC_VERSION__ >= 201112L

#elif __STDC_VERSION__ >= 199901L

#else

#endif

int main(){
    //标准输入输出流
    std::cout<<"helloworld"<<std::endl;
    return 0;
}