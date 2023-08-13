// MyClient.cpp : 实现文件
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyClient.h"


// MyClient

MyClient::MyClient()
{
}

MyClient::~MyClient()
{
}


// MyClient 成员函数

#include "MyClientList.h"
void MyClient::OnReceive(int nErrorCode)
{
	MyClientList *pTemp = (MyClientList*)this->lpMainDlg;
	CString strTemp;
	LPVOID Buf = new BYTE[100];
	ZeroMemory(Buf,100);//清空缓冲区
	int iTemp = 0;
	iTemp = this->Receive(Buf,100);
	if(iTemp>0)
	{	//接收数据成功
		strTemp.Format(_T("%d socket recv data is : %s"),this->m_Hinself,Buf);
		pTemp->AddListMsg(strTemp);
	}
	else
	{	//接收数据失败
		strTemp.Format(_T("%d socket recv data fail"),this->m_Hinself);
		pTemp->AddListMsg(strTemp);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}


void MyClient::OnConnect(int nErrorCode)
{	//连接成功之后客户端发送hello server
	CString strTemp;
	strTemp.Format(_T("hello server"));
	int iTemp = 0;
	iTemp = this->Send(strTemp,strTemp.GetLength()*2+1);
	if(iTemp<=0)
	{	//发送hello server失败
		strTemp.Format(_T("%d socket send data fail"),this->m_Hinself);
		MyClientList *pTemp = (MyClientList*)this->lpMainDlg;
		pTemp->AddListMsg(strTemp);
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
