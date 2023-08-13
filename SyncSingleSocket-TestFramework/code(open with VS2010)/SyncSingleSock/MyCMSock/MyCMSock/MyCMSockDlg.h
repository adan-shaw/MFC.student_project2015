
// MyCMSockDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <map>
#include <iterator>
using namespace std;

// MyCMSockDlg dialog
class MyCMSockDlg : public CDialogEx
{
// Construction
public:
	MyCMSockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYCMSOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedDefine();
	afx_msg void OnBnClickedStarttest();
	afx_msg void OnBnClickedSettestcount();
	DECLARE_MESSAGE_MAP()
public:
	//**********
	//±äÁ¿
	//**********
	LPVOID lpListener;
	int m_TestCount;
	int m_ErrorCount;
	int m_ServerCount;
	CStatic m_TextErrorCount;
	CStatic m_TextServerCount;

	CListCtrl m_ListClient;
	int m_iListClient;
	CListCtrl m_ListService;
	int m_iListService;
	//**********
	//º¯Êý
	//**********
	void AddSerivceMsg(CString m_Msg);
	void AddClientMsg(CString m_Msg);
	void AddServerCount(BOOL m_Choose);
	void AddError(void);

	map<int,LPVOID>MapSock;
	map<int,LPVOID>::iterator MapSockIt;
	int m_iMapSockCount;

	CString m_IP;
	void InitMainDlg(void);
};
