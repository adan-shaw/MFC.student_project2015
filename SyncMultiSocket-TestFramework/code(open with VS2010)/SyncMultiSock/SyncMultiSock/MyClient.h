#pragma once

// MyClient ����Ŀ��

class MyClient : public CAsyncSocket
{
public:
	MyClient();
	virtual ~MyClient();
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);

	LPVOID lpMainDlg;
	int m_Hinself;
};


