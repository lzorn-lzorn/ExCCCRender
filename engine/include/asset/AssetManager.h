#pragma once
#include "asset/SceneInfo.h"
namespace ExCCCRender::Asset {

class AssetManager {
public:
    static AssetManager& Instance() {
        static AssetManager instance;
        return instance;
    }

    static void Destory() {
    }

public:
    std::vector<Scene> scenes;
private:
    AssetManager()                               = default;
    AssetManager(const AssetManager&)            = delete;
    AssetManager(AssetManager&&)                 = delete;
    ~AssetManager()                              = default;
    AssetManager& operator=(AssetManager&&)      = delete;
    AssetManager& operator=(const AssetManager&) = delete;
};
}  // namespace ExCCCRender::Asset