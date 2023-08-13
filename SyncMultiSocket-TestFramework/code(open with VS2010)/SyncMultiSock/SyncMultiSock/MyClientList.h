#pragma once
#include <map>
#include <iterator>
#include "afxwin.h"
using namespace std;

// MyClientList �Ի���

class MyClientList : public CDialogEx
{
	DECLARE_DYNAMIC(MyClientList)

public:
	MyClientList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyClientList();

// �Ի�������
	enum { IDD = IDD_DIALOG_ClientList };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedClientbutstarttest();
	afx_msg void OnBnClickedClientbutsure();

	CString m_IP;
	int m_Number;
	int m_Port;

	CListCtrl m_ListMsg;
	int m_ListCount;

	CStatic m_SockCountText;
	int m_SockCount;
	CStatic m_Hint;

	void AddListMsg(CString m_Msg);
	virtual void OnCancel();

	map<int,LPVOID> MapClient;
	map<int,LPVOID>::iterator MapIt;
	int m_MapCount;
	
	void AddSockCount(void);
};
