# ExCCCRender

## How to build

If you want to build ExCCCRender, you need to install the following third-party libries:
- Vulkan (Recommand)



ExCCCRender uses cmake to build and used lots of C++20 feature. So please check your cmake version and C++ standard (Maybe C++23, I'll try)
- CMake version 3.20 at least
- C++ compiler should support C++20

## About Doc
In the doc/, I will introduce what is RayTracing and How can we implement a RayTracer (the Structure of ExCCCRender ^_^)

## Plan

-[] 封装std::random
-[] 蒙特卡洛积分器
-[] 重要性采样

-[] 光线, 点
-[] 碰撞体, 包围盒
-[] 矩阵类, 矩阵变换
    -[] 平移
    -[] 旋转
    -[] 缩放
    -[] 仿射变换
-[] 加速求交结构