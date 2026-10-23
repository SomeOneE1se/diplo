#include "files.h"
#include "logs.h"
#include <stdio.h>

/**
 * @brief file_getFileContent
 * @param filePath
 * @param modes
 * @param ressize
 * @param res
 * @return
 */
unsigned int file_getFileContent(
    const char  *filePath,
    const char  *modes,
    unsigned int ressize,
    char        *res
)
{
    if (!res || ressize == 0)
    {
        return 0;
    }

    FILE *fp = fopen(filePath, modes);
    if (fp == NULL)
    {
        LOG_INFO("! Can not open file: %s", filePath);
        return 0;
    }

    if (fseek(fp, 0, SEEK_END) != 0)
    {
        LOG_INFO("! Can not find end of file: %s", filePath);
        fclose(fp);
        return 0;
    }

    long size = ftell(fp);
    if (size < 0)
    {
        LOG_INFO("! Can not read file correctly: %s", filePath);
        fclose(fp);
        return 0;
    }
    rewind(fp);

    if (ressize < size)
    {
        size = ressize;
    }

    unsigned int read = fread(res, 1, size, fp);
    if (read <= 0)
    {
        fclose(fp);
        return 0;
    }

    res[read] = '\0';

    fclose(fp);
    return read;
}
