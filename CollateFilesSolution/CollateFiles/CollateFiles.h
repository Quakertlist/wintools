
// CollateFiles.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCollateFilesApp: 
// �йش����ʵ�֣������ CollateFiles.cpp
//

class CCollateFilesApp : public CWinApp
{
public:
	CCollateFilesApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCollateFilesApp theApp;