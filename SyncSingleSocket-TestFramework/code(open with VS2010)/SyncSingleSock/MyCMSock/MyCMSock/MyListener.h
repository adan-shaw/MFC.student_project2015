#pragma once

#include <map>
#include <iterator>
using namespace std;

// MyListener 命令目标

class MyListener : public CAsyncSocket
{
public:
	MyListener();
	virtual ~MyListener();
	virtual void OnAccept(int nErrorCode);
	//**********
	//变量
	//**********
	int m_iPort;
	LPVOID lpMainDlg;

	map<int,LPVOID>MapSock;
	map<int,LPVOID>::iterator MapSockIt;
	int m_iMapSockCount;
};


