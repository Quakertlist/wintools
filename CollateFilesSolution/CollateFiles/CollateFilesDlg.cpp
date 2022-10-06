
// CollateFilesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CollateFiles.h"
#include "CollateFilesDlg.h"
#include "afxdialogex.h"

#include "winapi\folderDlg.h"
#include "winapi\mkdir.h"

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


// CCollateFilesDlg 对话框



CCollateFilesDlg::CCollateFilesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COLLATEFILES_DIALOG, pParent)
    , m_edtSrcFolder(_T(""))
    , m_edtDstFolder(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCollateFilesDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, EDT_SOURCE_FOLDER, m_edtSrcFolder);
    DDX_Text(pDX, EDT_DEST_FOLER, m_edtDstFolder);
    DDX_Control(pDX, REDT_RESULT, m_redtResult);
}

BEGIN_MESSAGE_MAP(CCollateFilesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(BTN_START, &CCollateFilesDlg::OnBnClickedStart)
    ON_BN_CLICKED(BTN_SELECT_SOURCE_FOLDER, &CCollateFilesDlg::OnBnClickedSelectSourceFolder)
    ON_BN_CLICKED(BTN_SELECT_DEST_FOLDER, &CCollateFilesDlg::OnBnClickedSelectDestFolder)
END_MESSAGE_MAP()


// CCollateFilesDlg 消息处理程序

BOOL CCollateFilesDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCollateFilesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCollateFilesDlg::OnPaint()
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
HCURSOR CCollateFilesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
 * 开始处理
 */
void CCollateFilesDlg::OnBnClickedStart()
{
    this->UpdateData(TRUE);

#ifdef _DEBUG
    m_edtSrcFolder = _T("E:\\projects\\github.com\\Quakertlist\\wintools");
    m_edtDstFolder = _T("E:\\projects\\github.com\\Quakertlist\\wintools\\sample");
#endif // _DEBUG

    if (m_edtDstFolder.IsEmpty())
    {
        AfxMessageBox(IDS_ERROR_TIP1, MB_OK|MB_ICONERROR);
        return;
    }
    if (m_edtSrcFolder.IsEmpty())
    {
        AfxMessageBox(IDS_ERROR_TIP2, MB_OK | MB_ICONERROR);
        return;
    }
    if (m_edtSrcFolder == m_edtDstFolder)
    {
        AfxMessageBox(IDS_ERROR_TIP3, MB_OK | MB_ICONERROR);
        return;
    }
    enableControlles(FALSE);
    tidyFiles();
    enableControlles(TRUE);
}


/**
 * 选择源文件路径
 */
void CCollateFilesDlg::OnBnClickedSelectSourceFolder()
{
    // TODO: 在此添加控件通知处理程序代码
    m_edtSrcFolder = SelectFolder(GetSafeHwnd());
    UpdateData(FALSE);
}

/**
 * 选择目标文件路径
 */
void CCollateFilesDlg::OnBnClickedSelectDestFolder()
{
    // TODO: 在此添加控件通知处理程序代码
    m_edtDstFolder = SelectFolder(GetSafeHwnd());
    UpdateData(FALSE);
}

void CCollateFilesDlg::enableControlles(BOOL bEnable)
{
    UINT ids[] = { BTN_SELECT_DEST_FOLDER, BTN_SELECT_SOURCE_FOLDER, BTN_START };
    for each (UINT id in ids)
    {
        GetDlgItem(id)->EnableWindow(bEnable);
    }
}

void CCollateFilesDlg::tidyFiles()
{
    collateFiles(m_edtSrcFolder);
    processFiles();
}

void CCollateFilesDlg::collateFiles(const CString &strRootPath, LPCTSTR lpszSuffix/*=_T("*.*")*/)
{
    CFileFind ffd;
    BOOL bWorking = ffd.FindFile(strRootPath + _T("\\") + lpszSuffix);
    while (bWorking)
    {
        bWorking = ffd.FindNextFileW();
        CString strFileName = ffd.GetFileName();
        if (_T(".") == strFileName || _T("..") == strFileName)
        {
            continue;
        }
        CFileNodeInfo cFileNodeInfo;
        if (ffd.IsDirectory())
        {
            cFileNodeInfo.SetFileNodeMode(CFileNodeInfo::FNM_DIR);
            cFileNodeInfo.SetPathInfo(strRootPath, strFileName);
            appendResult(_T("找到了") + cFileNodeInfo.GetFullPath() + _T("目录"), RGB(123, 32, 124), TRUE, TRUE);
        }
        else
        {
            cFileNodeInfo.SetFileNodeMode(CFileNodeInfo::FNM_FILE);
            cFileNodeInfo.SetPathInfo(strRootPath, strFileName);
            m_cFileNodeCollect.AddFileNode(cFileNodeInfo);
            appendResult(_T("找到了") + cFileNodeInfo.GetFullPath() + _T("文件"), RGB(218, 123, 42), FALSE, TRUE);
        }

        if (cFileNodeInfo.GetFileNodeMode()==CFileNodeInfo::FNM_DIR) 
        {
            collateFiles(cFileNodeInfo.GetFullPath(), lpszSuffix);
        }
    }

}

void CCollateFilesDlg::processFiles()
{
    m_cFileNodeCollect.ForEach(std::bind(&CCollateFilesDlg::processFile, this, std::placeholders::_1));
}

bool CCollateFilesDlg::processFile(const CFileNodeInfo& info)
{
    CString strSrcFile = info.GetFullPath();
    CString strDstFile;
    CTime cCreateTime = info.GetFileTime(CFileNodeInfo::FS_CREATE_TIME);
    strDstFile.Format(_T("%s\\%04d-%02d-%02d\\"), m_edtDstFolder, cCreateTime.GetYear(), cCreateTime.GetMonth(), cCreateTime.GetDay());
    if (_taccess(strDstFile, 0)!=0)
    {
        MKDir(strDstFile);
    }
    strDstFile +=  info.GetFileName();
    CopyFile(strSrcFile, strDstFile, FALSE);
    appendResult(_T("移动文件")+ strSrcFile +_T("到")+ strDstFile, RGB(34, 32, 12), TRUE, TRUE);
    return true;
}

void CCollateFilesDlg::appendResult(const CString &strText, COLORREF color, BOOL bBold, BOOL bItalic)
{
    int nOldTextLen = m_strResult.GetLength();
    CTime tmNow = CTime::GetCurrentTime();
    CString strAppendText;
    strAppendText.Format(_T("%04d-%02d-%02d %02d:%02d:%02d %s"),
        tmNow.GetYear(), tmNow.GetMonth(), tmNow.GetDay(),
        tmNow.GetHour(), tmNow.GetMinute(), tmNow.GetSecond(),
        strText);


    CHARFORMAT cf = { 0 };
    cf.cbSize = sizeof(cf);
    cf.dwMask = (bBold ? CFM_BOLD : 0) | (bItalic ? CFM_ITALIC : 0) | CFM_COLOR;
    cf.dwEffects = (bBold ? CFE_BOLD : 0) | (bItalic ? CFE_ITALIC : 0) | ~CFE_AUTOCOLOR;
    cf.crTextColor = color;

    m_strResult.Append(strAppendText);
    int nNewTextLen = m_strResult.GetLength();
    m_strResult.Append(_T("\n"));
    m_redtResult.SetWindowText(m_strResult);
    m_redtResult.SetSel(nOldTextLen, nNewTextLen);
    m_redtResult.SetSelectionCharFormat(cf);
}
