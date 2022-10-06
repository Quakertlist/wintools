
// CollateFilesDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCollateFilesDlg �Ի���



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


// CCollateFilesDlg ��Ϣ�������

BOOL CCollateFilesDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCollateFilesDlg::OnPaint()
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
HCURSOR CCollateFilesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
 * ��ʼ����
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
 * ѡ��Դ�ļ�·��
 */
void CCollateFilesDlg::OnBnClickedSelectSourceFolder()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_edtSrcFolder = SelectFolder(GetSafeHwnd());
    UpdateData(FALSE);
}

/**
 * ѡ��Ŀ���ļ�·��
 */
void CCollateFilesDlg::OnBnClickedSelectDestFolder()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
            appendResult(_T("�ҵ���") + cFileNodeInfo.GetFullPath() + _T("Ŀ¼"), RGB(123, 32, 124), TRUE, TRUE);
        }
        else
        {
            cFileNodeInfo.SetFileNodeMode(CFileNodeInfo::FNM_FILE);
            cFileNodeInfo.SetPathInfo(strRootPath, strFileName);
            m_cFileNodeCollect.AddFileNode(cFileNodeInfo);
            appendResult(_T("�ҵ���") + cFileNodeInfo.GetFullPath() + _T("�ļ�"), RGB(218, 123, 42), FALSE, TRUE);
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
    appendResult(_T("�ƶ��ļ�")+ strSrcFile +_T("��")+ strDstFile, RGB(34, 32, 12), TRUE, TRUE);
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
