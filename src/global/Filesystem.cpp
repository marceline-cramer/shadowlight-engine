#include "Filesystem.hpp"

Filesystem::Filesystem(const char* _archive)
{
    archive = _archive;
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

    buffer.resize(PHYSFS_fileLength(f));
    PHYSFS_readBytes(f, buffer.data(), buffer.size());
    PHYSFS_close(f);
}
