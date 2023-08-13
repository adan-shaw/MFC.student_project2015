
// SyncMultiSockDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <map>
#include <iterator>
using namespace std;

// SyncMultiSockDlg dialog
class SyncMultiSockDlg : public CDialogEx
{
// Construction
public:
	SyncMultiSockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SYNCMULTISOCK_DIALOG };

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
	afx_msg void OnBnClickedListendlgButopenlistenwnd();
	afx_msg void OnBnClickedListendlgDefine();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT SerListStop(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT SerListStart(WPARAM wParam, LPARAM lParam);

	BOOL m_Run;
	virtual void OnCancel();
	CStatic m_Hint;
	CWinThread *pListenListThread;

	LPVOID lpListener;
	int m_Port;

	map<int,LPVOID>MapServer;
	map<int,LPVOID>::iterator MapIt;
	int m_MapCount;

};
