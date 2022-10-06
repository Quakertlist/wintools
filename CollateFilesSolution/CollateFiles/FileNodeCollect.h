/**
 * @file    FileNodeCollect.h
 * @brief   ɨ�赽���ļ��ڵ㼯��
 * @version 1.0
 * @date    2022.10.6
 */
#ifndef __FileNodeCollect_H__
#define __FileNodeCollect_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "FileNodeInfo.h"

class CFileNodeCollect
{
public:
    CFileNodeCollect();
    ~CFileNodeCollect();

    void Clear();
    size_t AddFileNode(const CFileNodeInfo &info);
    void ForEach(std::function<bool(const CFileNodeInfo &info)> fn);

private:
    std::list<CFileNodeInfo> m_lstFileNodes;
};

#endif /*__FileNodeCollect_H__*/