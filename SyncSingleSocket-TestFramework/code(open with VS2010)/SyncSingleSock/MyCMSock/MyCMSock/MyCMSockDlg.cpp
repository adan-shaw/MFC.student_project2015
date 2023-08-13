
// MyCMSockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyCMSock.h"
#include "MyCMSockDlg.h"
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


// MyCMSockDlg dialog




MyCMSockDlg::MyCMSockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyCMSockDlg::IDD, pParent)
	, m_IP(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TestCount = 0;
	m_ErrorCount = 0;
	m_ServerCount = 0;
	m_iListService = 0;
	m_iListClient = 0;
	this->m_iMapSockCount = 1;
}

void MyCMSockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EditTestCount, m_TestCount);
	DDX_Control(pDX, IDC_ErrorCount, m_TextErrorCount);
	DDX_Control(pDX, IDC_ServerCount, m_TextServerCount);
	DDX_Control(pDX, IDC_ListClient, m_ListClient);
	DDX_Control(pDX, IDC_ListSerive, m_ListService);
	DDX_Text(pDX, IDC_IP, m_IP);
}

BEGIN_MESSAGE_MAP(MyCMSockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Start, &MyCMSockDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_Stop, &MyCMSockDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_Define, &MyCMSockDlg::OnBnClickedDefine)
	ON_BN_CLICKED(IDC_StartTest, &MyCMSockDlg::OnBnClickedStarttest)
	ON_BN_CLICKED(IDC_SetTestCount, &MyCMSockDlg::OnBnClickedSettestcount)
END_MESSAGE_MAP()


// MyCMSockDlg message handlers

BOOL MyCMSockDlg::OnInitDialog()
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
	this->m_ListClient.InsertColumn(0,_T("Client message"),LVCFMT_LEFT,400,0);
	this->m_ListService.InsertColumn(0,_T("Service message"),LVCFMT_LEFT,600,0);
	this->InitMainDlg();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void MyCMSockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void MyCMSockDlg::OnPaint()
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
HCURSOR MyCMSockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void MyCMSockDlg::AddSerivceMsg(CString m_Msg)
{
	//添加消息服务端到列表
	this->m_ListService.InsertItem(this->m_iListService,_T(""));
	this->m_ListService.SetItemText(this->m_iListService,0,m_Msg);
	this->m_iListService++;
}


void MyCMSockDlg::AddClientMsg(CString m_Msg)
{
	//添加消息客户端端到列表
	this->m_ListClient.InsertItem(this->m_iListClient,_T(""));
	this->m_ListClient.SetItemText(this->m_iListClient,0,m_Msg);
	this->m_iListClient++;
}


void MyCMSockDlg::AddServerCount(BOOL m_Choose)
{
	//错误计数+/-
	if(m_Choose)
	{
	this->m_ServerCount++;
	CString strTemp;
	strTemp.Format(_T("%d"),this->m_ServerCount);
	this->m_TextServerCount.SetWindowTextW(strTemp);
	}
	else
	{
	this->m_ServerCount--;
	CString strTemp;
	strTemp.Format(_T("%d"),this->m_ServerCount);
	this->m_TextServerCount.SetWindowTextW(strTemp);
	}
}


void MyCMSockDlg::AddError(void)
{
	//错误计数+1
	this->m_ErrorCount++;
	CString strTemp;
	strTemp.Format(_T("%d"),this->m_ErrorCount);
	this->m_TextErrorCount.SetWindowTextW(strTemp);
}

#include "MyListener.h"
void MyCMSockDlg::OnBnClickedStart()
{
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_Start);
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_StartTest);
	pWnd->EnableWindow(TRUE);

	// 开始监听
	MyListener *pTemp = new MyListener;//创建监听者
	pTemp->lpMainDlg = this;//监听者继承主窗口
	this->lpListener = pTemp;//主窗口指定监听者

	if(!pTemp->Create(pTemp->m_iPort))
		{AfxMessageBox(_T("Create Listener Fail"));delete pTemp;this->lpListener=NULL;}
	if(!pTemp->Listen())
		{AfxMessageBox(_T("Listen Port Fail"));;delete pTemp;this->lpListener=NULL;}
	
	this->AddSerivceMsg(_T("Start listen"));

	pWnd=GetDlgItem(IDC_IP);
	pWnd->SetWindowTextW(_T("192.168.0.22"));
}


void MyCMSockDlg::OnBnClickedDefine()
{
	// 声明
	AfxMessageBox(_T("Copyright Notice:Mr.Shaw copyrights this specification. No part of this specification may be reproduced in any form or means, without the prior written consent of Mr.Shaw. \n\n Disclaimer:This specification is preliminary and is subject to change at any time without notice. Mr.Shaw assumes no responsibility for any errors contained herein. \n\n If the infringement please let us know the author"));
}

#include "MyClient.h"
void MyCMSockDlg::OnBnClickedStarttest()
{
	// 开始测试
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_Stop);
	pWnd->EnableWindow(TRUE);
	pWnd=GetDlgItem(IDC_StartTest);
	pWnd->EnableWindow(FALSE);

 	UpdateData(TRUE); //更新关联变量
	UpdateData(FALSE); //停止更新关联变量

	CString strTemp;
	MyListener *pListener = (MyListener*)this->lpListener;

	
	
	for(int iTemp = this->m_TestCount;iTemp>0;iTemp--)
	{
		MyClient *pClient = new MyClient;
		pClient->lpMainDlg = this;

		this->MapSock[this->m_iMapSockCount] = pClient;
		this->m_iMapSockCount++;
		try
		{
		pClient->Create();
		pClient->Connect(this->m_IP,pListener->m_iPort);
		
		}
		catch(...)
		{
			this->AddClientMsg(_T("test error"));
			break;
		}
	}
	strTemp.Format(_T("%d test success"),this->m_TestCount);
	this->AddClientMsg(strTemp);
}

#include "MyServer.h"
void MyCMSockDlg::OnBnClickedStop()
{
	// 停止监听
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_Stop);
	pWnd->EnableWindow(FALSE);													
	pWnd=GetDlgItem(IDC_EditTestCount);//找控件
	pWnd->EnableWindow(TRUE);
	pWnd=GetDlgItem(IDC_SetTestCount);//找控件
	pWnd->SetWindowTextW(_T("Set Test Count"));

	MyListener *pTemp = (MyListener*)this->lpListener;
	int iTemp = pTemp->MapSock.size();
	MyServer *pServer;
	CString strTemp;
	LPVOID lpTemp;
	for(;iTemp>0;iTemp--)
	{
		pTemp->MapSockIt = pTemp->MapSock.find(iTemp);
		if(pTemp->MapSockIt == pTemp->MapSock.end())
			continue;
		pServer = (MyServer*)pTemp->MapSockIt->second;
		pServer->Close();
		strTemp.Format(_T("server %d exit"),pServer->m_HimSelf);
		this->AddSerivceMsg(strTemp);
		delete pServer;
	}
	pTemp->Close();
	delete pTemp;

	MyClient *pClient;
	iTemp = this->MapSock.size();
	for(;iTemp>0;iTemp--)
	{
		this->MapSockIt = this->MapSock.find(iTemp);
		if(this->MapSockIt == this->MapSock.end())
			continue;
		pClient = (MyClient*)this->MapSockIt->second;
		pClient->Close();
		delete pClient;
	}
	AfxMessageBox(_T("The service stop"));
}

void MyCMSockDlg::OnBnClickedSettestcount()
{
	// 设置测试计数
	UpdateData(TRUE); //更新关联变量
	UpdateData(FALSE); //停止更新关联变量

	if(this->m_TestCount > 1000)
	{
		this->AddClientMsg(_T("have to <1000"));
		return;
	}
	CWnd *pWnd;	//定义窗口类指针													
	pWnd=GetDlgItem(IDC_EditTestCount);//找控件
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_Start);
	pWnd->EnableWindow(TRUE);

	pWnd=GetDlgItem(IDC_SetTestCount);//找控件
	pWnd->SetWindowTextW(_T("Reset Test Count"));
}





void MyCMSockDlg::InitMainDlg(void)
{
	CWnd *pWnd;													
	pWnd=GetDlgItem(IDC_Start);
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_Stop);
	pWnd->EnableWindow(FALSE);
	pWnd=GetDlgItem(IDC_StartTest);
	pWnd->EnableWindow(FALSE);
}
