// MyListener.cpp : 实现文件
//

#include "stdafx.h"
#include "MyCMSock.h"
#include "MyListener.h"


// MyListener

MyListener::MyListener()
{
	this->m_iMapSockCount = 1;
}

MyListener::~MyListener()
{
}


// MyListener 成员函数

#include "MyServer.h"
void MyListener::OnAccept(int nErrorCode)
{
	//监听者接受请求
	MyServer *pTemp = new MyServer;
	pTemp->lpMainDlg = this->lpMainDlg;

	this->Accept(*pTemp);
	this->MapSock[this->m_iMapSockCount] = pTemp;
	pTemp->m_HimSelf = this->m_iMapSockCount;
	this->m_iMapSockCount++;
	CAsyncSocket::OnAccept(nErrorCode);
}


