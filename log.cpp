#include "log.h"

void LogAction::log()
{

}
bool LogAction::rendLog(QString path, QString title, qint8 type, qint32 x, qint32 y, qint32 key)
{
    QString fullPath = QCoreApplication::applicationDirPath()+"/log/";
     QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString logFilePath(fullPath+time.toString("yyyy-MM-dd")+".txt");
    isDirExist(fullPath);
    if(isFileExist(logFilePath)){

    }
    QFile fileout(logFilePath);
    if(!fileout.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open failed";
        return false;
    }
    QTextStream txtOutput(&fileout);
    txtOutput << "["+time.toString("yyyy-MM-dd hh:mm:ss ddd")+"]" << path << title << type << x << y << key << "\n";
    fileout.close();
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
