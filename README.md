# ExCCCRender

## How to build

If you want to build ExCCCRender, you need to install the following third-party libries:
- Vulkan (Recommand)
- fmt::fmt



ExCCCRender uses cmake to build and used lots of C++20 feature. So please check your cmake version and C++ standard (Maybe C++23, I'll try)
- CMake version 3.20 at least
- C++ compiler should support C++20 (clang+llvm-19.1.0-x86_64-pc-window-msvc)

## About Doc
In the doc/, I will introduce what is RayTracing and How can we implement a RayTracer (the Structure of ExCCCRender ^_^)

## Plan
### RayTracer
**Math**
Matrix Interface
Backends: GLM
**Render**
Phyics-based Camera
aabb -> BVH
object Interface:
    backends: Meshes


### Asset
**Forward**
AssetManager
Import
Export
AssetBuffer
Interface Level
**Backends**
Assimp
OpenFBX

### Graphic API
**Forward**
Engine Pipeline

**Backends**
OpenGL
Vulkan
DX12

### Basement
Memory Pool
Thread Pool -> Task System (Corotinue)
ECS System
## GUI
SDL3+imgui