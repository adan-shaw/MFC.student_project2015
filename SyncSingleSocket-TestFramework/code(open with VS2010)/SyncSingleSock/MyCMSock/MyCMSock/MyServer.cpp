// MyServer.cpp : 实现文件
//

#include "stdafx.h"
#include "MyCMSock.h"
#include "MyServer.h"


// MyServer

MyServer::MyServer()
{
}

MyServer::~MyServer()
{
}


// MyServer 成员函数

//连接成功事件基本没用
//void MyServer::OnConnect(int nErrorCode)
//{
//	//连接成功之后
//	CString strTemp;
//	strTemp.Format(_T("hello client"));
//	this->Send(strTemp,strTemp.GetLength());
//	CAsyncSocket::OnConnect(nErrorCode);
//}

#include "MyCMSockDlg.h"
void MyServer::OnReceive(int nErrorCode)
{
	//接收数据
	MyCMSockDlg *pMainDlg = (MyCMSockDlg*)this->lpMainDlg;
	BYTE Buf[50];
	ZeroMemory(Buf,50);//情况必须要
	int iTemp = this->Receive(Buf,50);//接收字符是8位算的
	CString strTemp;
	strTemp.Format(_T("%d , %s"),this->m_HimSelf,Buf);
	pMainDlg->AddSerivceMsg(strTemp);
	
	strTemp.Format(_T("hello client"));
	this->Send(strTemp,strTemp.GetLength());

	CAsyncSocket::OnReceive(nErrorCode);
}

//关闭事件基本是没用的
//void MyServer::OnClose(int nErrorCode)
//{
//	//服务者关闭
//	CString strTemp;
//	strTemp.Format(_T("%d offline"),this->m_HimSelf);
//	MyCMSockDlg *pMainDlg = (MyCMSockDlg*)this->lpMainDlg;
//	pMainDlg->AddSerivceMsg(strTemp);
//	CAsyncSocket::OnClose(nErrorCode);
//}
