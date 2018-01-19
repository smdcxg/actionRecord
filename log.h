#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QFileInfo>
#include <QCoreApplication>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QDir>

class LogAction
{
public:
    explicit LogAction();
    ~LogAction();
    bool rendLog(QString path, QString title, QString fatherTitle, qint8 type, qint32 x, qint32 y, qint32 key);
    QFile *fileout;
    QTextStream txtOutput;

private:
    bool isDirExist(QString fullPath);
    bool isFileExist(QString fullFileName);
};

#endif // LOG_H
