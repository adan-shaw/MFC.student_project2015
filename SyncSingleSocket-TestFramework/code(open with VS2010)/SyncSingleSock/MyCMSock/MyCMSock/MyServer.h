#pragma once

// MyServer 命令目标

class MyServer : public CAsyncSocket
{
public:
	MyServer();
	virtual ~MyServer();
	/*********
	注意:窗口消息通知寄生于窗口,不要随便多加通知事件,否则速度会很慢.
	**********/
	virtual void OnReceive(int nErrorCode);
//	virtual void OnConnect(int nErrorCode);
//	virtual void OnClose(int nErrorCode);
	//**********
	//变量
	//**********
	LPVOID lpMainDlg;
	int m_HimSelf;
};


