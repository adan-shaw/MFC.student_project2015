#pragma once

// MyServer ����Ŀ��

class MyServer : public CAsyncSocket
{
public:
	MyServer();
	virtual ~MyServer();
	/*********
	ע��:������Ϣ֪ͨ�����ڴ���,��Ҫ�����֪ͨ�¼�,�����ٶȻ����.
	**********/
	virtual void OnReceive(int nErrorCode);
//	virtual void OnConnect(int nErrorCode);
//	virtual void OnClose(int nErrorCode);
	//**********
	//����
	//**********
	LPVOID lpMainDlg;
	int m_HimSelf;
};


