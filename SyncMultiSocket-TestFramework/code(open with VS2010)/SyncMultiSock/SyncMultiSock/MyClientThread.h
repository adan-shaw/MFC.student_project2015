#pragma once



// MyClientThread

class MyClientThread : public CWinThread
{
	DECLARE_DYNCREATE(MyClientThread)

protected:
	MyClientThread();           // 动态创建所使用的受保护的构造函数
	virtual ~MyClientThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


