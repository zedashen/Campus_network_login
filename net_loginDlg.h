
// net_loginDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// Cnet_loginDlg �Ի���
class Cnet_loginDlg : public CDialogEx
{
// ����
public:
	Cnet_loginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NET_LOGIN_DIALOG };

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
    afx_msg void OnBnClickedOk();
    CString Cusername;
    CString Cpassword;
    afx_msg void OnBnClickedCloseButton();
    CComboBox control_combobox;
    CString type_combobox;
    afx_msg void OnCbnSelchangeChooseCombo();
};
