
// net_loginDlg.cpp : 实现文件
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

CString a("电信网");
CString b("教育网");
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
size_t header_callback(const char  *ptr, size_t size, size_t nmemb, std::string *stream)    //头部回掉函数
{
    assert(stream != NULL);
    size_t len = size * nmemb;
    stream->append(ptr, len);
    return len;
}
size_t call_wirte_func(const char *ptr, size_t size, size_t nmemb, std::string *stream)    //返回体回调函数
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

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Cnet_loginDlg 对话框



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


// Cnet_loginDlg 消息处理程序

BOOL Cnet_loginDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码
    control_combobox.AddString(a);
    control_combobox.AddString(b);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cnet_loginDlg::OnPaint()
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
HCURSOR Cnet_loginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cnet_loginDlg::OnBnClickedOk()
{
    // TODO:  在此添加控件通知处理程序代码
    CString nettype;
    UpdateData(TRUE);
    control_combobox.GetWindowText(nettype);
    std::string szbuffer;
    std::string szheader_buffer;
    if (nettype != a&&nettype != b)                                          //登陆信息初步验证
        MessageBox(_T("请您选择网络类型"), _T("错误"));
    else if (Cusername.IsEmpty() || Cpassword.IsEmpty())
        MessageBox(_T("请您输入完整的登陆信息"), _T("错误"));
    else
    {
        CString ccommand;
        char *command;
        ccommand = _T("username=") + Cusername + _T("&password=") + Cpassword + _T("&B1=");             //构造POST参数
        USES_CONVERSION;
       
        command = W2A(ccommand);
        CURL *curl;
        CURLcode res;
        struct curl_slist *headers1 = NULL , *headers2 = NULL, *headers3 = NULL;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl){

            //http请求头
            headers1 = curl_slist_append(headers1, "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.110 Safari/537.36");    //模拟浏览器
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
            res = curl_easy_perform(curl);                           //运行
            curl_easy_cleanup(curl);
            std::string::size_type idx = szheader_buffer.find("Location:");         //切割头部找到要用的信息
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
            res = curl_easy_perform(curl);       //http请求
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers2);
            if (nettype == a)                 //选择电信网
            {
                idx = szbuffer.find("addInput");                    //切割获取
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
                res = curl_easy_perform(curl);                //POST按钮
                curl_easy_cleanup(curl);
                curl_slist_free_all(headers3);
                USES_CONVERSION;
                CString temp;
                const char *t = szbuffer.c_str();
                temp = t;
                MessageBox(temp, _T("登陆提示"));

            }
            else if (nettype == b)               //教育网
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
                MessageBox(temp, _T("登陆提示"));

            }
        }
    }
}

void Cnet_loginDlg::OnBnClickedCloseButton()              //关闭按钮
{
    CString nettype;
    UpdateData(TRUE);
    control_combobox.GetWindowText(nettype);
    std::string szbuffer;
    std::string szheader_buffer;
    if (nettype != a&&nettype != b)
        MessageBox(_T("请您选择网络类型"), _T("错误"));
    else if (Cusername.IsEmpty() || Cpassword.IsEmpty())
        MessageBox(_T("请您输入完整的登陆信息"), _T("错误"));
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

            //http请求头
            headers1 = curl_slist_append(headers1, "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.110 Safari/537.36");    //模拟浏览器
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
                MessageBox(temp, _T("登陆提示"));

            }
        }
    }
}


void Cnet_loginDlg::OnCbnSelchangeChooseCombo()
{
    // TODO:  在此添加控件通知处理程序代码
}
