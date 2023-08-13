#pragma once

// MyClient ÃüÁîÄ¿±ê

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


