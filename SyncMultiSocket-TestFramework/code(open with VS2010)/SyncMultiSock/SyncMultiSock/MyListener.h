#pragma once

// MyListener ����Ŀ��

class MyListener : public CAsyncSocket
{
public:
	MyListener();
	virtual ~MyListener();
	virtual void OnAccept(int nErrorCode);

	LPVOID lpMainDlg;
};


