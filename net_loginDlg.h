
// net_loginDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// Cnet_loginDlg 对话框
class Cnet_loginDlg : public CDialogEx
{
// 构造
public:
	Cnet_loginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NET_LOGIN_DIALOG };

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
    afx_msg void OnBnClickedOk();
    CString Cusername;
    CString Cpassword;
    afx_msg void OnBnClickedCloseButton();
    CComboBox control_combobox;
    CString type_combobox;
    afx_msg void OnCbnSelchangeChooseCombo();
};
