
// MP3PlayerDlg.h : ͷ�ļ�
//

#pragma once
#include <mmsystem.h>
#include <Digitalv.h>
#pragma  comment(lib,"winmm.lib")
// CMP3PlayerDlg �Ի���
class CMP3PlayerDlg : public CDialogEx
{
// ����
public:
	CMP3PlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��
private:
	HWND m_hwnd;
	DWORD m_Deviced;
	MCI_OPEN_PARMS m_mciParams;
	CString m_filePath;
	CString m_fileName;
	int m_volume;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MP3PLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedSelect();
private:
	void Load(HWND hwnd, CString filepath);
public:
	afx_msg void OnNMCustomdrawVolume(NMHDR *pNMHDR, LRESULT *pResult);
};
