#pragma once

#include "core/math/Point.h"
#include "core/illumination/Ray.h"

namespace ExCCCRender::Core {
using namespace ExCCCRender::Core::Illumination;

class Camera {
public:
    explicit Camera(int32_t id) : id(id) {
    }

    ~Camera() = default;

    Camera(const Camera&)            = default;
    Camera& operator=(const Camera&) = default;

    Camera(Camera&&)            = default;
    Camera& operator=(Camera&&) = default;

public:
    Ray GenerateRay() {

        return Ray();
    }

public:
    Camera& SetAperture(const double aperture) {
        this->aperture = aperture;
        return *this;
    }

    Camera& SetShutter(const double open, const double close) {
        this->shutter_open  = open;
        this->shutter_close = close;
        return *this;
    }

    Camera& SetFocalDistance(const double focal_distance) {
        this->focal_distance = focal_distance;
        return *this;
    }

    Camera& SetLens(const double lens_radius) {
        this->lens_radius = lens_radius;
        return *this;
    }

    unsigned char* GetFilm() const {
        return film;
    }

    // * 对图像做处理, 使其格式支持存入磁盘
    void ImageMateData() const {
    }

private:
    // * 基于物理的相机最后得到的胶片图片
    unsigned char* film = nullptr;

private:
    int32_t id{-1};

    // * 相机视锥的起点
    Point3D origin;  // 等价于 lookfrom
    // * 相机视锥的终点
    Point3D lookat;
    // * 相机的左下角坐标
    Point3D lower_left_corner;
    // * 相机的水平向量 和 垂直向量
    Vector3D horizontal, vertical;
    // * 视口平面的三个坐标系
    Vector3D u, v, w;
    // * 相机的上方向
    Vector3D up;
    // * 镜头半径
    double lens_radius;
    // * 快门开启的时间 和 结束的时间
    double shutter_open, shutter_close;
    // * 光圈大小
    double aperture;
    // * 相机焦距
    double focal_distance;
};

}  // namespace ExCCCRender::Core
