// MyServer.cpp : 实现文件
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


// MyServer 成员函数


void MyServer::OnReceive(int nErrorCode)
{
	AfxBeginThread(RecvThread,(LPVOID)this);//开始接收数据线程

	CAsyncSocket::OnReceive(nErrorCode);
}

#include "SyncMultiSockDlg.h"
UINT MyServer::RecvThread(LPVOID lParam)
{
	MyServer *pServer = (MyServer*)lParam;
	SyncMultiSockDlg *pMainDlg = (SyncMultiSockDlg*)pServer->lpMainDlg;

	LPVOID Buf = new BYTE[100];
	ZeroMemory(Buf,100);//清空缓冲区
	int iTemp = 0;
	iTemp = pServer->Receive(Buf,100);//接收数据
	if(iTemp>0)
		::PostMessage(pMainDlg->pListenListThread->m_pMainWnd->m_hWnd,WM_MAINDLG_RECVBUF,(WPARAM)Buf,pServer->m_iHimself);
	else
		::PostMessage(pMainDlg->pListenListThread->m_pMainWnd->m_hWnd,WM_MAINDLG_RECVERROR,pServer->m_iHimself,NULL);
	
	CString strTemp;//回发welcome aboard client 给客户端
	strTemp.Format(_T("welcome aboard client"));
	iTemp = 0;
	iTemp = pServer->Send(strTemp,strTemp.GetLength()*2+1);
	if(iTemp<=0)
	{	//回发失败显示失败消息
		::PostMessage(pMainDlg->pListenListThread->m_pMainWnd->m_hWnd,WM_MAINDLG_SENDERROR,pServer->m_iHimself,NULL);
	}
	return 0;
}
