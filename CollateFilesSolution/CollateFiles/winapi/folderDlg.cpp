#include "stdafx.h"
#include "folderDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString SelectFolder(HWND hwndParent, LPCTSTR lpszTitle)
{
    CString filePath = _T(""); //�õ��ļ�·��
    LPMALLOC pMalloc;
    if (::SHGetMalloc(&pMalloc) == NOERROR) //ȡ��IMalloc�������ӿ�
    {
        BROWSEINFO bi;
        TCHAR pszBuffer[MAX_PATH] = { 0 };
        LPITEMIDLIST pidl;
        bi.hwndOwner = hwndParent;
        bi.pidlRoot = NULL;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = lpszTitle; //ѡ��Ŀ¼�Ի�����ϲ��ֵı���
                                    //����½��ļ��а�ť BIF_NEWDIALOGSTYLE
        bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
        bi.lpfn = NULL;
        bi.lParam = 0;
        bi.iImage = 0;
        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)  //ȡ��IMalloc�������ӿ�
        {
            if (::SHGetPathFromIDList(pidl, pszBuffer)) //���һ���ļ�ϵͳ·��
            {
                filePath = pszBuffer;
            }
            pMalloc->Free(pidl); //�ͷ��ڴ�
        }
        pMalloc->Release(); //�ͷŽӿ�
    }
    return filePath;
}
