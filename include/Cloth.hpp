#ifndef ASS_02_CLOTH_HPP
#define ASS_02_CLOTH_HPP

#pragma once

#include "PointMass.hpp"
#include "Spring.hpp"
#include "Table.hpp"
#include <atlas/utils/Geometry.hpp>

class Cloth : public atlas::utils::Geometry
{
public:
    Cloth(Table &t);
    ~Cloth();

    void updateGeometry(atlas::utils::Time const& t) override;
    void renderGeometry(atlas::math::Matrix4 projection, atlas::math::Matrix4 view) override;
    void resetGeometry() override;
    bool testCollision(PointMass *p);

private:
    int numX;
    int numY;
    std::vector<std::vector<PointMass*> > mBalls;
    std::vector<Spring*> mSprings;
    Table& mSphere;
};


#endif
