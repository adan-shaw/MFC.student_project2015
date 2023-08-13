// MyServiceList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyServiceList.h"
#include "afxdialogex.h"


// MyServiceList �Ի���

IMPLEMENT_DYNAMIC(MyServiceList, CDialogEx)

MyServiceList::MyServiceList(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyServiceList::IDD, pParent)
{

}

MyServiceList::~MyServiceList()
{
}

void MyServiceList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SerListMsg, m_ListMsg);
	DDX_Control(pDX, IDC_SerButStart, m_ButStart);
	DDX_Control(pDX, IDC_SerButStop, m_ButStop);
	DDX_Control(pDX, IDC_SerButOpenClient, m_ButOpenClient);
}


BEGIN_MESSAGE_MAP(MyServiceList, CDialogEx)
	ON_BN_CLICKED(IDC_SerButStart, &MyServiceList::OnBnClickedSerbutstart)
	ON_BN_CLICKED(IDC_SerButStop, &MyServiceList::OnBnClickedSerbutstop)
	ON_BN_CLICKED(IDC_SerButOpenClient, &MyServiceList::OnBnClickedSerbutopenclient)
	//�Զ�����Ϣ��Ӧ���
	ON_MESSAGE(WM_MAINDLG_HIMSELF,&MyServiceList::MainDlgHimself)
	ON_MESSAGE(WM_MAINDLG_ACCEPTERROR,&MyServiceList::MainDlgAcceptError)
	ON_MESSAGE(WM_MAINDLG_RECVERROR,&MyServiceList::MainDlgRecvError)
	ON_MESSAGE(WM_MAINDLG_RECVBUF,&MyServiceList::MainDlgRecvBuf)
	ON_MESSAGE(WM_MAINDLG_SENDERROR,&MyServiceList::MainDlgSendError)
END_MESSAGE_MAP()


// MyServiceList ��Ϣ�������


void MyServiceList::OnBnClickedSerbutstart()
{
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_SerButStart);								
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_SerButStop);								
	pWnd->EnableWindow(TRUE);
	pWnd=GetDlgItem(IDC_SerButOpenClient);
	pWnd->EnableWindow(TRUE);
	pWnd=GetDlgItem(IDC_SerButStop);	
	pWnd->EnableWindow(TRUE);
	this->m_SWStop = TRUE;
	//֪ͨ�����ڿ�ʼ����
	::PostMessage(this->pMainDlg, WM_SERLIST_START, NULL, NULL);
}


void MyServiceList::OnBnClickedSerbutstop()
{
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_SerButStart);								
	pWnd->EnableWindow(TRUE);
	pWnd=GetDlgItem(IDC_SerButStop);								
	pWnd->EnableWindow(FALSE);

	//֪ͨ������ֹͣ����
	this->m_SWStop = FALSE;
	::PostMessage(this->pMainDlg, WM_SERLIST_STOP, NULL, NULL);
}

#include "MyClientThread.h"
void MyServiceList::OnBnClickedSerbutopenclient()
{
	//�����ͻ����û��߳�
	pClientListThread = AfxBeginThread(RUNTIME_CLASS(MyClientThread));
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_SerButOpenClient);								
	pWnd->EnableWindow(FALSE);
}

BOOL MyServiceList::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->m_ListMsg.InsertColumn(0,_T("Count"),LVCFMT_LEFT,80,0);
	this->m_ListMsg.InsertColumn(1,_T("Message"),LVCFMT_LEFT,800,0);
	this->m_ListCount = 0;

	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_SerButOpenClient);
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_SerButStop);	
	pWnd->EnableWindow(FALSE);
	m_SWStop = FALSE;//��ͣ��ť�뽻���˳��ķ�ֹ��ͻ��ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	
}

void MyServiceList::AddListMsg(CString strMsg)
{
	
	CString strTemp;
	strTemp.Format(_T("%d"),this->m_ListCount);
	this->m_ListMsg.InsertItem(this->m_ListCount,_T(""));
	this->m_ListMsg.SetItemText(this->m_ListCount,0,strTemp);
	this->m_ListMsg.SetItemText(this->m_ListCount,1,strMsg);
	this->m_ListCount++;
	
}


LRESULT MyServiceList::MainDlgHimself(WPARAM wParam, LPARAM lParam)
{
	this->pMainDlg = (HWND)wParam;//�յ�Himself�ͼ̳�������HWND����
	return 0;
}

LRESULT MyServiceList::MainDlgAcceptError(WPARAM wParam, LPARAM lParam)
{
	//�������������Ϣ
	int iTemp = wParam;
	CString strTemp;
	strTemp.Format(_T("%d socket accept fail"),iTemp);
	this->AddListMsg(strTemp);
	return 0;
}

LRESULT MyServiceList::MainDlgRecvError(WPARAM wParam, LPARAM lParam)
{
	//�������ݳ�����Ϣ
	int iTemp = wParam;
	CString strTemp;
	strTemp.Format(_T("%d socket recv data fail"),iTemp);
	this->AddListMsg(strTemp);
	return 0;
}

LRESULT MyServiceList::MainDlgRecvBuf(WPARAM wParam, LPARAM lParam)
{
	//�������ݳɹ�����ʾ
	LPVOID lpTemp = (LPVOID)wParam;
	int iTemp = lParam;
	CString strTemp;
	strTemp.Format(_T("%d socket recv data is : %s"),iTemp,lpTemp);
	this->AddListMsg(strTemp);
	delete lpTemp;//ɾ��������
	return 0;
}

LRESULT MyServiceList::MainDlgSendError(WPARAM wParam, LPARAM lParam)
{
	//���ͳ�����Ϣ
	int iTemp = wParam;
	CString strTemp;
	strTemp.Format(_T("%d socket send data fail"),iTemp);
	this->AddListMsg(strTemp);
	return 0;
}


void MyServiceList::OnCancel()
{
	//�����˳�ѯ�ʿ��ط�ֹ��ͻ
	if(m_SWStop)
		::PostMessage(this->pMainDlg, WM_SERLIST_STOP, NULL, NULL);//֪ͨ������ֹͣ����
	CDialogEx::OnCancel();
}
