
// CollateFilesDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "FileNodeCollect.h"
#include "afxcmn.h"


// CCollateFilesDlg 对话框
class CCollateFilesDlg : public CDialogEx
{
// 构造
public:
	CCollateFilesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLATEFILES_DIALOG };
#endif

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
    afx_msg void OnBnClickedStart();
    afx_msg void OnBnClickedSelectSourceFolder();
    afx_msg void OnBnClickedSelectDestFolder();
	DECLARE_MESSAGE_MAP()
   
private:
    void enableControlles(BOOL bEnable);
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
