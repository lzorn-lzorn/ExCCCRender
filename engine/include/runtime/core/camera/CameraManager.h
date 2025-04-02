#pragma once
#include "runtime/core/camera/Camera.h"
#include <vector>
#include <memory>
namespace ExCCCRender::Core{
/*
 * 相机管理器
 * 管理多个的相机
 * 相机的创建和删除
 */
class CameraManager{
public:
    static CameraManager& Instance(){
        static CameraManager instance;
        return instance;
    }

    Camera& CreatCamera(){

    }
private:
    // * @function: 为一个相机分配内存
    Camera* CameraAllocator(){
        Camera* camera_ptr = std::allocator<Camera>().allocate(1);
        std::construct_at(camera_ptr, cameras.size()+1);
        return camera_ptr;
    }

private:
    /*
    * 相机的Builder用于构建相机的内置参数
    * 用于快速初始化一个预设好的相机
    */
    struct CameraBuilder{

    } builder;
    std::vector<Camera> cameras;
};





}
