// MyClientThread.cpp : ʵ���ļ�
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
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	MyClientList pTempDlg;//��������
	this->m_pMainWnd = &pTempDlg;
	pTempDlg.DoModal();
	return TRUE;
}

int MyClientThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(MyClientThread, CWinThread)
END_MESSAGE_MAP()


// MyClientThread ��Ϣ�������
