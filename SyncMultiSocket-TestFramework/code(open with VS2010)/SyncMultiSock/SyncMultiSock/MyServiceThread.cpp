// MyServiceThread.cpp : 实现文件
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyServiceThread.h"


// MyServiceThread

IMPLEMENT_DYNCREATE(MyServiceThread, CWinThread)


MyServiceThread::MyServiceThread()
{
	
}

MyServiceThread::~MyServiceThread()
{
}
#include "MyServiceList.h"
BOOL MyServiceThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	MyServiceList pTempDlg;//创建窗口
	this->m_pMainWnd = &pTempDlg;
	pTempDlg.DoModal();
	return TRUE;
}

int MyServiceThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(MyServiceThread, CWinThread)
END_MESSAGE_MAP()


// MyServiceThread 消息处理程序
