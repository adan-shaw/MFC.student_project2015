#pragma once

#include <map>
#include <iterator>
using namespace std;

// MyListener ����Ŀ��

class MyListener : public CAsyncSocket
{
public:
	MyListener();
	virtual ~MyListener();
	virtual void OnAccept(int nErrorCode);
	//**********
	//����
	//**********
	int m_iPort;
	LPVOID lpMainDlg;

	map<int,LPVOID>MapSock;
	map<int,LPVOID>::iterator MapSockIt;
	int m_iMapSockCount;
};


