#ifndef MAINWINDOW_H // 防止头文件重复包含
#define MAINWINDOW_H // 定义头文件

#include <QMainWindow> // 包含QMainWindow类的头文件,用于创建主窗口
#include <QFileDialog> // 包含QFileDialog类的头文件，用于文件对话框
#include <QListWidget> // 包含QListWidget类的头文件，用于列表框
#include <QMessageBox> // 包含QMessageBox类的头文件，用于消息对话框
#include <QTextStream> // 包含QTextStream类的头文件，用于文本流
#include <QFile>       // 包含QFile类的头文件，用于文件操作

QT_BEGIN_NAMESPACE // 命名空间开始
    namespace Ui
{
    class MainWindow;
} // 声明ui命名空间
QT_END_NAMESPACE // 命名空间结束

    class MainWindow : public QMainWindow // 声明MainWindow类，继承QMainWindow类
{
    Q_OBJECT // 声明宏，用于信号与槽的连接

        public : MainWindow(QWidget *parent = nullptr); // 构造函数，parent为父窗口，默认为nullptr
    ~MainWindow();                                      // 析构函数

private slots:
    void on_loadButton_clicked();     // 用于“录入”按钮
    void on_editButton_clicked();     // 用于“修改”按钮
    void on_reloadButton_clicked();   // 由于“加载”按钮
    void on_detectButton_clicked();   // 用于“检测冲突”按钮
    void on_actcleanButton_clicked(); // 用于清除“活动列表”按钮
    void on_concleanButton_clicked(); // 用于清除“冲突列表”按钮

private:
    Ui::MainWindow *ui; // 声明ui指针，用于访问ui界面
};

#endif // 头文件结束
