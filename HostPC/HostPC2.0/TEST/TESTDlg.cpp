//////////////////////// TestDlg.cpp : implementation file
#include "stdafx.h"
#include <afxsock.h>
#include <iostream>
#include "Test.h"
#include "TestDlg.h"
#include "Struct.h"
#include "stdlib.h"
#include "winsock.h"
#include <fstream>
#include "mstcpip.h"
#include "WinSock2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_NC (WM_USER+100)

char tbuffer[20] = { '0' };
char CH[16] = { '0' };
int state = 0;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTESTDlg 对话框
CTESTDlg::CTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTESTDlg::IDD, pParent)
	, m_D(0)
	, m_A(0)
	, m_F(0)
	, m_Input(_T(""))
	, m_Output(_T(""))
//	, m_strCurrentIP(_T(""))

, Timer(false)
{
	//{{AFX_DATA_INIT(CTESTDlg)
	m_Info = _T("");
	m_Output = _T("");
	 m_Input = _T("");
	m_Connect = _T("");
	//m_strCurrentIP = _T("");
	m_IPAddress = _T("");
	m_IPAddress2 = _T("");
	m_Port = 0;
	m_Status = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_test = 0;
}

void CTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTESTDlg)



	DDX_Text(pDX, IDC_CONNECTEDIT, m_Connect);
	DDX_Text(pDX, IDC_IPADDRESS, m_IPAddress);
	DDX_Text(pDX, IDC_IPADDRESS, m_IPAddress2);
	//  DDV_MaxChars(pDX, m_IPAddress, 15);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Radio(pDX, IDC_SERVERRADIO, m_Status);
	/*CString canstant;
	canstant = "0";
	  DDX_Text(pDX, IDC_EDIT7, canstant);
	  DDX_Text(pDX, IDC_EDIT5, canstant);
	  DDX_Text(pDX, IDC_EDIT6, canstant);*/


	DDX_Control(pDX, IDC_CONNECTEDIT, m_TIME);
}

BEGIN_MESSAGE_MAP(CTESTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_NC,OnNotifyIcon)
	ON_BN_CLICKED(IDC_CONNECTBUTTON, OnConnect)
	ON_BN_CLICKED(IDC_DISCONNECTBUTTON, OnDisconnect)
	ON_BN_CLICKED(IDC_SENDBUTTON, OnSend)
	ON_BN_CLICKED(IDC_SERVERRADIO, OnServerradio)
	ON_BN_CLICKED(IDC_CLIENTRADIO, OnClientradio)

	//ON_BN_CLICKED(IDC_RECEIVECLEARBUTTON, OnReceiveclear)

	
	ON_EN_CHANGE(IDC_INPUTEDIT, &CTESTDlg::OnEnChangeInputedit)
	ON_BN_CLICKED(IDC_BUTTON6, &CTESTDlg::OnBnClickedButton6)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS, &CTESTDlg::OnIpnFieldchangedIpaddress)
	ON_EN_CHANGE(IDC_EDIT1, &CTESTDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_PORT, &CTESTDlg::OnEnChangePort)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTESTDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CTESTDlg::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CTESTDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &CTESTDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT5, &CTESTDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CTESTDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CTESTDlg::OnEnChangeEdit7)

	ON_BN_CLICKED(IDC_RADIO1, &CTESTDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CTESTDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK1, &CTESTDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CTESTDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CTESTDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CTESTDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CTESTDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CTESTDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CTESTDlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CTESTDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CTESTDlg::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CTESTDlg::OnBnClickedCheck10)
	ON_BN_CLICKED(IDC_CHECK11, &CTESTDlg::OnBnClickedCheck11)
	ON_BN_CLICKED(IDC_CHECK12, &CTESTDlg::OnBnClickedCheck12)
	ON_BN_CLICKED(IDC_CHECK13, &CTESTDlg::OnBnClickedCheck13)
	ON_BN_CLICKED(IDC_CHECK14, &CTESTDlg::OnBnClickedCheck14)
	ON_BN_CLICKED(IDC_CHECK15, &CTESTDlg::OnBnClickedCheck15)
	ON_BN_CLICKED(IDC_CHECK16, &CTESTDlg::OnBnClickedCheck16)
	
	//ON_WM_TIMER()

	

	//ON_BN_CLICKED(IDC_CONNECTBUTTON2, &CTESTDlg::OnBnClickedConnectbutton2)
	ON_STN_CLICKED(IDC_CONNECTEDIT, &CTESTDlg::OnStnClickedConnectedit)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS2, &CTESTDlg::OnIpnFieldchangedIpaddress2)
	ON_BN_CLICKED(IDC_SENDBUTTON2, &CTESTDlg::OnBnClickedSendbutton2)
END_MESSAGE_MAP()



// CTESTDlg 消息处理程序

BOOL CTESTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	CComboBox *COMBO1 = (CComboBox*)GetDlgItem(IDC_COMBO1);
	COMBO1->SetCurSel(0);
	CComboBox *COMBO2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	COMBO2->SetCurSel(0);
	CComboBox *COMBO3 = (CComboBox*)GetDlgItem(IDC_COMBO4);
	COMBO3->SetCurSel(0);

	
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
		
	m_Status=-1;
	m_ServerSocket=NULL;
	m_ClientSocket=NULL;
	m_arIn=NULL;
	m_arOut=NULL;
	m_file=NULL;



	m_Connect="";
	m_IPAddress="192.168.1.17";
	m_IPAddress2 = "192.168.1.17";
	m_Port=8000;


	using namespace std;
	ifstream icin;
	icin.open("Data.txt");
	char temp[100];//定义一个数组，用来存放文本中的数组
	icin >> temp;//将文件中的数组输出到temp中去

	

	m_IPAddress = CString(temp);
	m_IPAddress2 = CString(temp);
	icin >> m_Port;

	
	
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT)->EnableWindow(FALSE);
	UpdateData(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control

	
}




void CTESTDlg::OnSysCommand(UINT nID, LPARAM IParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		if (nID == SC_MINIMIZE)
		{
			ShowWindow(SW_HIDE);
			ZeroMemory(&NotifyIcon, sizeof(NotifyIcon));
			NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
			NotifyIcon.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
			NotifyIcon.hWnd = m_hWnd;
			strcpy(NotifyIcon.szTip, "提示信息");
			NotifyIcon.uCallbackMessage = WM_NC;
			NotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
			//Shell_NotifyIcon(NIM_ADD, &NotifyIcon);
		}
		else
		{
			CDialog::OnSysCommand(nID, IParam);
		}
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTESTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTESTDlg::OnConnect() 
{
	using namespace std;
	ofstream ocout;//定义输出流的一个对象
	FILE f;

	
	ocout.open("data.txt");
	ocout << m_IPAddress + " ";
	ocout << m_IPAddress2 + " ";
	ocout << m_Port;
	ocout.close();
	//AfxMessageBox("OK!");

	
	CString msg;
	UpdateData(TRUE); 
	if (m_Status==0 ) //server
	{
		if (m_ServerSocket)
		{
			MessageBox("WindowsSocket initial failed!","Connect",MB_ICONSTOP);
			m_Connect="Please disconnect!";
			((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
			UpdateData(FALSE);
		}
		else
		{
			m_Connect="Waiting for Client...";
			((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
			UpdateData(FALSE);
			if(!AfxSocketInit())
			{
				MessageBox("WindowsSocket initial failed!","Send",MB_ICONSTOP);
				return;
			}


			

			m_ServerSocket = new CNewSocket;
			m_ServerSocket->m_Status = m_Status;
			m_ServerSocket->GetDlg(this);
			if (!m_ServerSocket->Create(m_Port))
			{
				MessageBox("WindowsSocket Create failed!","Send",MB_ICONSTOP);
			}
			else
				m_ServerSocket->Listen();
		}
	}
	else
	{
		if (m_Status==1)//Client
		{
			if(m_ClientSocket)
			{
				
				m_Connect="Please disconnect!";
				((CEdit*)GetDlgItem(MB_ICONSTOP))->SetWindowText(m_Connect);
				UpdateData(FALSE);
			}
			else
			{
				
				m_Connect="Connect to the Server...";
			    ((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
				UpdateData(FALSE);
				if (!AfxSocketInit())
				{
					MessageBox("WindowsSocket initial failed!","Receive",MB_ICONSTOP);
					return;
				}

			
				m_ClientSocket = new CNewSocket;
				m_ClientSocket->GetDlg(this);
				m_ClientSocket->m_Status=m_Status;
				if(!m_ClientSocket->Create())
				{
					MessageBox("WindowsSocket create failed!","Receive",MB_ICONSTOP);
					return;
				}
				else
				{
					if (!m_ClientSocket->Connect(m_IPAddress,m_Port))
					{
						CString str = m_Connect;
						SocketReset();
						m_Connect=str;
						m_Connect+="Error!";
						((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
						UpdateData(FALSE);
					}
					else
					{
						m_Connect+="OK!";
						((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
						m_file = new CSocketFile(m_ClientSocket);
						m_arIn = new CArchive(m_file,CArchive::load);
						m_arOut = new CArchive(m_file,CArchive::store);
					}
					UpdateData(FALSE);
				
					
				}
				/*
				int  iMode = 1;  //non-blocking mode is enabled.
				SOCKET ClientSocket = *m_ClientSocket;
				ioctlsocket(ClientSocket, FIONBIO, (u_long FAR*)&iMode);
				//rs = recvfrom(ClientSocket, buf, sizeof(buf), 0, (SOCKADDR FAR*)addr, int FAR * len);
				unsigned long flag = 1;
				if (ioctlsocket(ClientSocket, FIONBIO, &flag) != 0)
				{
					closesocket(ClientSocket);
					return false;
				}
				struct timeval timeout;

				fd_set r;

				int ret;
				connect(ClientSocket, (LPSOCKADDR)IDC_SERVERRADIO, 1000);
				FD_ZERO(&r);

				FD_SET(ClientSocket, &r);

				timeout.tv_sec = 5;

				timeout.tv_usec = 0;

				ret = select(0, 0, &r, 0, &timeout);

				if (ret <= 0)

				{

					closesocket(ClientSocket);

					return false;

				}*/

			}
		}
	}

	//KillTimer(1);//关闭定时器
	/*
	struct timeval timeout ; 

fd_set r; 

int ret; 
connect(m_Status, (LPSOCKADDR)sockAddr, sockAddr.Size());
FD_ZERO(&r); 

FD_SET(m_Status, &r);

timeout.tv_sec = 5; 

timeout.tv_usec =0; 

ret = select(0,0,&r,0,&timeout); 

if ( ret <= 0 ) 

{ 

closesocket(sock); 

return false; 

} 

*/
	CTESTDlg::OnKeepAlive();
	if (m_Status==-1)
	{
		msg="Please choose the status!";
		AfxMessageBox(msg);
	}

	
}
//在给客户端发送数据时做相关预处理

void CTESTDlg::OnSend() 
{
	//OnKeepAlive();
	 if (m_arOut)
	  {
		    if (m_Status==0)
			  {
				     //UpdateData(TRUE);
					 m_arOut->Write(tbuffer , sizeof(PCmdWlanToCPU));
					
					 //*m_arOut<<m_Output;
					 m_arOut->Flush(); 
					 
			  }
			  else 
			    {
					 //UpdateData(TRUE);
					 //*m_arOut<<m_Output;
					 m_arOut->Write(tbuffer, sizeof(PCmdWlanToCPU));
					 //m_arOut->Write((char * a), sizeof());
					 m_arOut->Flush(); 
					
			  }
			
	  }

	  else AfxMessageBox("Not connected!");
	//  m_Connect = "发送成功";
	 // ((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
	 if ( state == 0 )
		  MessageBox("请按确认键！");
	  state = 0; 

	  int i;
	  for (i = 0; i < sizeof(PCmdWlanToCPU); i = i + 1)
	  {

		  tbuffer[i] =0;

	  }
	//  free(ptr);
}

//接受链接请求，并保存与发起链接请求的客户端进行通信Socket
//为新的Socket注册异步事件，注意没有Accept事件
void CTESTDlg::OnAccept()
{
	m_Connect+="OK!";
	((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
	UpdateData(FALSE);
	m_ClientSocket=new CNewSocket;
	m_ClientSocket->GetDlg(this);
	m_ServerSocket->Accept(*m_ClientSocket);
	m_ClientSocket->m_Status=m_ServerSocket->m_Status;
	m_file=new CSocketFile(m_ClientSocket); 
	m_arIn=new CArchive(m_file, CArchive::load); 
	m_arOut=new CArchive(m_file, CArchive::store); 

}
//读出网络缓冲区中的数据包
void CTESTDlg::OnReceive()
{
	//*m_arIn>>m_Input; 
	//UpdateData(FALSE); 

	BYTE cbDataBuffer[1024],i=0;
	memset(cbDataBuffer,0,sizeof(cbDataBuffer));
	int ret = m_ClientSocket->Receive(cbDataBuffer,1024);
	if (ret <= 0)
	{
		MessageBox("接受数据不大于零！");
	}
	else
	{
		m_Input += CString(cbDataBuffer);
		UpdateData(FALSE);
		//MessageBox("接受数据！");
	}
}

void CTESTDlg::OnDisconnect() 
{
	 if (m_arOut!=NULL)
	  {
			SocketReset();
			m_Connect="Disconnected!";
			((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
			UpdateData(FALSE);
	  }
}
//结束相应客户端的通信，释放相应资源
void CTESTDlg::OnClose()
{
	if (m_ClientSocket->m_Status == 0)
	{
		m_Connect = "Client ";
		((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
	}
	else{
		m_Connect = "Server ";
		
	
	m_Connect+="has disconnected!"; 
	((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
	}
	UpdateData(FALSE);
}

void CTESTDlg::SocketReset()
{
	if (m_arIn!=NULL) 
	{ 
		delete m_arIn;
		m_arIn=NULL;
	}
	if (m_arOut!=NULL) 
	{
		 delete m_arOut;
		 m_arOut=NULL;
	} 
	if (m_file!=NULL) 
	{
		delete m_file;
		m_file=NULL;
	}
	if (m_ClientSocket!=NULL) 
	{
		delete m_ClientSocket;
		m_ClientSocket=NULL;
	}
	if (m_ServerSocket!=NULL)
	{ 
		delete m_ServerSocket;
		m_ServerSocket=NULL;
	}
	m_Connect="";
	UpdateData(FALSE);
}

void CTESTDlg::OnServerradio() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT)->EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CTESTDlg::OnClientradio() 
{ 
	UpdateData(TRUE);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_PORT)->EnableWindow(TRUE);
	UpdateData(FALSE);
}

//采用心跳机制，防止非正常断开连接,设置KeepAlive
void CTESTDlg::OnKeepAlive()
{
BOOL   bKeepAlive = TRUE;

    SOCKET ClientSocket = *m_ClientSocket;

	int nRet = ::setsockopt(ClientSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&bKeepAlive, sizeof(bKeepAlive));
if (nRet != 0)
{
	AfxMessageBox("1");
	return ;
}


tcp_keepalive    inKeepAlive = { 0 };   //输入参数     
unsigned   long   ulInLen = sizeof(tcp_keepalive);

tcp_keepalive    outKeepAlive = { 0 };   //输出参数     
unsigned   long   ulOutLen = sizeof(tcp_keepalive);

unsigned   long   ulBytesReturn = 0;

//设置socket的keep   alive为10秒，并且发送次数为3次     
inKeepAlive.onoff = 1;
inKeepAlive.keepaliveinterval = 1000;   //两次KeepAlive探测间的时间间隔     
inKeepAlive.keepalivetime = 1000;   //开始首次KeepAlive探测前的TCP空闭时间     

nRet = WSAIoctl(ClientSocket,
	SIO_KEEPALIVE_VALS,
	(LPVOID)&inKeepAlive,
	ulInLen,
	(LPVOID)&outKeepAlive,
	ulOutLen,
	&ulBytesReturn,
	NULL,
	NULL);
if (SOCKET_ERROR == nRet)
{
	AfxMessageBox(" ");
	return;
}
}
/*
//计时器函数
void CTESTDlg::OnTimer(UINT nIDEvent)
{
	SetTimer(1, 5000, NULL);
	switch (nIDEvent)
	{
	case 1:
	{
			  //OnDisconnect();
			  break;
	}
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}*/






void CTESTDlg::OnEnChangeInputedit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	/*
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%Y-%m-%d %H:%M:%S");
	SetDlgItemText(IDC_INPUTEDIT, strTime);        //显示系统时间
	*/
}


void CTESTDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CTESTDlg::OnIpnFieldchangedIpaddress(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	*pResult = 0;
	
}


void CTESTDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




void CTESTDlg::OnEnChangePort()
{

	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CTESTDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	
	
}

void CTESTDlg::OnCbnSelchangeCombo2()
{
	// TODO:  在此添加控件通知处理程序代码

	

}




void CTESTDlg::OnCbnSelchangeCombo4()
{
	// TODO:  在此添加控件通知处理程序代码

	

}
/***********************************************************/

unsigned char AscToHex(unsigned char aHex){
	if ((aHex >= 0) && (aHex <= 9))
		aHex += 0x30;
	else if ((aHex >= 10) && (aHex <= 15))//A-F
		aHex += 0x37;
	else aHex = 0xff;
	return aHex;
}

char  HexToASCII(unsigned char  data_hex)
{
	char  ASCII_Data;
	ASCII_Data = data_hex & 0x0F;
	if (ASCII_Data<10)
		ASCII_Data = ASCII_Data + 0x30; //‘0--9’
	else
		ASCII_Data = ASCII_Data + 0x37;       //‘A--F’
	return ASCII_Data;
}






int m_H;

void CTESTDlg::OnBnClickedButton1()

{

	//V = 1;
	//D = 2;
	//F = 3;

	CString  strTemp, strTemp1, strTemp2;
	PCmdWlanToCPU *a;
	short A; LONG64 f; LONG64 d1, d2;
	a = (PCmdWlanToCPU *)malloc(sizeof(PCmdWlanToCPU));


	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(strTemp);
	char *p = (LPSTR)(LPCTSTR)strTemp;
	//a->VolID = *p;
	//a->FreqVal = m_F;

	((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowText(strTemp1);
	char *q = (LPSTR)(LPCTSTR)strTemp1;
	//a->FreqID = *q;


	((CComboBox*)GetDlgItem(IDC_COMBO4))->GetWindowText(strTemp2);
	char *r = (LPSTR)(LPCTSTR)strTemp2;
	
	
	
	//幅值的转换
	//int a1;
	 CString test,test1,test2;
	((CEdit*)GetDlgItem(IDC_EDIT5))->GetWindowText(test);	
	((CEdit*)GetDlgItem(IDC_EDIT6))->GetWindowText(test1);
	((CEdit*)GetDlgItem(IDC_EDIT7))->GetWindowText(test2);
	 double V = atof(test);
	 double F = atof(test1);
	 double D = atof(test2);
	
	
	
	if (strTemp == "V")
	{
		if (test == '0')
		{
			A = 0;
		}
		else
		{
			//A = 1000 * (3300 / 256)*V*1.00;
			A = (51000 / ((V* 1.00 * 5) - 1) - 3000) / 10;
			//A = A / 1000;

		}
			
	}
	
	else if (strTemp == "mV")
	{	
		if (test == '0')
		{
			A = 0;
		}
		else
		{
			//A = (3300 / 256)*V*1.00;
			A = (51000 / ((V* 1.00 / 200) - 1) - 3000) / 10;
			//A = A / 1000;
		}
		
	}
  
//TRACE("A=%X",A);

	//频率的转换
	//int i;
	if (strTemp2 == "KHZ")
	{
		f = (1.00)*((1e6) / 5) / F;
		
		//i = 1;
	}
	 if (strTemp2 == "MHZ")
	{
		 f = (1.00)*((1e3) / 5) / F;
		//i = 2;
	}
	 if (strTemp2 == "HZ")
	{
		 f = (1.00)*((1e9) / 5) / F;
	//	i = 0;
	}
	
	//占空比的转换
	 if (strTemp1 == "‰oo")
	 {
		 d1 = (f *D*1.00) / 100000;
		 d2 = f*1.00 - f *D*1.00 / 100000;
	 }
	else if (strTemp1 == "‰o")
	{
		d1 = (f *D*1.00) / 10000;
		d2 = f*1.00- f *D*1.00 / 10000;				
	}

	else if (strTemp1 == "‰")
	{
		d1 = (f *D*1.00) / 1000;
		d2 = f*1.00 - f *D*1.00 / 1000;
	}
	else if (strTemp1 == "%")
	{
		d1 = (f *D*1.00) / 100;
		d2 = f*1.00 - f *D*1.00 / 100;
	}
	//TRACE("%d,",D_H,D_L);

	
	m_A = A;
	m_H = f;
	m_D_H = d1;
	m_D_L = d2;
	A = NULL;
	f = NULL;
	d1 = NULL;
	d2 = NULL;

	//m_H=htons(m_H);
	//m_D_H = htons(m_D_H);
	//m_D_L = htons(m_D_L);
	//m_A=htons(m_A);
	



	a->StartID = 0x7E;
	a->mode = m;
	a->Res1 = 0x00;
	//a->Res2 = 0x00c0;
	a->FreqVal = m_H;
	a->DutyVal1 = m_D_H;
	a->DutyVal2 = m_D_L;
	a->VolVal = m_A;
	a->EndID = 0X7F;

	int i;
	
	a->Channle[0] = 0x00;
	a->Channle[1] = 0x00;
	for (i = 0; i < 16; i++)
	{
		if (i < 8){
			a->Channle[0] = (CH[i] << i) | a->Channle[0];
		}
		else {
			a->Channle[1] = (CH[i] << (i-8)) | a->Channle[1];
		}
	}
	


   char *ptr = (char*)a;

	for (i = 0; i < sizeof(PCmdWlanToCPU); i = i + 1)
	{
		
		tbuffer[i] = *(ptr + i);	
		
	}
	free(a);
	state = 1;

	
	UpdateData(true);


}


void CTESTDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CTESTDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CTESTDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CTESTDlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

	char m;
void CTESTDlg::OnBnClickedRadio1()
{
	
	// TODO: Add your control notification handler code here
	//UpdateData(true);
	if (m_A>0)
	{
		//m_A = m_A;
		m = 1;
	}
	else
	{
		//m_A =- m_A;
		m = 0;
	}
	UpdateData(true);
}


void CTESTDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	//UpdateData(true);
	if (m_A<0)
	{
	//	m_A = m_A;
		m = 1;
	}
	else
	{
	//	m_A = -m_A;
		m = 0;
	}
	UpdateData(true);
}

//char C[16];

void CTESTDlg::OnBnClickedCheck1()
{
	// TODO:  在此添加控件通知处理程序代码
	//UINT iChecked1;
	iChecked1 = IsDlgButtonChecked(IDC_CHECK1);
	if (iChecked1 == BST_CHECKED) 
	{
		CH[0] = 1;
		//TRACE("HAHA");
	}
	else
	{
		CH[0] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck2()
{
	// TODO:  在此添加控件通知处理程序代码
	
	iChecked1 = IsDlgButtonChecked(IDC_CHECK2);
	if (iChecked1 == BST_CHECKED)
	{
		CH[1] = 1;
	}
	else
	{
		CH[1] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck3()
{
	// TODO:  在此添加控件通知处理程序代码
	
	iChecked1 = IsDlgButtonChecked(IDC_CHECK3);
	if (iChecked1 == BST_CHECKED)
	{
		CH[2] = 1;
	}
	else
	{
		CH[2] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck4()
{
	// TODO:  在此添加控件通知处理程序代码

	iChecked1 = IsDlgButtonChecked(IDC_CHECK4);
	if (iChecked1 == BST_CHECKED)
	{
		CH[3] = 1;
	}
	else
	{
		CH[3] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck5()
{
	// TODO:  在此添加控件通知处理程序代码
	
	iChecked1 = IsDlgButtonChecked(IDC_CHECK5);
	if (iChecked1 == BST_CHECKED)
	{
		CH[4] = 1;
	}
	else
	{
		CH[4] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck6()
{
	// TODO:  在此添加控件通知处理程序代码
	
	iChecked1 = IsDlgButtonChecked(IDC_CHECK6);
	if (iChecked1 == BST_CHECKED)
	{
		CH[5] = 1;
	}
	else
	{
		CH[5] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck7()
{
	// TODO:  在此添加控件通知处理程序代码

	iChecked1 = IsDlgButtonChecked(IDC_CHECK7);
	if (iChecked1 == BST_CHECKED)
	{
		CH[6] = 1;
	}
	else
	{
		CH[6] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck8()
{
	// TODO:  在此添加控件通知处理程序代码

	iChecked1 = IsDlgButtonChecked(IDC_CHECK8);
	if (iChecked1 == BST_CHECKED)
	{
		CH[7] = 1;
	}
	else
	{
		CH[7] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck9()
{
	// TODO:  在此添加控件通知处理程序代码
	
	iChecked1 = IsDlgButtonChecked(IDC_CHECK9);
	if (iChecked1 == BST_CHECKED)
	{
		CH[8] = 1;
	}
	else
	{
		CH[8] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck10()
{
	// TODO:  在此添加控件通知处理程序代码
	
	iChecked1 = IsDlgButtonChecked(IDC_CHECK10);
	if (iChecked1 == BST_CHECKED)
	{
		CH[9] = 1;
	}
	else
	{
		CH[9] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck11()
{
	// TODO:  在此添加控件通知处理程序代码

	iChecked1 = IsDlgButtonChecked(IDC_CHECK11);
	if (iChecked1 == BST_CHECKED)
	{
		CH[10] = 1;
	}
	else
	{
		CH[10] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck12()
{
	// TODO:  在此添加控件通知处理程序代码

	iChecked1 = IsDlgButtonChecked(IDC_CHECK12);
	if (iChecked1 == BST_CHECKED)
	{
		CH[11] = 1;
	}
	else
	{
		CH[11] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck13()
{
	// TODO:  在此添加控件通知处理程序代码

	iChecked1 = IsDlgButtonChecked(IDC_CHECK13);
	if (iChecked1 == BST_CHECKED)
	{
		CH[12] = 1;
	}
	else
	{
		CH[12] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck14()
{
	// TODO:  在此添加控件通知处理程序代码

	iChecked1 = IsDlgButtonChecked(IDC_CHECK14);
	if (iChecked1 == BST_CHECKED)
	{
		CH[13] = 1;
	}
	else
	{
		CH[13] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck15()
{
	// TODO:  在此添加控件通知处理程序代码

	iChecked1 = IsDlgButtonChecked(IDC_CHECK15);
	if (iChecked1 == BST_CHECKED)
	{
		CH[14] = 1;
	}
	else
	{
		CH[14] = 0;
	}
}


void CTESTDlg::OnBnClickedCheck16()
{
	// TODO:  在此添加控件通知处理程序代码

	iChecked1 = IsDlgButtonChecked(IDC_CHECK16);
	if (iChecked1 == BST_CHECKED)
	{
		CH[15] = 1;
	}
	else
	{
		CH[15] = 0;
	}
}
LRESULT CTESTDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_LBUTTONDOWN || lParam == WM_RBUTTONDOWN)
	{
		ShowWindow(SW_SHOW);
	}
	return 1;
}



void CTESTDlg::OnStnClickedConnectedit()
{
	// TODO: Add your control notification handler code here
}


void CTESTDlg::OnIpnFieldchangedIpaddress2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

}


void CTESTDlg::OnBnClickedSendbutton2()
{
	state = 1;
	// TODO: Add your control notification handler code here
	CTESTDlg::OnConnect();
	CTESTDlg::OnBnClickedButton1();
	if (m_arOut)
	{
		if (m_Status == 0)
		{
			//UpdateData(TRUE);
			m_arOut->Write(tbuffer, sizeof(PCmdWlanToCPU));

			//*m_arOut<<m_Output;
			m_arOut->Flush();

		}
		else
		{
			//UpdateData(TRUE);
			//*m_arOut<<m_Output;
			m_arOut->Write(tbuffer, sizeof(PCmdWlanToCPU));
			//m_arOut->Write((char * a), sizeof());
			m_arOut->Flush();

		}

	}

	else AfxMessageBox("Not connected!");
	//  m_Connect = "发送成功";
	// ((CEdit*)GetDlgItem(IDC_INPUTEDIT))->SetWindowText(m_Connect);
	/*if (state == 0)
		MessageBox("请按确认键！");
	state = 0;*/

	int i;
	for (i = 0; i < sizeof(PCmdWlanToCPU); i = i + 1)
	{

		tbuffer[i] = 0;

	}
}
