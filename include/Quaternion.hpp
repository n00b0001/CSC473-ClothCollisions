#ifndef ASS02_INCLUDE_QUATERNION_HPP
#define ASS02_INCLUDE_QUATERNION_HPP

#pragma once

#include <atlas/core/Macros.hpp>
#include <atlas/core/GLFW.hpp>
#include "atlas/math/Vector.hpp"

class Quaternion
{
public:
    Quaternion();
    Quaternion(float w, glm::vec3 v);
    ~Quaternion();

    float length();
    Quaternion normalize();
    Quaternion conjugate();
    Quaternion operator* (Quaternion const& q);
    glm::vec3 getV();
    float getW();

    float W;
    glm::vec3 V;
};

#endif
