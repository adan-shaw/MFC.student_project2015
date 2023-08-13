#pragma once

// MyListener ÃüÁîÄ¿±ê

class MyListener : public CAsyncSocket
{
public:
	MyListener();
	virtual ~MyListener();
	virtual void OnAccept(int nErrorCode);

	LPVOID lpMainDlg;
};


