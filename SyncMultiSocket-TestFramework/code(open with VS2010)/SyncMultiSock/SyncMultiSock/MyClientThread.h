#pragma once



// MyClientThread

class MyClientThread : public CWinThread
{
	DECLARE_DYNCREATE(MyClientThread)

protected:
	MyClientThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~MyClientThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


