/**
 * @file    folderDlg.h
 * @brief   封装Windows的对话框函数
 * @version 1.0
 * @date    2022.10.6
 */
#ifndef __folderDlg_H__
#define __folderDlg_H__


/**
 * @brief 打开文件选择对话框，获取选择的文件信息
 * @param[in] hwndParent 父窗口句柄
 * @param[in] lpszTitle 显示在选择框上的标题
 * @return CString 返回选择的文件夹路径
 */
CString SelectFolder(HWND hwndParent, LPCTSTR lpszTitle=_T("选择文件夹"));


#endif /*__folderDlg_H__*/