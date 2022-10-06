
// CollateFilesDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "FileNodeCollect.h"


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
	DECLARE_MESSAGE_MAP()
   
private:
    void enableControlles(BOOL bEnable);
    void tidyFiles();
    void collateFiles(const CString &strRootPath, LPCTSTR lpszSuffix=_T("*.*"));
    void processFiles();
    bool processFile(const CFileNodeInfo& info);

private:
    CString m_edtSrcFolder;
    CString m_edtDstFolder;
    CFileNodeCollect    m_cFileNodeCollect;
};
