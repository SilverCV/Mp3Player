
// MP3PlayerDlg.h : 头文件
//

#pragma once
#include <mmsystem.h>
#include <Digitalv.h>
#pragma  comment(lib,"winmm.lib")
// CMP3PlayerDlg 对话框
class CMP3PlayerDlg : public CDialogEx
{
// 构造
public:
	CMP3PlayerDlg(CWnd* pParent = NULL);	// 标准构造函数
private:
	HWND m_hwnd;
	DWORD m_Deviced;
	MCI_OPEN_PARMS m_mciParams;
	CString m_filePath;
	CString m_fileName;
	int m_volume;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MP3PLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
