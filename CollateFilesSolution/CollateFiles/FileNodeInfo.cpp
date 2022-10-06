#include "stdafx.h"
#include "FileNodeInfo.h"


CFileNodeInfo::CFileNodeInfo()
{
}


CFileNodeInfo::~CFileNodeInfo()
{
}

void CFileNodeInfo::SetFileNodeMode(FILE_NODE_MODE nFileNodeMode)
{
    m_nFileNodeMode = nFileNodeMode;
}

CFileNodeInfo::FILE_NODE_MODE CFileNodeInfo::GetFileNodeMode() const
{
    return m_nFileNodeMode;
}

void CFileNodeInfo::SetPathInfo(const CString &strRootPath, const CString &strFileName)
{
    m_strRootPath = strRootPath;
    m_strFileName = strFileName;
    m_strFullPath = strRootPath + _T("\\") + strFileName;
    CFile::GetStatus(m_strFullPath, m_cFileStatus);
}

CString CFileNodeInfo::GetFullPath() const
{
    return m_strFullPath;
}

CString CFileNodeInfo::GetFileName() const
{
    return m_strFileName;
}

CTime CFileNodeInfo::GetFileTime(FILE_STATUS nFileStatus) const
{
    switch (nFileStatus)
    {
    case CFileNodeInfo::FS_CREATE_TIME:
        return m_cFileStatus.m_ctime;
    case CFileNodeInfo::FS_MODIFY_TIME:
        return m_cFileStatus.m_mtime;
    default:
        return m_cFileStatus.m_atime;
    }
}

ULONGLONG CFileNodeInfo::GetFileSize() const
{
    return m_cFileStatus.m_size;
}

DWORD CFileNodeInfo::GetFileAttribute() const
{
    return m_cFileStatus.m_attribute;
}
