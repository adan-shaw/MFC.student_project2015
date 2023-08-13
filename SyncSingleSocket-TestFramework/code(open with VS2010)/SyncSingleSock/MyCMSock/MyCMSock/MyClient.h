#pragma once

// MyClient 命令目标

class MyClient : public CAsyncSocket
{
public:
	MyClient();
	virtual ~MyClient();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//**********
	//变量
	//**********
	LPVOID lpMainDlg;
};


