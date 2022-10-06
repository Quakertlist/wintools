/**
 * @file    mkdir.h
 * @brief   创建多级文件夹目录
 * @version 1.0
 * @date    2022.10.6
 */
#ifndef __mkdir_H__
#define __mkdir_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

int MKDir(const CString &strPath);

#endif /*__mkdir_H__*/