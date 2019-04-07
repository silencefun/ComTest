# ComTest
Android 串口通信 调试工具 源码
包含了5个项目
ComAssistant 是Eclipse 的项目
ComTest2 是Android Studio 项目
这两个项目是直接 使用jni调用编译好的so文件 

AndroidStuido_3.0_COMTEST 是 Android  Studio 3.0 使用 Cmake方式 完成串口调试工具 的实现

ComTest_SetN81 是 增加 设定 N-8-1 （数据位停止位校验方式  Android  Studio 3.0 使用 Cmake方式）的Demo 实现

附自己学习这个硬件串口通讯的一些记录，都在简书：

Android 串口通信开发笔记01 https://www.jianshu.com/p/25abd940b1dd

Android 串口通信笔记2 调试工具分析 工具类实现分析、项目实现 https://www.jianshu.com/p/d3d65230ecdb

Android 串口通信开发笔记3：CMake 方式实现和 多对多的实现逻辑 https://www.jianshu.com/p/6a6c47a3b01b

Android 串口开发 支持N-8-1（数据位停止位校验方式） 设定 https://www.jianshu.com/p/0868e90303be

2019年4月7日 12:12:15 更新
Android  Studio 新版的cmake可能是C++语法，在.cpp文件中 出现
类似 operator to 'Jnienv' instead of a pointer
查看了
https://stackoverflow.com/questions/47504229/android-jni-cmake-member-reference-type-jnienv-aka-jnienv-is-not-a-point
解释，

并不怎么了解C与C++的差异，
解决办法为把扩展名.cpp改成.c
同样还有 在Cmakelist 中也要改成.c
