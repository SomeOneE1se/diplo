#ifndef FILES_H
#define FILES_H

unsigned int file_getFileContent(
    const char  *filePath,
    const char  *modes,
    unsigned int ressize,
    char        *res
);

#endif  // FILES_H
