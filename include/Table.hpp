#ifndef ASS_02_TABLE_HPP
#define ASS_02_TABLE_HPP

#pragma once

#include <atlas/utils/Geometry.hpp>
#include <atlas/primitives/Sphere.hpp>
#include <atlas/core/Float.hpp>
#include <atlas/core/Log.hpp>

class Table : public atlas::utils::Geometry
{
public:
    Table(float r);
    ~Table();
    void updateGeometry(atlas::utils::Time const& t);
    void renderGeometry(atlas::math::Matrix4 projection, atlas::math::Matrix4 view) override;
    void transformGeometry(atlas::math::Matrix4 const& t) override;
    const glm::vec3 getPos();
    const float getRad();

private:
    GLuint mVao;
    float radius;
    atlas::primitives::Sphere mSphere;
    glm::vec3 currPos;
};

#endif
