// MyClient.cpp : 实现文件
//

#include "stdafx.h"
#include "MyCMSock.h"
#include "MyClient.h"


// MyClient

MyClient::MyClient()
{
}

MyClient::~MyClient()
{
}


// MyClient 成员函数


void MyClient::OnConnect(int nErrorCode)
{
	// 客户端连接成功
	CString strTemp;
	strTemp.Format(_T("hello server"));
	this->Send(strTemp,strTemp.GetLength()*2+1);//字符个数*2+1=缓冲区大小,缓冲区为8位
	CAsyncSocket::OnConnect(nErrorCode);
}

#include "MyCMSockDlg.h"
void MyClient::OnReceive(int nErrorCode)
{
	// 客户端接收数据
	MyCMSockDlg *pMainDlg = (MyCMSockDlg*)this->lpMainDlg;
	BYTE Buf[20];
	ZeroMemory(Buf,20);
	this->Receive(Buf,20);
	CString strTemp;
	strTemp.Format(_T("%s"),Buf);
	pMainDlg->AddClientMsg(strTemp);
	this->ShutDown(2);
	CAsyncSocket::OnReceive(nErrorCode);
}
