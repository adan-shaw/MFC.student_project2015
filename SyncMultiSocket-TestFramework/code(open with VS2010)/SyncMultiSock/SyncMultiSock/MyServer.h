#pragma once

// MyServer ����Ŀ��

class MyServer : public CAsyncSocket
{
public:
	MyServer();
	virtual ~MyServer();
	virtual void OnReceive(int nErrorCode);

	LPVOID lpMainDlg;
	static UINT RecvThread(LPVOID lParam);
	int m_iHimself;
};


