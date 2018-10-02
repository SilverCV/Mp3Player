
// MP3PlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MP3Player.h"
#include "MP3PlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMP3PlayerDlg �Ի���



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


// CMP3PlayerDlg ��Ϣ�������

BOOL CMP3PlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMP3PlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMP3PlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMP3PlayerDlg::OnBnClickedPlay()
{
	Load(m_hWnd, m_filePath);
	MCI_PLAY_PARMS mci_play_params;
	mci_play_params.dwCallback = (DWORD)m_hwnd;
	mci_play_params.dwFrom = 0;	//��0 ��ʼ
	mciSendCommand(m_Deviced, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&m_mciParams);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMP3PlayerDlg::OnBnClickedPause()
{
	CString keep;
	
	GetDlgItem(IDC_PAUSE)->GetWindowTextW(keep);
	if (keep.Compare(L"����") == 0)
	{
		mciSendCommand(m_Deviced, MCI_RESUME, 0, 0);	//�ָ�����
		GetDlgItem(IDC_PAUSE)->SetWindowText(L"��ͣ");
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (keep.Compare(L"��ͣ") == 0)
	{
		mciSendCommand(m_Deviced, MCI_PAUSE, 0, 0);	//ֹͣ����
		GetDlgItem(IDC_PAUSE)->SetWindowText(L"����");
	}
}


void CMP3PlayerDlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mciSendCommand(m_Deviced, MCI_STOP, 0, 0);	//ֹͣ����
	mciSendCommand(m_Deviced, MCI_CLOSE, 0, 0);	//��յ�ǰ�����ļ�
}


void CMP3PlayerDlg::OnBnClickedSelect()
{
	
	CString fileFilter = 
		L"mp3�ļ�(*.mp3)|*.mp3|wma�ļ�(*.wma)|*.wma|wav�ļ�(*.wav)|*.wav|�����ļ�(*.*)|*.*||";
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, fileFilter);
	if (dlg.DoModal() == IDOK) 
	{
		m_filePath = dlg.GetPathName();
		m_fileName = dlg.GetFileName();
		GetDlgItem(IDC_FILENAME)->SetWindowText(m_fileName);
		
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CMP3PlayerDlg::Load(HWND hwnd, CString filepath)
{
	m_hwnd = hwnd;
	mciSendCommand(m_Deviced, MCI_CLOSE, 0, 0);
	m_mciParams.lpstrElementName = filepath;//�������ļ�·�������豸
	DWORD dwReturn;
	dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&m_mciParams);
	if (dwReturn)
	{
		wchar_t buff[256];
		mciGetErrorString(dwReturn, buff, 253);
		MessageBox(buff, L"����", MB_OK | MB_OKCANCEL);
	}
	m_Deviced = m_mciParams.wDeviceID;
}

void CMP3PlayerDlg::OnNMCustomdrawVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_volume = ((CSliderCtrl*)GetDlgItem(IDC_VOLUME))->GetPos();
	MCI_DGV_SETAUDIO_PARMS mci_dgv_volums;
	mci_dgv_volums.dwCallback = NULL;
	mci_dgv_volums.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mci_dgv_volums.dwValue = m_volume;
	mciSendCommand(m_Deviced, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&mci_dgv_volums);
	*pResult = 0;
}
