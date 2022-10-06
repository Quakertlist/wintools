#include "stdafx.h"
#include "folderDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString SelectFolder(HWND hwndParent, LPCTSTR lpszTitle)
{
    CString filePath = _T(""); //得到文件路径
    LPMALLOC pMalloc;
    if (::SHGetMalloc(&pMalloc) == NOERROR) //取得IMalloc分配器接口
    {
        BROWSEINFO bi;
        TCHAR pszBuffer[MAX_PATH] = { 0 };
        LPITEMIDLIST pidl;
        bi.hwndOwner = hwndParent;
        bi.pidlRoot = NULL;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = lpszTitle; //选择目录对话框的上部分的标题
                                    //添加新建文件夹按钮 BIF_NEWDIALOGSTYLE
        bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
        bi.lpfn = NULL;
        bi.lParam = 0;
        bi.iImage = 0;
        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)  //取得IMalloc分配器接口
        {
            if (::SHGetPathFromIDList(pidl, pszBuffer)) //获得一个文件系统路径
            {
                filePath = pszBuffer;
            }
            pMalloc->Free(pidl); //释放内存
        }
        pMalloc->Release(); //释放接口
    }
    return filePath;
}
