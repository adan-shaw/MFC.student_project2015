#pragma once



// MyServiceThread

class MyServiceThread : public CWinThread
{
	DECLARE_DYNCREATE(MyServiceThread)

protected:
	MyServiceThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~MyServiceThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


