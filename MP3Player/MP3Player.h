
// MP3Player.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMP3PlayerApp: 
// �йش����ʵ�֣������ MP3Player.cpp
//

class CMP3PlayerApp : public CWinApp
{
public:
	CMP3PlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMP3PlayerApp theApp;