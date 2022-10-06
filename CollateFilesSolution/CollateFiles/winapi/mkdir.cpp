#include "stdafx.h"
#include "mkdir.h"

#ifdef WIN32
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _tmkdir(path)
#else
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif


int MKDir(const CString &strPath)
{
    int dirPathLen = strPath.GetLength();
    if (dirPathLen > MAX_PATH)
    {
        return -1;
    }
    TCHAR tmpDirPath[MAX_PATH] = { 0 };
    for (int i = 0; i < dirPathLen; ++i)
    {
        tmpDirPath[i] = strPath.GetAt(i);
        if (tmpDirPath[i] == _T('\\') || tmpDirPath[i] == _T('/'))
        {
            if (_taccess(tmpDirPath, 0) != 0)
            {
                int ret = MKDIR(tmpDirPath);
                if (ret != 0)
                {
                    return ret;
                }
            }
        }
    }
    return 0;
}

