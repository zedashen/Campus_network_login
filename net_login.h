
// net_login.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cnet_loginApp: 
// �йش����ʵ�֣������ net_login.cpp
//

class Cnet_loginApp : public CWinApp
{
public:
	Cnet_loginApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cnet_loginApp theApp;