// MyListener.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyListener.h"


// MyListener

MyListener::MyListener()
{
}

MyListener::~MyListener()
{
}


// MyListener ��Ա����

#include "SyncMultiSockDlg.h"
#include "MyServer.h"
void MyListener::OnAccept(int nErrorCode)
{
	
	SyncMultiSockDlg *pMainDlg = (SyncMultiSockDlg*)this->lpMainDlg;
	MyServer *pTemp = new MyServer;//����socket��

	if(this->Accept(*pTemp))//��������
	{	//�ɹ����ʼ������
		pMainDlg->MapServer[pMainDlg->m_MapCount] = pTemp;
		pTemp->m_iHimself = pMainDlg->m_MapCount;//ָ������λ��
		pMainDlg->m_MapCount++;
		pTemp->lpMainDlg = this->lpMainDlg;//ָ��������
	}
	else
	{	//ʧ�ܷ���ʧ����Ϣ
		::PostMessage(pMainDlg->pListenListThread->m_pMainWnd->m_hWnd,WM_MAINDLG_ACCEPTERROR,pMainDlg->m_MapCount,NULL);
		delete pTemp;
	}
	//����ʧ��û����ʾ��,������鷳

	CAsyncSocket::OnAccept(nErrorCode);
}
