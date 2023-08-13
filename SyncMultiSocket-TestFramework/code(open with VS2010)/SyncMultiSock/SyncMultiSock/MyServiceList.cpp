// MyServiceList.cpp : 实现文件
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "MyServiceList.h"
#include "afxdialogex.h"


// MyServiceList 对话框

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
	//自定义消息响应入口
	ON_MESSAGE(WM_MAINDLG_HIMSELF,&MyServiceList::MainDlgHimself)
	ON_MESSAGE(WM_MAINDLG_ACCEPTERROR,&MyServiceList::MainDlgAcceptError)
	ON_MESSAGE(WM_MAINDLG_RECVERROR,&MyServiceList::MainDlgRecvError)
	ON_MESSAGE(WM_MAINDLG_RECVBUF,&MyServiceList::MainDlgRecvBuf)
	ON_MESSAGE(WM_MAINDLG_SENDERROR,&MyServiceList::MainDlgSendError)
END_MESSAGE_MAP()


// MyServiceList 消息处理程序


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
	//通知主窗口开始服务
	::PostMessage(this->pMainDlg, WM_SERLIST_START, NULL, NULL);
}


void MyServiceList::OnBnClickedSerbutstop()
{
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_SerButStart);								
	pWnd->EnableWindow(TRUE);
	pWnd=GetDlgItem(IDC_SerButStop);								
	pWnd->EnableWindow(FALSE);

	//通知主窗口停止监听
	this->m_SWStop = FALSE;
	::PostMessage(this->pMainDlg, WM_SERLIST_STOP, NULL, NULL);
}

#include "MyClientThread.h"
void MyServiceList::OnBnClickedSerbutopenclient()
{
	//创建客户端用户线程
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
	m_SWStop = FALSE;//暂停按钮与交叉退出的防止冲突初始化

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
	this->pMainDlg = (HWND)wParam;//收到Himself就继承主窗口HWND即可
	return 0;
}

LRESULT MyServiceList::MainDlgAcceptError(WPARAM wParam, LPARAM lParam)
{
	//接受请求出错消息
	int iTemp = wParam;
	CString strTemp;
	strTemp.Format(_T("%d socket accept fail"),iTemp);
	this->AddListMsg(strTemp);
	return 0;
}

LRESULT MyServiceList::MainDlgRecvError(WPARAM wParam, LPARAM lParam)
{
	//接收数据出错消息
	int iTemp = wParam;
	CString strTemp;
	strTemp.Format(_T("%d socket recv data fail"),iTemp);
	this->AddListMsg(strTemp);
	return 0;
}

LRESULT MyServiceList::MainDlgRecvBuf(WPARAM wParam, LPARAM lParam)
{
	//接收数据成功并显示
	LPVOID lpTemp = (LPVOID)wParam;
	int iTemp = lParam;
	CString strTemp;
	strTemp.Format(_T("%d socket recv data is : %s"),iTemp,lpTemp);
	this->AddListMsg(strTemp);
	delete lpTemp;//删除缓冲区
	return 0;
}

LRESULT MyServiceList::MainDlgSendError(WPARAM wParam, LPARAM lParam)
{
	//发送出错消息
	int iTemp = wParam;
	CString strTemp;
	strTemp.Format(_T("%d socket send data fail"),iTemp);
	this->AddListMsg(strTemp);
	return 0;
}


void MyServiceList::OnCancel()
{
	//交叉退出询问开关防止冲突
	if(m_SWStop)
		::PostMessage(this->pMainDlg, WM_SERLIST_STOP, NULL, NULL);//通知主窗口停止监听
	CDialogEx::OnCancel();
}
