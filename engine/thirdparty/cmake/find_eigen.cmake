cmake_minimum_required(VERSION 3.14)

include(FetchContent)

# 配置Eigen的FetchContent参数
FetchContent_Declare(
    Eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0 # 指定版本号或分支
)

# 执行获取和配置
FetchContent_MakeAvailable(Eigen)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建可执行目标
add_executable(${PROJECT_NAME} main.cpp)

# 链接Eigen库
target_link_libraries(${PROJECT_NAME}
    PRIVATE Eigen3::Eigen
)