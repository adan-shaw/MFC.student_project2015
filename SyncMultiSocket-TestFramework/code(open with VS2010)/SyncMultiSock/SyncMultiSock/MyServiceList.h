#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// MyServiceList �Ի���

class MyServiceList : public CDialogEx
{
	DECLARE_DYNAMIC(MyServiceList)

public:
	MyServiceList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyServiceList();

// �Ի�������
	enum { IDD = IDD_DIALOG_ServiceList };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedSerbutstart();
	afx_msg void OnBnClickedSerbutstop();
	afx_msg void OnBnClickedSerbutopenclient();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT MainDlgHimself(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT MainDlgAcceptError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT MainDlgRecvError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT MainDlgRecvBuf(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT MainDlgSendError(WPARAM wParam, LPARAM lParam);
	HWND pMainDlg;

	
	CListCtrl m_ListMsg;
	int m_ListCount;
	CButton m_ButStart;
	CButton m_ButStop;
	CButton m_ButOpenClient;

	CWinThread *pClientListThread;
	virtual BOOL OnInitDialog();
	void AddListMsg(CString strMsg);
	virtual void OnCancel();
	BOOL m_SWStop;
};
