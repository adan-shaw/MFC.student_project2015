// MyListener.cpp : 实现文件
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyListener.h"


// MyListener

MyListener::MyListener()
{
}

MyListener::~MyListener()
{
}


// MyListener 成员函数

#include "SyncMultiSockDlg.h"
#include "MyServer.h"
void MyListener::OnAccept(int nErrorCode)
{
	
	SyncMultiSockDlg *pMainDlg = (SyncMultiSockDlg*)this->lpMainDlg;
	MyServer *pTemp = new MyServer;//创建socket类

	if(this->Accept(*pTemp))//接受请求
	{	//成功则初始化该类
		pMainDlg->MapServer[pMainDlg->m_MapCount] = pTemp;
		pTemp->m_iHimself = pMainDlg->m_MapCount;//指定自身位置
		pMainDlg->m_MapCount++;
		pTemp->lpMainDlg = this->lpMainDlg;//指定主窗口
	}
	else
	{	//失败发送失败消息
		::PostMessage(pMainDlg->pListenListThread->m_pMainWnd->m_hWnd,WM_MAINDLG_ACCEPTERROR,pMainDlg->m_MapCount,NULL);
		delete pTemp;
	}
	//错误丢失都没有提示了,否则很麻烦

	CAsyncSocket::OnAccept(nErrorCode);
}
