#pragma once

// MyClient ����Ŀ��

class MyClient : public CAsyncSocket
{
public:
	MyClient();
	virtual ~MyClient();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//**********
	//����
	//**********
	LPVOID lpMainDlg;
};


