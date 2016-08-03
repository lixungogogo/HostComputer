///////////////////////////////////////////////////////////////// TestDlg.h : header file
#if !defined(AFX_TESTDLG_H__EDDDE196_1BF1_11D3_BE77_0000B454AEE4__INCLUDED_)
#define AFX_TESTDLG_H__EDDDE196_1BF1_11D3_BE77_0000B454AEE4__INCLUDED_
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "NewSocket.h"
#include "afxwin.h"
#include <shellapi.h>



// CTESTDlg 对话框
class CTESTDlg : public CDialog
{
	// Construction
public:
	 void OnKeepAlive();
	 void SocketReset();
	 void OnClose();
	 void OnReceive();
	 void OnAccept();
	// void OnTimer(UINT nIDEvent);
	 CSocketFile *m_file;
	 CArchive *m_arOut;
	 CArchive *m_arIn;
	 CNewSocket* m_ServerSocket;
	 CNewSocket *m_ClientSocket;
	 CTESTDlg(CWnd* pParent = NULL); // standard constructor
	 // Dialog Data
	 //{{AFX_DATA(CTESTDlg)
	 enum { IDD = IDD_TEST_DIALOG };
	 CString m_Info;
	 char buf[256];
	// char tbuffer[20];
	 CString m_Output;// = buf;
	 CString m_Input;
	 CString m_Connect;
	 CString m_IPAddress;
	 CString m_IPAddress2;

	// CString m_strCurrentIP;
	 UINT m_Port;
	 UINT iChecked1;
	
	 int m_Status;
	 int m_H;
	 //}}AFX_DATA
	 // ClassWizard generated virtual function overrides
	 //{{AFX_VIRTUAL(CTESTDlg)


protected:
	HICON m_hIcon;///< 托盘图标
	NOTIFYICONDATA NotifyIcon;//< 托盘的数据结构
	//afx_msg void OnNotifyIcon(WPARAM wParam, LPARAM IParam);

	



protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL
	// Implementation



protected:
	//HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CTESTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//afx_msg void OnNotifyIcon(WPARAM wParam, LPARAM IParam);
	//afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnSend();
	afx_msg void OnServerradio();
	afx_msg void OnClientradio();
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM IParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnEnChangeOutputedit();
	afx_msg void OnEnChangeInputedit();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnIpnFieldchangedIpaddress(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnEnChangePort();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg virtual void OnBnClickedButton1() final;
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
	afx_msg void OnBnClickedCheck11();
	afx_msg void OnBnClickedCheck12();
	afx_msg void OnBnClickedCheck13();
	afx_msg void OnBnClickedCheck14();
	afx_msg void OnBnClickedCheck15();
	afx_msg void OnBnClickedCheck16();

	int m_D, m_D_L, m_D_H;
	int m_A;
	int m_F;
	char m;
//	unsigned int V = 0;
	//unsigned int H = 0;
//	unsigned int F = 0;
//	unsigned int D = 0;
	//unsigned int D_H = 0;
	//unsigned int D_L = 0;
	int state = 0;
	
	//char *ptr;

	
	CStatic m_TIME;
	afx_msg void OnBnClickedConnectbutton2();

	bool Timer;
	afx_msg void OnStnClickedConnectedit();
	afx_msg void OnIpnFieldchangedIpaddress2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSendbutton2();
};
#endif 
