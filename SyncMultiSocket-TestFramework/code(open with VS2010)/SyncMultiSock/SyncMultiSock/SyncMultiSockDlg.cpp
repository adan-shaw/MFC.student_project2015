
// SyncMultiSockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SyncMultiSock.h"
#include "SyncMultiSockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// SyncMultiSockDlg dialog




SyncMultiSockDlg::SyncMultiSockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SyncMultiSockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Run = FALSE;
}

void SyncMultiSockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ListenDlg_Hint, m_Hint);
}

BEGIN_MESSAGE_MAP(SyncMultiSockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ListenDlg_ButOpenListenWnd, &SyncMultiSockDlg::OnBnClickedListendlgButopenlistenwnd)
	ON_BN_CLICKED(IDC_ListenDlg_Define, &SyncMultiSockDlg::OnBnClickedListendlgDefine)
	ON_MESSAGE(WM_SERLIST_STOP,&SyncMultiSockDlg::SerListStop)
	ON_MESSAGE(WM_SERLIST_START,&SyncMultiSockDlg::SerListStart)
END_MESSAGE_MAP()


// SyncMultiSockDlg message handlers

BOOL SyncMultiSockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void SyncMultiSockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void SyncMultiSockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR SyncMultiSockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#include "MyServiceThread.h"
void SyncMultiSockDlg::OnBnClickedListendlgButopenlistenwnd()
{
	//创建监听者显示列表用户线程
	pListenListThread = AfxBeginThread(RUNTIME_CLASS(MyServiceThread));
	this->m_Hint.SetWindowTextW(_T("listen windows opened"));
	
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_ListenDlg_ButOpenListenWnd);								
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_ListenDlg_Define);								
	pWnd->EnableWindow(FALSE);
	//做完上面操作后,监听者显示列表用户线程 应该初始化完毕,发送继承 监听者窗口消息
	::PostMessage(pListenListThread->m_pMainWnd->m_hWnd, WM_MAINDLG_HIMSELF, (WPARAM)this->m_hWnd, NULL);//通知主窗口,service list 窗口创建完毕

}


void SyncMultiSockDlg::OnBnClickedListendlgDefine()
{
	//声明
	AfxMessageBox(_T("Copyright Notice:Mr.Shaw copyrights this specification. No part of this specification may be reproduced in any form or means, without the prior written consent of Mr.Shaw. \n\n Disclaimer:This specification is preliminary and is subject to change at any time without notice. Mr.Shaw assumes no responsibility for any errors contained herein. \n\n If the infringement please let us know the author"));
}


void SyncMultiSockDlg::OnCancel()
{
	//监听者退出开关询问--正在工作不能退出,要在监听者显示列表窗口中退出
	if(this->m_Run)
	{
		this->m_Hint.SetWindowTextW(_T("please stop listening first"));
		return;
	}

	CDialogEx::OnCancel();
}
#include "MyListener.h"
#include "MyServer.h"
LRESULT SyncMultiSockDlg::SerListStop(WPARAM wParam, LPARAM lParam)
{
	//停止监听消息
	this->m_Run = FALSE;
	MyListener *pTemp = (MyListener*)this->lpListener;

	if(pTemp != NULL)
	{
		delete pTemp;
		pTemp = NULL;
	}

	int iTemp;
	MyServer *pServer;
	for(iTemp = 0;iTemp<this->m_MapCount;iTemp++)//清空服务者socket
	{
		this->MapIt = this->MapServer.find(iTemp);
		if(this->MapIt ==  this->MapServer.end())
			continue;//找不到服务者下一个
		pServer = (MyServer*)this->MapIt->second;
		if(pServer == NULL)
			continue;//服务者为空下一个
		if(pServer->ShutDown(2))
			pServer->Close();
		else
			delete pServer;
	}
	this->MapServer.clear();//清空map
	this->m_MapCount = 0;

	this->m_Hint.SetWindowTextW(_T("listening stoped"));

	return 0;
}


LRESULT SyncMultiSockDlg::SerListStart(WPARAM wParam, LPARAM lParam)
{
	this->m_Run = TRUE;
	this->m_Port = 9213;//监听端口
	this->m_MapCount = 0;//map计数初始化

	MyListener *pTemp = new MyListener;//创建监听类
	this->lpListener = pTemp;
	pTemp->lpMainDlg = this;
	pTemp->Create(this->m_Port);//创建监听者
	pTemp->Listen();//监听

	this->m_Hint.SetWindowTextW(_T("listen begin"));
	return 0;
}