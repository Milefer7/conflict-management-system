#include "activity.h"
#include "ui_mainwindow.h"

// 接口实现：从文件中加载活动，返回一个包含加载的活动的 QList<activity>。
QList<Activity::activity> Activity::loadActivitiesFromFile(const QString &filePath)
{
    QFile file(filePath);       // 创建一个文件对象
    QList<activity> activities; // 创建一个活动类列表

    // 错误处理
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "无法打开文件：" << filePath;
        return activities;
    }

    // 读取文件
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        activities.append(Activity::parseActivity(line));
    }

    // 关闭文件
    file.close();

    // 返回活动类列表
    return activities;
}

// 接口实现：将字符串转换为活动类
Activity::activity Activity::parseActivity(const QString &line)
{
    QStringList parts = line.split(", "); // 用逗号分割字符串
    activity act;                         // 创建一个活动类

    // 将字符串转换为活动类
    if (parts.size() >= 4) // 检查字符串是否有四个部分
    {
        act.startTime = QDateTime::fromString(parts[0], "yyyy-MM-dd HH:mm"); // 将字符串转换为日期时间
        act.endTime = QDateTime::fromString(parts[1], "yyyy-MM-dd HH:mm");   // 将字符串转换为日期时间
        act.content = parts[2].trimmed();                                    // 去除字符串两端的空格
        act.participants = parts[3].split("; ");                             // 用分号分割字符串
    }

    // 返回活动类
    return act;
}

// 接口实现：将活动类列表显示到活动列表中
void Activity::showActivitiesList(QList<activity> activities, Ui::MainWindow *ui)
{
    // 获取组数
    int numActivities = activities.size();

    // 逐个输出活动列表中的结构体数据
    for (int i = 0; i < numActivities; ++i)
    {
        const activity &act = activities.at(i); // 获取活动类
        QString s = act.stringActivity(act);    // 调用接口: 将活动类转换为字符串
        ui->activitiesListWidget->addItem(s);
    }
}

// 接口实现：将活动类转换为字符串
QString Activity::stringActivity(const Activity::activity &act)
{
    QString formattedActivity; // 创建一个字符串

    // 将日期时间转换为字符串
    QString startTimeStr = act.startTime.toString("yyyy-MM-dd hh:mm");
    QString endTimeStr = act.endTime.toString("yyyy-MM-dd hh:mm");

    // 拼接日期时间、事件内容和参与者信息
    formattedActivity = startTimeStr + ", " + endTimeStr + ", " + act.content + ", " + act.participants.join("; ");

    return formattedActivity;
}

// 接口实现：检测冲突
bool Activity::hasConflict(const Activity::activity &a, const Activity::activity &b)
{
    // 检查两个活动是否有时间上的冲突,如果有冲突，返回true
    return a.endTime > b.startTime && b.endTime > a.startTime; // 依据时间段的定义，如果两个时间段有重叠，就认为有冲突
}
