#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include <physfs.h>

class Filesystem
{
public:
    Filesystem(const char*);
    ~Filesystem();

    void loadFile(const char*, std::vector<char>&);
private:
    const char* archive;
};
