// MyServiceThread.cpp : ʵ���ļ�
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
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	MyServiceList pTempDlg;//��������
	this->m_pMainWnd = &pTempDlg;
	pTempDlg.DoModal();
	return TRUE;
}

int MyServiceThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(MyServiceThread, CWinThread)
END_MESSAGE_MAP()


// MyServiceThread ��Ϣ�������
