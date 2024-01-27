#include "./MainWindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // 调用构造函数，创建一个应用程序对象
    MainWindow w;               // 创建一个窗口对象
    w.show();                   // 显示窗口
    return a.exec();            // 进入消息循环
}
