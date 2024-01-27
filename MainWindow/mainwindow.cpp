#include "ui_mainwindow.h"       // 包含ui界面的头文件
#include "./Activity/activity.h" // 包含活动类的头文件
#include <QDesktopServices>      // 包含QDesktopServices类的头文件，用于打开文件夹
#include <QList>                 // 包含QList类的头文件，用于列表

// 构造函数
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// 析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

// 录入按钮实现
void MainWindow::on_loadButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Activity File"), "", tr("Activity Files (*.txt)"));
    if (!filePath.isEmpty())
    {
        QList act = Activity::loadActivitiesFromFile(filePath); // 调用录入接口，返回值是活动类列表
        Activity::showActivitiesList(act, ui);                  // 调用展示活动列表接口，将活动类列表显示到活动列表中
    }
}

// 修改按钮实现
void MainWindow::on_editButton_clicked()
{
    // 点击编辑按钮时，调出文件并打开文件。用户修改完后点击关闭。
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Activity File"), "", tr("Activity Files (*.txt)"));
    if (!filePath.isEmpty())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath)); // 调用打开文件夹接口
    }
}

// 重新加载按钮实现
void MainWindow::on_reloadButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Activity File"), "", tr("Activity Files (*.txt)"));
    if (!filePath.isEmpty())
    {
        QList act = Activity::loadActivitiesFromFile(filePath); // 调用录入接口，返回值是活动类列表
        ui->activitiesListWidget->clear();
        Activity::showActivitiesList(act, ui); // 调用展示活动列表接口
    }
}

// 检测冲突按钮实现
void MainWindow::on_detectButton_clicked()
{
    // 获取当前所有活动
    QList<Activity::activity> allActivities;

    for (int i = 0; i < ui->activitiesListWidget->count(); ++i) // 遍历活动列表中的每一项
    {
        QListWidgetItem *item = ui->activitiesListWidget->item(i);        // 获取活动列表中的每一项
        QString activityString = item->text();                            // 获取活动列表中的每一项的文本
        Activity::activity act = Activity::parseActivity(activityString); // 调用“将字符串转换为活动类”接口
        allActivities.append(act);                                        // 将活动类添加到活动列表中
    }

    // 检测冲突
    QList<Activity::activity> conflictingActivities; // 创建一个冲突活动列表
    for (int i = 0; i < allActivities.size(); ++i)   // 遍历活动列表中的每一项
    {
        for (int j = i + 1; j < allActivities.size(); ++j) // 遍历活动列表中的每一项
        {
            if (Activity::hasConflict(allActivities[i], allActivities[j])) // 调用 hasConflict 接口，检测是否冲突
            {
                // 如果冲突，将冲突的活动添加到冲突活动列表中
                conflictingActivities.append(allActivities[i]);
                conflictingActivities.append(allActivities[j]);
            }
        }
    }

    // 清空原来的活动列表
    ui->activitiesListWidget->clear();

    // 将没有冲突的活动重新添加到活动列表中
    for (const Activity::activity &act : allActivities)
    {
        if (!conflictingActivities.contains(act))
        {
            QString s = Activity::stringActivity(act);
            ui->activitiesListWidget->addItem(s);
        }
    }

    // 显示有冲突的活动列表到 conflictListWidget
    ui->conflictListWidget->clear();
    for (const Activity::activity &conflictingAct : conflictingActivities)
    {
        QString s = Activity::stringActivity(conflictingAct); // 调用“将结构体变成QString”接口
        ui->conflictListWidget->addItem(s);
    }
}

// 清除“活动列表的内容”按钮实现
void MainWindow::on_actcleanButton_clicked()
{
    ui->activitiesListWidget->clear();
}

// 清除“冲突列表的内容”按钮实现
void MainWindow::on_concleanButton_clicked()
{
    ui->conflictListWidget->clear();
}
