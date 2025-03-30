1.使用Qt注意事项
Qt是由商业公司控制，如果是 [个人] 想使用，请看清楚Qt公司的开源版本协议。
2.Qt不是语言
Qt本质上是一个框架，我举个例子

正常写C++程序:
源代码(原生C++)->编译器->可执行文件
当你使用Qt时:
源代码(原生C++  +  Qt封装的函数)->经过Qt的处理->编译器->可执行文件

如果想提升Qt水平，请先提高C++水平

3.Qt框架是由很多模块组成的，最基本的模块有三个
①core:核心模块，最基本的功能都封装在里面
②widget:高层用户组件界面
③gui:底层图形接口

可以看出，Qt最大的优点是 "界面"。如果不想做带的界面应用，Qt也并不是好的选择

4.Qt一些常用的但新手不清楚的用法
①添加exe的图标。
当用户在代码中使用setwindowicon函数来指导exe图标时，其指定的是运行起来的进程的图标-而不是在硬盘中躺着不动的程序的图标。
如果想一劳永逸的指定图标，就要在qmake文件中去指定ICON= xx.ico；
②数据库问题
在开源版的Qt中用户无法使用MySQL数据库，因为Qt公司没有编译它的驱动。用户需要手动编译它，在这里我推荐一个博主:爱编程的大丙
这个博主的教程详细的说明了如何编译，并且指明白了可能失败的原因。在此我要点个好评
③静态编译问题
用户可能不喜欢Qt在打包时拖家带口的情况，这时就需要静态编译了，编译方法网上很多我不做赘述，我只提醒要注意协议，如果是商业
盈利的项目请不要使用静态编译，自己玩的随便。
④编译器和字符编码的问题
Qt在Windows下可以使用MinGw和MSVC两种编译器(Linux只有MinGw，MacOS我还没用过)。当你使用MSVC时记得在qmake中指定字符编码
否则会出现乱码现象
⑤Qt做好看的界面
Qt是C++的框架，主要是C++没有几个能够轻松做界面的框架，所以请不要指望这玩意能雕出多好的花。用Qt多半是希望:有界面；运行流畅
如果用户想要好看的界面我建议搞Web前端，因为Qt公司从来没把UI好看与否放在他们的考虑之内。
⑥计时器
计时器多了程序会很卡
⑦quote
当你要在qmake设置路径，但有些路径含有空格，而这些路径又不能随意更改，那么可以查查quote的用法，会有帮助

5.Qt中字符串的处理
C字符数组；C++字符串；Qt字符串 三种字符串之间的转换请先搞清楚，否则会给你调用Qt函数带来很大的不便，这里我给出总结

①QByteArray->Qstring
QByteArray byteArray = "你好, Qt!"; // 假设是 UTF-8 编码
QString str = QString::fromUtf8(byteArray);
②Qstring->QByteArray
QString str = "Hello, 世界!";
QByteArray byteArray = str.toUtf8(); // 常用
③QByteArray->std::string
QByteArray byteArray = "Hello";
std::string stdStr = byteArray.toStdString(); // 直接转换
// 或
std::string stdStr(byteArray.constData(), byteArray.size());
④std::string->QByteArray
std::string stdStr = "World";
QByteArray byteArray = QByteArray::fromStdString(stdStr); // 直接转换
// 或
QByteArray byteArray(stdStr.data(), stdStr.size());
⑤QByteArray->char*
QByteArray byteArray = "Qt";
const char* charPtr = byteArray.constData(); // 只读指针
char* mutablePtr = byteArray.data();        // 可修改指针（可能触发深拷贝）
⑥char*->QByteArray
const char* charPtr = "Hello";
QByteArray byteArray(charPtr);              // 自动计算长度（直到 \0）
// 或指定长度（避免中间有 \0）
QByteArray byteArray(charPtr, strlen(charPtr));
⑦Qstring->std::string
QString str = "你好";
std::string stdStr = str.toStdString(); // 默认可能损失非 ASCII 字符
// 推荐显式转 UTF-8
std::string stdUtf8 = str.toUtf8().toStdString();
⑧std::string->Qstring
std::string stdStr = "こんにちは";
QString str = QString::fromUtf8(stdStr.c_str());
⑨Qstring->char*
QString str = "Hello";
QByteArray utf8 = str.toUtf8(); // 先转 QByteArray
const char* charPtr = utf8.constData(); // 只读指针
⑩char*->Qstring
const char* charPtr = "Привет";
QString str = QString::fromUtf8(charPtr); // UTF-8 编码
// 或 Latin1
QString str = QString::fromLatin1(charPtr);

6.Qt的领域一般为工控
在此我给出一个我之前上班时用过的模板，初学者可以参考

Qt有很多细节的用法，我无法一一列出，因此我想了一些给我造成过重大困扰的点总结于此，希望给初学者一点帮助
祝你愉快