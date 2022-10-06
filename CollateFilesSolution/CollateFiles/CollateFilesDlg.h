
// CollateFilesDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "FileNodeCollect.h"
#include "afxcmn.h"


enum PROCESS_STEP
{
    PS_START,
    PS_PROCESSING,
    PS_END,
};
enum PROCESS_STATUS_TYPE
{
    PST_INFO,
    PST_WARN,
    PST_ERROR,
};

struct ProcessStepParam
{
    PROCESS_STEP m_nStep;
    PROCESS_STATUS_TYPE m_nStatusType;
    CString     m_strText;
};

#define WM_NOTIFY_PROCESSSTEP   (WM_USER+1)

// CCollateFilesDlg �Ի���
class CCollateFilesDlg : public CDialogEx
{
// ����
public:
	CCollateFilesDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLATEFILES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:

    void EnableControlles(BOOL bEnable);
    void ProcessTidyFiles();
    void ReportProcessStatus(PROCESS_STEP nStep, const CString &strText, PROCESS_STATUS_TYPE nType);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnBnClickedStart();
    afx_msg void OnBnClickedSelectSourceFolder();
    afx_msg void OnBnClickedSelectDestFolder();
    afx_msg LRESULT OnProcessStepNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
   
private:
    void tidyFiles();
    void collateFiles(const CString &strRootPath, LPCTSTR lpszSuffix=_T("*.*"));
    void processFiles();
    bool processFile(const CFileNodeInfo& info);

    void appendResult(const CString &strText, COLORREF color, BOOL bBold, BOOL bItalic);

private:
    CString m_edtSrcFolder;
    CString m_edtDstFolder;
    CFileNodeCollect    m_cFileNodeCollect;
    CRichEditCtrl m_redtResult;
    CString m_strResult;
};
