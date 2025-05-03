#pragma once
#include "../AssetLoader/AssetLoader.h"


namespace ExCCCRender::Asset {
class AssimpLoader : public AssetLoader{
public:
    bool LoadOneFile(const std::string_view) override;
    bool LoadAllFold(const std::string_view) override;

private:

};
}