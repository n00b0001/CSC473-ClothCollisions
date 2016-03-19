#ifndef ASS_02_POINT_MASS_HPP
#define ASS_02_POINT_MASS_HPP

#pragma once

#include <atlas/utils/Geometry.hpp>
#include <atlas/primitives/Sphere.hpp>
#include <atlas/core/Float.hpp>
#include <atlas/core/Log.hpp>

class PointMass : public atlas::utils::Geometry
{
public:
    PointMass(glm::vec3 pos);
    ~PointMass();
    void updateGeometry(atlas::utils::Time const& t);
    void renderGeometry(atlas::math::Matrix4 projection,
                        atlas::math::Matrix4 view) override;
    void transformGeometry(atlas::math::Matrix4 const& t) override;
    const glm::vec3 getPos();
    void setPos(glm::vec3 p);
    void setForce(glm::vec3 f);
    void addForce(glm::vec3 f);
    void setAnchored(bool a);
    bool isAnchored();
    const glm::vec3 getVelocity();
    void setVelocity(atlas::math::Vector v);
    void collides();

private:
    GLuint mVao;
    float mass;
    int collisions;
    bool isAnchor;
    atlas::primitives::Sphere mPMass;
    atlas::math::Vector currPos, currForce;
    atlas::math::Vector mVelocity;
};

#endif
