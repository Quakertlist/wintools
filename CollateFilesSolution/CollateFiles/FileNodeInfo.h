/**
 * @file    FileNodeInfo.h
 * @brief   保存扫描到的文件信息的结构体
 * @version 1.0
 * @date    2022.10.6
 */
#ifndef __FileNodeInfo_H__
#define __FileNodeInfo_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileNodeInfo
{
public:
    enum FILE_NODE_MODE
    {
        FNM_DIR = 1,
        FNM_FILE,
    };

    enum FILE_STATUS
    {
        FS_CREATE_TIME = 1,
        FS_MODIFY_TIME,
        FS_LASTACCESS_TIME,
    };
public:
    CFileNodeInfo();
    ~CFileNodeInfo();

    void SetFileNodeMode(FILE_NODE_MODE nFileNodeMode);
    FILE_NODE_MODE GetFileNodeMode() const;
    void SetPathInfo(const CString &strRootPath, const CString &strFileName);
    CString GetFullPath() const;
    CString GetFileName() const;
    CTime GetFileTime(FILE_STATUS nFileStatus) const;
    ULONGLONG GetFileSize() const;
    DWORD GetFileAttribute() const;

private:
    FILE_NODE_MODE  m_nFileNodeMode;
    CString m_strRootPath;
    CString m_strFileName;
    CString m_strFullPath;
    CFileStatus m_cFileStatus;
};

#endif /*__FileNodeInfo_H__*/