/**
 * @file    folderDlg.h
 * @brief   ��װWindows�ĶԻ�����
 * @version 1.0
 * @date    2022.10.6
 */
#ifndef __folderDlg_H__
#define __folderDlg_H__


/**
 * @brief ���ļ�ѡ��Ի��򣬻�ȡѡ����ļ���Ϣ
 * @param[in] hwndParent �����ھ��
 * @param[in] lpszTitle ��ʾ��ѡ����ϵı���
 * @return CString ����ѡ����ļ���·��
 */
CString SelectFolder(HWND hwndParent, LPCTSTR lpszTitle=_T("ѡ���ļ���"));


#endif /*__folderDlg_H__*/