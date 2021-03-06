/**********************************************************
  不用调用dll就可以执行的全局钩子示例:
  只留下F12做为程序退出,屏蔽键盘和鼠标,测试时请注意
  ********************************************************/
#ifndef HH_H
#define HH_Hsqllite3
#include <QApplication>
#include <Windows.h>
#include <Psapi.h>
#include <QDebug>
#include <QDebug>

#include "log.h"

HHOOK keyHook=NULL;
HHOOK mouseHook=NULL;
LogAction *lA = new LogAction();

TCHAR lpString[MAX_PATH], fpString[MAX_PATH];
POINT point;

//声明卸载函数,以便调用
void unHook();
BOOL SetPrivilege()   // 提取权限
{
    HANDLE hToken;
    TOKEN_PRIVILEGES NewState;
    LUID luidPrivilegeLUID;

    //获取进程令牌
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)||!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luidPrivilegeLUID))
    {
        printf("SetPrivilege Error\n");
        return FALSE;
    }
    NewState.PrivilegeCount = 1;
    NewState.Privileges[0].Luid = luidPrivilegeLUID;
    NewState.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    //提示进程权限，注意该函数也可以改变线程的权限，如果hToken指向一个线程的令牌
    if(!AdjustTokenPrivileges(hToken, FALSE, &NewState, NULL, NULL, NULL))
    {
        printf("AdjustTokenPrivilege Errro\n");
        return FALSE;
    }

    return TRUE;
}
BOOL GetCurrentWindow(POINT point, int wParam, int type)
{
    HWND hwnd, fatherHwnd;
    //DWORD len;
    DWORD ProcessID;
    HANDLE hProcess;
    DWORD nSize = MAX_PATH+1;
    WCHAR path[MAX_PATH+1];

    hwnd = WindowFromPoint(point);
    //qDebug() << point.x << ' ' << point.y;
    GetWindowThreadProcessId(hwnd, &ProcessID);
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |PROCESS_VM_READ, false, ProcessID);
    //len = GetProcessImageFileName(hProcess, path, nSize);   // 兼容性好
    if(!QueryFullProcessImageName(hProcess, 0, path, &nSize)){  // win7 以上操作系统
        qDebug() << "QueryFullProcessImageName";
        return false;
    }
    //qDebug() << QString((QChar*)path);

    GetWindowText(hwnd, lpString, MAX_PATH);
    fatherHwnd = GetParent(hwnd);   // 获取父窗口句柄
    GetWindowText(fatherHwnd, fpString, MAX_PATH);
    //qDebug() << GetForegroundWindow() << QString((QChar*)lpString);
    return lA->rendLog(QString((QChar*)path), QString((QChar*)lpString), QString((QChar*)fpString), type, point.x, point.y, wParam);
}
//键盘钩子过程
LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam )
{

    //qDebug() << wParam << ' ' << lParam;
    //在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
    if(pkbhs->vkCode==VK_F12)
    {
        void unHook();
        qApp->quit();
    }
    GetCurrentWindow(point, pkbhs->vkCode, 1);
    return 0;//返回1表示截取消息不再传递,返回0表示不作处理,消息继续传递

}
//鼠标钩子过程
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    point = ((MOUSEHOOKSTRUCT *) lParam)->pt;//鼠标位置信息
    GetCurrentWindow(point, wParam, 0);
    return 0;//返回1表示截取消息不再传递,返回0表示不作处理,消息继续传递

}
//卸载钩子
void unHook()
{
    UnhookWindowsHookEx(keyHook);
    UnhookWindowsHookEx(mouseHook);
    delete lA;

}
//安装钩子,调用该函数即安装钩子
void setHook()
{
    LPARAM lParam;
    //这两个底层钩子,不要DLL就可以全局
    //                         底层键盘钩子
    keyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);
    //                          底层鼠标钩子
    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
}
#endif HH_H
