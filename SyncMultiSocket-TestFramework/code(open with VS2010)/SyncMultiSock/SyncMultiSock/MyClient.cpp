// MyClient.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyClient.h"


// MyClient

MyClient::MyClient()
{
}

MyClient::~MyClient()
{
}


// MyClient ��Ա����

#include "MyClientList.h"
void MyClient::OnReceive(int nErrorCode)
{
	MyClientList *pTemp = (MyClientList*)this->lpMainDlg;
	CString strTemp;
	LPVOID Buf = new BYTE[100];
	ZeroMemory(Buf,100);//��ջ�����
	int iTemp = 0;
	iTemp = this->Receive(Buf,100);
	if(iTemp>0)
	{	//�������ݳɹ�
		strTemp.Format(_T("%d socket recv data is : %s"),this->m_Hinself,Buf);
		pTemp->AddListMsg(strTemp);
	}
	else
	{	//��������ʧ��
		strTemp.Format(_T("%d socket recv data fail"),this->m_Hinself);
		pTemp->AddListMsg(strTemp);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}


void MyClient::OnConnect(int nErrorCode)
{	//���ӳɹ�֮��ͻ��˷���hello server
	CString strTemp;
	strTemp.Format(_T("hello server"));
	int iTemp = 0;
	iTemp = this->Send(strTemp,strTemp.GetLength()*2+1);
	if(iTemp<=0)
	{	//����hello serverʧ��
		strTemp.Format(_T("%d socket send data fail"),this->m_Hinself);
		MyClientList *pTemp = (MyClientList*)this->lpMainDlg;
		pTemp->AddListMsg(strTemp);
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
