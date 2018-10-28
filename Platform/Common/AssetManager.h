#pragma once
#include "Asset.h"

enum EAssetType {
    TextAsset
    AudioAsset
    UnsupportedAsset
};


class AssetManager {
public:
    Asset Open(std::string InFilePath);
    Asset Open(std::string InFilePath, EAssetType InType);

    EFileExtension GetExtension(std::string FilePath);
};