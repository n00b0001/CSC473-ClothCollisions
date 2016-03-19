#ifndef ASS02_INCLUDE_MAYA_CAMERA_HPP
#define ASS02_INCLUDE_MAYA_CAMERA_HPP

#pragma once

#include <atlas/utils/Camera.hpp>
#include <memory>
#include <atlas/core/Float.hpp>
#include <atlas/core/Log.hpp>
#include <atlas/utils/Time.hpp>

class ClothCamera : public atlas::utils::Camera
{
public:
    ClothCamera();
    ~ClothCamera();

    void resetCamera() override;
    atlas::math::Matrix4 getCameraMatrix() override;
    void doQuatRotate(atlas::utils::Time const& t);

private:

    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 cameraDirection;
    glm::vec3 up;

};

#endif


