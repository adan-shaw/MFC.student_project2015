// MyClientList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyClientList.h"
#include "afxdialogex.h"


// MyClientList �Ի���

IMPLEMENT_DYNAMIC(MyClientList, CDialogEx)

MyClientList::MyClientList(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyClientList::IDD, pParent)
{

	m_IP = _T("");
	m_Number = 0;
	m_Port = 0;
}

MyClientList::~MyClientList()
{
}

void MyClientList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ClientIp, m_IP);
	DDX_Text(pDX, IDC_ClientNumber, m_Number);
	DDX_Text(pDX, IDC_ClientPort, m_Port);
	DDX_Control(pDX, IDC_ClientListMsg, m_ListMsg);
	DDX_Control(pDX, IDC_ClientSockCount, m_SockCountText);
	DDX_Control(pDX, IDC_Hint, m_Hint);
}


BEGIN_MESSAGE_MAP(MyClientList, CDialogEx)
	
	ON_BN_CLICKED(IDC_ClientButStarttest, &MyClientList::OnBnClickedClientbutstarttest)
	ON_BN_CLICKED(IDC_ClientButSure, &MyClientList::OnBnClickedClientbutsure)
END_MESSAGE_MAP()


// MyClientList ��Ϣ�������





BOOL MyClientList::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//��ʼ������
	this->m_ListCount = 0;
	this->m_MapCount = 0;
	this->m_SockCount = 0;

	this->m_ListMsg.InsertColumn(0,_T("Count"),LVCFMT_LEFT,80,0);
	this->m_ListMsg.InsertColumn(1,_T("Message"),LVCFMT_LEFT,800,1);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	
}

#include "MyClient.h"
void MyClientList::OnBnClickedClientbutstarttest()
{
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_ClientButStarttest);
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_ClientButSure);
	pWnd->EnableWindow(FALSE);

	pWnd=GetDlgItem(IDC_ClientPort);
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_ClientNumber);
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_ClientIp);
	pWnd->EnableWindow(FALSE);

	MyClient *pClient;
	CString strTemp;

	for(int iTemp = 0;iTemp<this->m_Number;iTemp++)
	{
		pClient = new MyClient;
		pClient->lpMainDlg = this;
		pClient->m_Hinself = iTemp;

		this->MapClient[iTemp] = pClient;//����ӳ��
		if(!pClient->Create())//����socket
		{
			strTemp.Format(_T("%d socket create fail"),iTemp);
			this->AddListMsg(strTemp);
			delete pClient;
			this->MapClient[iTemp] = NULL;
		}
		//�첽���Ӳ����������,����if
		pClient->Connect(this->m_IP,this->m_Port);
		this->AddSockCount();//�����ı�+1
	}
}


void MyClientList::OnBnClickedClientbutsure()
{
	UpdateData(TRUE);
	UpdateData(FALSE);

}


void MyClientList::AddListMsg(CString m_Msg)
{
	CString strTemp;
	strTemp.Format(_T("%d"),this->m_ListCount);
	this->m_ListMsg.InsertItem(this->m_ListCount,_T(""));
	this->m_ListMsg.SetItemText(this->m_ListCount,0,strTemp);
	this->m_ListMsg.SetItemText(this->m_ListCount,1,m_Msg);
	this->m_ListCount++;
}


void MyClientList::OnCancel()
{
	MyClient *pClient;
	CString strTemp;

	for(int iTemp = 0;iTemp<this->m_Number;iTemp++)
	{
		this->MapIt = this->MapClient.find(iTemp);
		if(this->MapIt == this->MapClient.end())
			continue;//�Ҳ�������һ��
		pClient = (MyClient*)this->MapIt->second;
		if(pClient == NULL)
			continue;//�ͻ��˲����ھ���һ��
		if(pClient->ShutDown(2))//ִ��ɾ���ж�
			pClient->Close();
		else
			delete pClient;
	}

	CDialogEx::OnCancel();
}


void MyClientList::AddSockCount(void)
{
	CString strTemp;
	strTemp.Format(_T("%d"),this->m_SockCount);
	this->m_SockCountText.SetWindowTextW(strTemp);
	this->m_SockCount++;
}
