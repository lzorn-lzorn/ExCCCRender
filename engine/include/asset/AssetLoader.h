#pragma once
#include "asset/MeshInfo.h"
#include <vector>
namespace ExCCCRender::Asset{

class AssetLoader{

public:
    /*
     * @function: 加载一个资源, 输入资源的绝对路径
     * @return: 加载成功则返回true, 加载失败则返回false;
     * @note: 加载一个空资源也返回true 
     */
    bool LoadOneFile(const std::string_view);
    bool LoadOneFile(const char *);
    /*
     * @function: 并行 Load 该文件路径下所有的资源文件
     * 
     */
    bool LoadAllFold(const std::string_view);

private:
    MeshInfo& load_one_file_(const std::string_view);

private:
    static std::vector<MeshInfo> mesh_pool;
};
}