#include "global/Filesystem.hpp"

Filesystem::Filesystem(const char* _archive)
{
    archive = _archive;
    
    // TODO Add different mount targets for mods/DLC/etc and connect it to this class
    if(!PHYSFS_mount(archive, NULL, 0)) {
        throw std::runtime_error("Failed to mount " + std::string(archive));
    }
}

Filesystem::~Filesystem()
{
    PHYSFS_unmount(archive);
}

void Filesystem::loadFile(const char* fileName, std::vector<char>& buffer)
{
    if(!PHYSFS_exists(fileName)) {
        throw std::runtime_error("File '" + std::string(fileName) + "' does not exist");
    }

    auto f = PHYSFS_openRead(fileName);

    if(!f) {
        throw std::runtime_error("Failed to open " + std::string(fileName));
    }

    // TODO More error checking
    buffer.resize(PHYSFS_fileLength(f));
    PHYSFS_readBytes(f, buffer.data(), buffer.size());
    PHYSFS_close(f);
}

void Filesystem::loadFile(const char* fileName, std::string& contents)
{
    std::vector<char> buffer;
    loadFile(fileName, buffer);
    contents = std::string(buffer.data(), buffer.size());
}

void Filesystem::loadJson(const char* fileName, rapidjson::Document& doc)
{
    std::string json;
    loadFile(fileName, json);

    if(doc.Parse(json.c_str()).HasParseError()) {
        throw std::runtime_error("JSON file " + std::string(fileName) + " failed to parse");
    }
}
