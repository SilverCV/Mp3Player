
// MP3PlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MP3Player.h"
#include "MP3PlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMP3PlayerDlg 对话框



CMP3PlayerDlg::CMP3PlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MP3PLAYER_DIALOG, pParent)
	, m_volume(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMP3PlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_VOLUME, m_volume);
	DDV_MinMaxInt(pDX, m_volume, 0, 100);
}

BEGIN_MESSAGE_MAP(CMP3PlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, &CMP3PlayerDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_PAUSE, &CMP3PlayerDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_STOP, &CMP3PlayerDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_SELECT, &CMP3PlayerDlg::OnBnClickedSelect)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_VOLUME, &CMP3PlayerDlg::OnNMCustomdrawVolume)
END_MESSAGE_MAP()


// CMP3PlayerDlg 消息处理程序

BOOL CMP3PlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMP3PlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMP3PlayerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMP3PlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMP3PlayerDlg::OnBnClickedPlay()
{
	Load(m_hWnd, m_filePath);
	MCI_PLAY_PARMS mci_play_params;
	mci_play_params.dwCallback = (DWORD)m_hwnd;
	mci_play_params.dwFrom = 0;	//从0 开始
	mciSendCommand(m_Deviced, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&m_mciParams);
	// TODO: 在此添加控件通知处理程序代码
}


void CMP3PlayerDlg::OnBnClickedPause()
{
	CString keep;
	
	GetDlgItem(IDC_PAUSE)->GetWindowTextW(keep);
	if (keep.Compare(L"继续") == 0)
	{
		mciSendCommand(m_Deviced, MCI_RESUME, 0, 0);	//恢复播放
		GetDlgItem(IDC_PAUSE)->SetWindowText(L"暂停");
	}
	// TODO: 在此添加控件通知处理程序代码
	if (keep.Compare(L"暂停") == 0)
	{
		mciSendCommand(m_Deviced, MCI_PAUSE, 0, 0);	//停止播放
		GetDlgItem(IDC_PAUSE)->SetWindowText(L"继续");
	}
}


void CMP3PlayerDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendCommand(m_Deviced, MCI_STOP, 0, 0);	//停止播放
	mciSendCommand(m_Deviced, MCI_CLOSE, 0, 0);	//清空当前播放文件
}


void CMP3PlayerDlg::OnBnClickedSelect()
{
	
	CString fileFilter = 
		L"mp3文件(*.mp3)|*.mp3|wma文件(*.wma)|*.wma|wav文件(*.wav)|*.wav|所有文件(*.*)|*.*||";
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, fileFilter);
	if (dlg.DoModal() == IDOK) 
	{
		m_filePath = dlg.GetPathName();
		m_fileName = dlg.GetFileName();
		GetDlgItem(IDC_FILENAME)->SetWindowText(m_fileName);
		
	}
	// TODO: 在此添加控件通知处理程序代码
}
void CMP3PlayerDlg::Load(HWND hwnd, CString filepath)
{
	m_hwnd = hwnd;
	mciSendCommand(m_Deviced, MCI_CLOSE, 0, 0);
	m_mciParams.lpstrElementName = filepath;//将音乐文件路径传给设备
	DWORD dwReturn;
	dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&m_mciParams);
	if (dwReturn)
	{
		wchar_t buff[256];
		mciGetErrorString(dwReturn, buff, 253);
		MessageBox(buff, L"错误", MB_OK | MB_OKCANCEL);
	}
	m_Deviced = m_mciParams.wDeviceID;
}

void CMP3PlayerDlg::OnNMCustomdrawVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_volume = ((CSliderCtrl*)GetDlgItem(IDC_VOLUME))->GetPos();
	MCI_DGV_SETAUDIO_PARMS mci_dgv_volums;
	mci_dgv_volums.dwCallback = NULL;
	mci_dgv_volums.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mci_dgv_volums.dwValue = m_volume;
	mciSendCommand(m_Deviced, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&mci_dgv_volums);
	*pResult = 0;
}
