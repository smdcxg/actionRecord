#include "log.h"

LogAction::LogAction()
{
    QString fullPath = QCoreApplication::applicationDirPath()+"/log/";
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString logFilePath(fullPath+time.toString("yyyy-MM-dd")+".txt");
    qDebug() << logFilePath;
    isDirExist(fullPath);
    fileout = new QFile(logFilePath);
    if(!fileout->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Open failed";
    }

}
LogAction::~LogAction()
{
    fileout->close();
}
bool LogAction::rendLog(QString path, QString title, QString fatherTitle, qint8 type, qint32 x, qint32 y, qint32 key)
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间

    QTextStream txtOutput(fileout);
    QFileInfo fileInfo(path);
    txtOutput << "["+time.toString("yyyy-MM-dd hh:mm:ss.zzz")+"]" << "\t" << fileInfo.fileName()  << "\t" << title << "\t" << fatherTitle << "\t" << type  << "\t" << x  << "\t" << y  << "\t" << key << "\n";
    txtOutput.flush();
    return true;
}
bool LogAction::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    else
    {
       bool ok = dir.mkdir(fullPath);//只创建一级子目录，即必须保证上级目录存在
       return ok;
    }
}
bool LogAction::isFileExist(QString fullFileName)
{
    QFileInfo fileInfo(fullFileName);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}
