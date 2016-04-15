#ifndef FILE_H
#define FILE_H

namespace fileManagement
{
    enum FileStatus{CREATED, MODIFIED, DELETED};
}

class file
{

public:
    file();
    ~file();

private:
    QDateTime dt;
    fileManagement::FileStatus stat;

};

#endif // FILE_H
