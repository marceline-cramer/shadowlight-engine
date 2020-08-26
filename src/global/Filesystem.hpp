#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <physfs.h>
#include <rapidjson/document.h>

class Filesystem
{
public:
    Filesystem(const char*);
    ~Filesystem();

    void loadFile(const char*, std::vector<char>&);
    void loadJson(const char*, rapidjson::Document&);
private:
    const char* archive;
};
