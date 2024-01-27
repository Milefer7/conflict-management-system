#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QDebug>
#include "MainWindow/mainwindow.h"

class Activity
{
public:
    // Activity(MainWindow* mainWindow) : mainWindow(mainWindow) {}

    struct activity
    {
        QDateTime startTime;
        QDateTime endTime;
        QString content;
        QStringList participants;

        // 重构 “==”
        bool operator==(const activity &other) const
        {
            return this->startTime == other.startTime &&
                   this->endTime == other.endTime &&
                   this->content == other.content &&
                   this->participants == other.participants;
        }

        // 把一个对象结构体转换成QString
        QString stringActivity(const activity &act) const
        {
            QString formattedActivity;

            // 将日期时间转换为字符串
            QString startTimeStr = act.startTime.toString("yyyy-MM-dd hh:mm");
            QString endTimeStr = act.endTime.toString("yyyy-MM-dd hh:mm");

            // 拼接日期时间、事件内容和参与者信息
            formattedActivity = startTimeStr + ", " + endTimeStr + ", " + act.content + ", " + act.participants.join("; ");

            return formattedActivity;
        }
    };

    static QList<activity> loadActivitiesFromFile(const QString &filePath);            // 从文件中加载活动，返回一个包含加载的活动的 QList<activity>。
    static QList<activity> editActivitiesFromFile(const QString &filePath);            // 从文件中加载活动，返回一个包含加载的活动的 QList<activity>。
    static void showActivitiesList(QList<activity> activities, Ui::MainWindow *ui);    // 将结构体QList列表变成QString输出到列表
    static activity parseActivity(const QString &line);                                // 解析一行文本以创建一个活动对象，返回解析的活动对象。
    QList<Activity> activities;                                                        // 存储所有活动的列表
    static bool hasConflict(const Activity::activity &a, const Activity::activity &b); // 检测冲突
    static QString stringActivity(const Activity::activity &act);                      // 将结构体变成QString

};

#endif // ACTIVITY_H
