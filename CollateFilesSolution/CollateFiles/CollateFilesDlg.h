
// CollateFilesDlg.h : ͷ�ļ�
//

#pragma once


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
	DECLARE_MESSAGE_MAP()
public:
};
