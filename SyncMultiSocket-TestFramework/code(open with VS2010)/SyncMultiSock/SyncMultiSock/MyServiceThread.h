#pragma once



// MyServiceThread

class MyServiceThread : public CWinThread
{
	DECLARE_DYNCREATE(MyServiceThread)

protected:
	MyServiceThread();           // 动态创建所使用的受保护的构造函数
	virtual ~MyServiceThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


