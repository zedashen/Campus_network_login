
// net_loginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "net_login.h"
#include "net_loginDlg.h"
#include "afxdialogex.h"
#include <curl.h>
#include <string>
#include <assert.h>   
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString a("������");
CString b("������");
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
size_t header_callback(const char  *ptr, size_t size, size_t nmemb, std::string *stream)    //ͷ���ص�����
{
    assert(stream != NULL);
    size_t len = size * nmemb;
    stream->append(ptr, len);
    return len;
}
size_t call_wirte_func(const char *ptr, size_t size, size_t nmemb, std::string *stream)    //������ص�����
{
    assert(stream != NULL);
    size_t len = size * nmemb;
    stream->append(ptr, len);
    return len;
}
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cnet_loginDlg �Ի���



Cnet_loginDlg::Cnet_loginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cnet_loginDlg::IDD, pParent)
    , Cusername(_T(""))
    , Cpassword(_T(""))
    , type_combobox(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cnet_loginDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_USERNAME_EDIT, Cusername);
    DDX_Text(pDX, IDC_PASSWORD_EDIT, Cpassword);
    DDX_Control(pDX, IDC_CHOOSE_COMBO, control_combobox);
    DDX_CBString(pDX, IDC_CHOOSE_COMBO, type_combobox);
}

BEGIN_MESSAGE_MAP(Cnet_loginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &Cnet_loginDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_CLOSE_BUTTON, &Cnet_loginDlg::OnBnClickedCloseButton)
    ON_CBN_SELCHANGE(IDC_CHOOSE_COMBO, &Cnet_loginDlg::OnCbnSelchangeChooseCombo)
END_MESSAGE_MAP()


// Cnet_loginDlg ��Ϣ�������

BOOL Cnet_loginDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
    control_combobox.AddString(a);
    control_combobox.AddString(b);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cnet_loginDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cnet_loginDlg::OnPaint()
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
HCURSOR Cnet_loginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cnet_loginDlg::OnBnClickedOk()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CString nettype;
    UpdateData(TRUE);
    control_combobox.GetWindowText(nettype);
    std::string szbuffer;
    std::string szheader_buffer;
    if (nettype != a&&nettype != b)                                          //��½��Ϣ������֤
        MessageBox(_T("����ѡ����������"), _T("����"));
    else if (Cusername.IsEmpty() || Cpassword.IsEmpty())
        MessageBox(_T("�������������ĵ�½��Ϣ"), _T("����"));
    else
    {
        CString ccommand;
        char *command;
        ccommand = _T("username=") + Cusername + _T("&password=") + Cpassword + _T("&B1=");             //����POST����
        USES_CONVERSION;
       
        command = W2A(ccommand);
        CURL *curl;
        CURLcode res;
        struct curl_slist *headers1 = NULL , *headers2 = NULL, *headers3 = NULL;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl){

            //http����ͷ
            headers1 = curl_slist_append(headers1, "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.110 Safari/537.36");    //ģ�������
            headers1 = curl_slist_append(headers1, "Host:passport.csdn.net");
            headers1 = curl_slist_append(headers1, "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
            headers1 = curl_slist_append(headers1, "Accept-Language:zh-CN,zh;q=0.8");
            headers1 = curl_slist_append(headers1, "Accept-Encoding:gzip, deflate");
            headers1 = curl_slist_append(headers1, "Content-Length: 41");
            headers1 = curl_slist_append(headers1, "Cache-Control:no-cache");
            headers1 = curl_slist_append(headers1, "Upgrade-Insecure-Requests: 1");
            headers1 = curl_slist_append(headers1, "X-Requested-With:XMLHttpRequest");
            headers1 = curl_slist_append(headers1, "Connection:keep-alive");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS,command);
            curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.168.46/?$USERURL");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, call_wirte_func);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szbuffer);
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &szheader_buffer);
            res = curl_easy_perform(curl);                           //����
            curl_easy_cleanup(curl);
            std::string::size_type idx = szheader_buffer.find("Location:");         //�и�ͷ���ҵ�Ҫ�õ���Ϣ
            szheader_buffer=szheader_buffer.substr(idx + 1);
            idx = szheader_buffer.find(":");
            szheader_buffer = szheader_buffer.substr(idx + 1);
            idx= szheader_buffer.find("\n");
            szheader_buffer = szheader_buffer.substr(0,idx);
            curl_slist_free_all(headers1);
            curl = curl_easy_init();
            headers2 = curl_slist_append(headers2, "Connection: keep-alive");
            headers2 = curl_slist_append(headers2, "Cache-Control: max-age=0");
            headers2 = curl_slist_append(headers2, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
            headers2 = curl_slist_append(headers2, "Upgrade-Insecure-Requests: 1");
            headers2 = curl_slist_append(headers2, "Accept-Encoding: gzip, deflate, sdch");
            headers2 = curl_slist_append(headers2, "Accept-Language: zh-CN,zh;q=0.8,en;q=0.6");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers2);
            curl_easy_setopt(curl, CURLOPT_URL, szheader_buffer);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, call_wirte_func);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szbuffer);
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &szheader_buffer);
            res = curl_easy_perform(curl);       //http����
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers2);
            if (nettype == a)                 //ѡ�������
            {
                idx = szbuffer.find("addInput");                    //�и��ȡ
                szbuffer = szbuffer.substr(idx + 8);
                idx = szbuffer.find("addInput");
                szbuffer = szbuffer.substr(idx + 8);
                idx = szbuffer.find(",");
                szbuffer = szbuffer.substr(idx + 1);
                idx = szbuffer.find(",");
                szbuffer = szbuffer.substr(idx + 1);
                idx = szbuffer.find(",");
                szbuffer = szbuffer.substr(idx + 2);
                idx = szbuffer.find("'");
                szbuffer = szbuffer.substr(0,idx);
                std::string postnumber = "POSTLanmanUserURL&Lanmannumber=" + szbuffer;
                curl = curl_easy_init();
                headers3 = curl_slist_append(headers3, "Connection: keep-alive");
                headers3 = curl_slist_append(headers3, "Pragma: no-cache");
                headers3 = curl_slist_append(headers3, "Cache-Control: no-cache");
                headers3 = curl_slist_append(headers3, "Accept: application/json, text/javascript, */*; q=0.01");
                headers3 = curl_slist_append(headers3, "X-Requested-With: XMLHttpRequest");
                headers3 = curl_slist_append(headers3, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
                headers3 = curl_slist_append(headers3, "Referer: http://192.168.168.46:9999/?LanmanUserURL=$USERURL");
                headers3 = curl_slist_append(headers3, "Accept-Encoding: gzip, deflate");
                headers3 = curl_slist_append(headers3, "Accept-Language: zh-CN,zh;q=0.8,en;q=0.6");
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers3);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postnumber);
                curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.168.46:9999/");
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, call_wirte_func);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szbuffer);
                curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
                curl_easy_setopt(curl, CURLOPT_HEADERDATA, &szheader_buffer);
                res = curl_easy_perform(curl);                //POST��ť
                curl_easy_cleanup(curl);
                curl_slist_free_all(headers3);
                USES_CONVERSION;
                CString temp;
                const char *t = szbuffer.c_str();
                temp = t;
                MessageBox(temp, _T("��½��ʾ"));

            }
            else if (nettype == b)               //������
            {
                idx = szbuffer.find("addInput");
                szbuffer = szbuffer.substr(idx + 8);
                idx = szbuffer.find(",");
                szbuffer = szbuffer.substr(idx + 1);
                idx = szbuffer.find(",");
                szbuffer = szbuffer.substr(idx + 1);
                idx = szbuffer.find(",");
                szbuffer = szbuffer.substr(idx + 2);
                idx = szbuffer.find("'");
                szbuffer = szbuffer.substr(0, idx);
                std::string postnumber = "POSTLanmanUserURL&Lanmannumber=" + szbuffer;
                curl = curl_easy_init();
                headers3 = curl_slist_append(headers3, "Connection: keep-alive");
                headers3 = curl_slist_append(headers3, "Pragma: no-cache");
                headers3 = curl_slist_append(headers3, "Cache-Control: no-cache");
                headers3 = curl_slist_append(headers3, "Accept: application/json, text/javascript, */*; q=0.01");
                headers3 = curl_slist_append(headers3, "X-Requested-With: XMLHttpRequest");
                headers3 = curl_slist_append(headers3, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
                headers3 = curl_slist_append(headers3, "Referer: http://192.168.168.46:9999/?LanmanUserURL=$USERURL");
                headers3 = curl_slist_append(headers3, "Accept-Encoding: gzip, deflate");
                headers3 = curl_slist_append(headers3, "Accept-Language: zh-CN,zh;q=0.8,en;q=0.6");
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers3);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postnumber);
                curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.168.46:9999/");
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, call_wirte_func);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szbuffer);
                curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
                curl_easy_setopt(curl, CURLOPT_HEADERDATA, &szheader_buffer);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                curl_slist_free_all(headers3);
                idx = szbuffer.find_last_of("<br>");
                szbuffer = szbuffer.substr(0, idx);
                USES_CONVERSION;
                CString temp;
                const char *t = szbuffer.c_str();
                temp = t;
                MessageBox(temp, _T("��½��ʾ"));

            }
        }
    }
}

void Cnet_loginDlg::OnBnClickedCloseButton()              //�رհ�ť
{
    CString nettype;
    UpdateData(TRUE);
    control_combobox.GetWindowText(nettype);
    std::string szbuffer;
    std::string szheader_buffer;
    if (nettype != a&&nettype != b)
        MessageBox(_T("����ѡ����������"), _T("����"));
    else if (Cusername.IsEmpty() || Cpassword.IsEmpty())
        MessageBox(_T("�������������ĵ�½��Ϣ"), _T("����"));
    else
    {
        CString ccommand;
        char *command;
        ccommand = _T("username=") + Cusername + _T("&password=") + Cpassword + _T("&B1=");
        USES_CONVERSION;

        command = W2A(ccommand);
        CURL *curl;
        CURLcode res;
        struct curl_slist *headers1 = NULL, *headers2 = NULL, *headers3 = NULL;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl){

            //http����ͷ
            headers1 = curl_slist_append(headers1, "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.110 Safari/537.36");    //ģ�������
            headers1 = curl_slist_append(headers1, "Host:passport.csdn.net");
            headers1 = curl_slist_append(headers1, "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
            headers1 = curl_slist_append(headers1, "Accept-Language:zh-CN,zh;q=0.8");
            headers1 = curl_slist_append(headers1, "Accept-Encoding:gzip, deflate");
            headers1 = curl_slist_append(headers1, "Content-Length: 41");
            headers1 = curl_slist_append(headers1, "Cache-Control:no-cache");
            headers1 = curl_slist_append(headers1, "Upgrade-Insecure-Requests: 1");
            headers1 = curl_slist_append(headers1, "X-Requested-With:XMLHttpRequest");
            headers1 = curl_slist_append(headers1, "Connection:keep-alive");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, command);
            curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.168.46/?$USERURL");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, call_wirte_func);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szbuffer);
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &szheader_buffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            std::string::size_type idx = szheader_buffer.find("Location:");
            szheader_buffer = szheader_buffer.substr(idx + 1);
            idx = szheader_buffer.find(":");
            szheader_buffer = szheader_buffer.substr(idx + 1);
            idx = szheader_buffer.find("\n");
            szheader_buffer = szheader_buffer.substr(0, idx);
            curl_slist_free_all(headers1);
            curl = curl_easy_init();
            headers2 = curl_slist_append(headers2, "Connection: keep-alive");
            headers2 = curl_slist_append(headers2, "Cache-Control: max-age=0");
            headers2 = curl_slist_append(headers2, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
            headers2 = curl_slist_append(headers2, "Upgrade-Insecure-Requests: 1");
            headers2 = curl_slist_append(headers2, "Accept-Encoding: gzip, deflate, sdch");
            headers2 = curl_slist_append(headers2, "Accept-Language: zh-CN,zh;q=0.8,en;q=0.6");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers2);
            curl_easy_setopt(curl, CURLOPT_URL, szheader_buffer);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, call_wirte_func);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szbuffer);
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &szheader_buffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers2);
            if (nettype == a)
            {
                idx = szbuffer.find("addInput");
                szbuffer = szbuffer.substr(idx + 8);
                idx = szbuffer.find("addInput");
                szbuffer = szbuffer.substr(idx + 8);
                idx = szbuffer.find("addInput");
                szbuffer = szbuffer.substr(idx + 8);
                idx = szbuffer.find(",");
                szbuffer = szbuffer.substr(idx + 1);
                idx = szbuffer.find(",");
                szbuffer = szbuffer.substr(idx + 1);
                idx = szbuffer.find(",");
                szbuffer = szbuffer.substr(idx + 2);
                idx = szbuffer.find("'");
                szbuffer = szbuffer.substr(0, idx);
                std::string postnumber = "POSTLanmanUserURL&Lanmannumber=" + szbuffer;
                curl = curl_easy_init();
                headers3 = curl_slist_append(headers3, "Connection: keep-alive");
                headers3 = curl_slist_append(headers3, "Pragma: no-cache");
                headers3 = curl_slist_append(headers3, "Cache-Control: no-cache");
                headers3 = curl_slist_append(headers3, "Accept: application/json, text/javascript, */*; q=0.01");
                headers3 = curl_slist_append(headers3, "X-Requested-With: XMLHttpRequest");
                headers3 = curl_slist_append(headers3, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
                headers3 = curl_slist_append(headers3, "Referer: http://192.168.168.46:9999/?LanmanUserURL=$USERURL");
                headers3 = curl_slist_append(headers3, "Accept-Encoding: gzip, deflate");
                headers3 = curl_slist_append(headers3, "Accept-Language: zh-CN,zh;q=0.8,en;q=0.6");
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers3);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postnumber);
                curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.168.46:9999/");
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, call_wirte_func);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szbuffer);
                curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
                curl_easy_setopt(curl, CURLOPT_HEADERDATA, &szheader_buffer);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                curl_slist_free_all(headers3);
                USES_CONVERSION;
                CString temp;
                const char *t = szbuffer.c_str();
                temp = t;
                MessageBox(temp, _T("��½��ʾ"));

            }
        }
    }
}


void Cnet_loginDlg::OnCbnSelchangeChooseCombo()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}
