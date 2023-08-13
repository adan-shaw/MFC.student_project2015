// MyServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyServer.h"


// MyServer

MyServer::MyServer()
{
}

MyServer::~MyServer()
{
}


// MyServer ��Ա����


void MyServer::OnReceive(int nErrorCode)
{
	AfxBeginThread(RecvThread,(LPVOID)this);//��ʼ���������߳�

	CAsyncSocket::OnReceive(nErrorCode);
}

#include "SyncMultiSockDlg.h"
UINT MyServer::RecvThread(LPVOID lParam)
{
	MyServer *pServer = (MyServer*)lParam;
	SyncMultiSockDlg *pMainDlg = (SyncMultiSockDlg*)pServer->lpMainDlg;

	LPVOID Buf = new BYTE[100];
	ZeroMemory(Buf,100);//��ջ�����
	int iTemp = 0;
	iTemp = pServer->Receive(Buf,100);//��������
	if(iTemp>0)
		::PostMessage(pMainDlg->pListenListThread->m_pMainWnd->m_hWnd,WM_MAINDLG_RECVBUF,(WPARAM)Buf,pServer->m_iHimself);
	else
		::PostMessage(pMainDlg->pListenListThread->m_pMainWnd->m_hWnd,WM_MAINDLG_RECVERROR,pServer->m_iHimself,NULL);
	
	CString strTemp;//�ط�welcome aboard client ���ͻ���
	strTemp.Format(_T("welcome aboard client"));
	iTemp = 0;
	iTemp = pServer->Send(strTemp,strTemp.GetLength()*2+1);
	if(iTemp<=0)
	{	//�ط�ʧ����ʾʧ����Ϣ
		::PostMessage(pMainDlg->pListenListThread->m_pMainWnd->m_hWnd,WM_MAINDLG_SENDERROR,pServer->m_iHimself,NULL);
	}
	return 0;
}
