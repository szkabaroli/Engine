#include "AssetManager.h"

Asset* AssetManager::Open(std::string InFilePath, EAssetType InType)
{




    return new Asset();
}

Asset* AssetManager::Open(std::string InFilePath)
{
    std::string ext = path.substr(path.find_last_of(".") + 1);

    EAssetType Type

    switch(ext)
    {
        case "txt":
            Type = TextAsset;
            break
        case "mp4":
            Type = AudioAsset;
        default:
            Type = UnsupportedAsset;
            return nullptr;
    }

    return Open(InFilePath, Type);
}