// MyClientThread.cpp : 实现文件
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyClientThread.h"


// MyClientThread

IMPLEMENT_DYNCREATE(MyClientThread, CWinThread)

MyClientThread::MyClientThread()
{
}

MyClientThread::~MyClientThread()
{
}
#include "MyClientList.h"
BOOL MyClientThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	MyClientList pTempDlg;//创建窗口
	this->m_pMainWnd = &pTempDlg;
	pTempDlg.DoModal();
	return TRUE;
}

int MyClientThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(MyClientThread, CWinThread)
END_MESSAGE_MAP()


// MyClientThread 消息处理程序
