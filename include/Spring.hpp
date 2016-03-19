#ifndef ASS02_SPRING_HPP
#define ASS02_SPRING_HPP

#pragma once

#include "PointMass.hpp"

class Spring
{
public:
    Spring(float l, PointMass *a, PointMass *b);
    ~Spring();

    void updateSpring(atlas::utils::Time const& t);


private:
    float mRestLen;
    PointMass *b1, *b2;
    float hooke, damping;
};

#endif
