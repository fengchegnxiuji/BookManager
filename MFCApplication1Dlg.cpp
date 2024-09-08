
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Control(pDX, IDC_EDIT1, m_EditorNum);
	DDX_Control(pDX, IDC_EDIT2, m_A);
	DDX_Control(pDX, IDC_EDIT3, m_B);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_List.SetExtendedStyle(dwStyle);

	// TODO: 在此添加额外的初始化代码
	m_List.InsertColumn(0, TEXT("编号"), 0, 100);
	m_List.InsertColumn(1, TEXT("书名"), 0, 100);
	m_List.InsertColumn(2, TEXT("现存数量"), 0, 100);
	m_List.InsertColumn(3, TEXT("价格"), 0, 100);
	m_List.InsertColumn(4, TEXT("已借出"), 0, 100);
	InitList();
	//UpdateList();
	//init child list
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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

void CMFCApplication1Dlg::InitList() {
	m_List.DeleteAllItems();
	m_book[BOOK_A] = std::make_shared<Book>(101, 2, 35.8, "A");
	m_book[BOOK_B] = std::make_shared<Book>(102, 5, 66.2, "B");
	return;
}

void CMFCApplication1Dlg::UpdateList() {
	CString str;
	str.Format(TEXT("%s"), m_book[BOOK_A]->getName().c_str());
	m_List.SetItemText(0, 1, str);
	str.Format(TEXT("%d"), m_book[BOOK_A]->getCap());
	m_List.SetItemText(0, 2, str);
	str.Format(TEXT("%f"), m_book[BOOK_A]->getPrice());
	m_List.SetItemText(0, 3, str);
	str.Format(TEXT("%d"), m_book[BOOK_A]->getLend());
	m_List.SetItemText(0, 4, str);

	str.Format(TEXT("%s"), m_book[BOOK_B]->getName().c_str());
	m_List.SetItemText(1, 1, str);
	str.Format(TEXT("%d"), m_book[BOOK_B]->getCap());
	m_List.SetItemText(1, 2, str);
	str.Format(TEXT("%f"), m_book[BOOK_B]->getPrice());
	m_List.SetItemText(1, 3, str);
	str.Format(TEXT("%d"), m_book[BOOK_B]->getLend());
	m_List.SetItemText(1, 4, str);
	return;
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	int Num = m_book[BOOK_A]->getCap() + m_book[BOOK_B]->getCap();
	str.Format(TEXT("%d"), Num);
	CString str2 = _T("剩余图书总数 : ") + str;
	MessageBox(str2);
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	CString leftNum = m_List.GetItemText(0, 3) > m_List.GetItemText(1, 3) ?
		          m_List.GetItemText(0, 2) : m_List.GetItemText(1, 2);
	if (m_List.GetItemText(0, 3) > m_List.GetItemText(1, 3)) {
		if (_ttoi(m_List.GetItemText(0, 2)) < 3) {
			MessageBox(_T("较高价格剩余图书不得小于3本"));
			return;
		}
		if (_ttoi(m_List.GetItemText(1, 2)) < 8) {
			MessageBox(_T("较低价格剩余图书不得小于8本"));
			return;
		}
		m_book[BOOK_A]->LendBook(3);
		m_book[BOOK_B]->LendBook(8);
		UpdateList();
	}
	else {
		if (_ttoi(m_List.GetItemText(1, 2)) < 3) {
			MessageBox(_T("较高价格剩余图书不得小于3本"));
			return;
		}
		if (_ttoi(m_List.GetItemText(0, 2)) < 8) {
			MessageBox(_T("较低价格剩余图书不得小于8本"));
			return;
		}
		m_book[BOOK_B]->LendBook(3);
		m_book[BOOK_A]->LendBook(8);
		UpdateList();
	}
	
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码 add book num
	if (m_List.GetNextItem(-1, LVNI_SELECTED) == -1) {
		MessageBox(_T("请选择图书"));
		return;
	}
	int index = m_List.GetSelectionMark();
	CString str;
	int num = m_book[index]->getCap();
	num++;
	if (num > 10) {
		CString str2 = _T("图书总数不能大于10");
		MessageBox(str2);
		return;
	}
	m_book[index]->AddBook(1);
	UpdateList();
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{	
	// TODO: 在此添加控件通知处理程序代码 give back
	if (m_List.GetNextItem(-1, LVNI_SELECTED) == -1) {
		MessageBox(_T("请选择图书"));
		return;
	}
	int index = m_List.GetSelectionMark();
	CString num;
	m_EditorNum.GetWindowText(num);
	int IntNum = _ttoi(num);
	int leftnum = m_book[index]->getCap();
	if (IntNum > m_book[index]->getLend()) {
		MessageBox(_T("图书未借去该数量"));
		return;
	}
	if (IntNum + leftnum > 10) {
		MessageBox(_T("图书总数不得超过10本"));
		return;
	}
	m_book[index]->GiveBack(IntNum);
	UpdateList();
}


void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	str.Format(TEXT("%d"), m_book[BOOK_A]->getNo());
	m_List.InsertItem(0, str);
	str.Format(TEXT("%d"), m_book[BOOK_B]->getNo());
	m_List.InsertItem(1, str);
	UpdateList();
}


void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString numA;
	CString numB;
	m_A.GetWindowText(numA);
	m_B.GetWindowText(numB);
	if (numA.IsEmpty() || numB.IsEmpty()) {
		MessageBox(_T("请输入A或者B书的添加数量"));
		return;
	}
	int IntNumA = _ttoi(numA);
	int IntNumB = _ttoi(numB);
	if (IntNumA + m_book[BOOK_A]->getCap() > 10 ||
		IntNumB + m_book[BOOK_B]->getCap() > 10) {
		MessageBox(_T("A或者B添加的书籍超过了10本"));
		return;
	}
	m_book[BOOK_A]->AddBook(IntNumA);
	m_book[BOOK_B]->AddBook(IntNumB);
	UpdateList();
}
