#include "AssetManager.h"

void FileSystem::OpenFile(std::string path)
{
    std::fstream fs;
    fs.open ("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    fs << " more lorem ipsum";

    fs.close();

}