/**********************************************************
  不用调用dll就可以执行的全局钩子示例:
  只留下F12做为程序退出,屏蔽键盘和鼠标,测试时请注意
  ********************************************************/
#ifndef HH_H
#define HH_H
#include <QApplication>
#include <Windows.h>
#include <QDebug>
#include <QDebug>

HHOOK keyHook=NULL;
HHOOK mouseHook=NULL;
//声明卸载函数,以便调用
void unHook();
//键盘钩子过程
LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam )
{

    qDebug() << nCode << ' ' << wParam << ' ' << lParam;
    //在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
    if(pkbhs->vkCode==VK_F12)
    {
        void unHook();
        qApp->quit();
    }
    return 0;//返回1表示截取消息不再传递,返回0表示不作处理,消息继续传递

}
//鼠标钩子过程
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{

    POINT point = ((MOUSEHOOKSTRUCT *) lParam)->pt;//鼠标位置信息
    qDebug() << point.x << ' ' << point.y;
    return 0;

}
//卸载钩子
void unHook()
{
    UnhookWindowsHookEx(keyHook);
    UnhookWindowsHookEx(mouseHook);

}
//安装钩子,调用该函数即安装钩子
void setHook()
{
    //这两个底层钩子,不要DLL就可以全局
    //                         底层键盘钩子
    keyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);
    //                          底层鼠标钩子
    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
}
#endif HH_H
