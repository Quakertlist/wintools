#include "stdafx.h"
#include "FileNodeCollect.h"


CFileNodeCollect::CFileNodeCollect()
{
}


CFileNodeCollect::~CFileNodeCollect()
{
}

void CFileNodeCollect::Clear()
{
    m_lstFileNodes.clear();
}

size_t CFileNodeCollect::AddFileNode(const CFileNodeInfo &info)
{
    m_lstFileNodes.push_back(info);
    return m_lstFileNodes.size();
}

void CFileNodeCollect::ForEach(std::function<bool(const CFileNodeInfo &info)> fn)
{
    for each (const CFileNodeInfo& info in m_lstFileNodes)
    {
        if (!fn(info))
        {
            break;
        }
    }
}
