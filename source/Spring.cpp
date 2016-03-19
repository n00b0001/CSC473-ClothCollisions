#include "Spring.hpp"
#include <atlas/core/Float.hpp>
#include <atlas/core/Log.hpp>
#include <atlas/core/Macros.hpp>
#include <atlas/core/GLFW.hpp>
#include <iostream>

Spring::Spring(float l, PointMass *a, PointMass *b) :
    mRestLen(l),
    b1(a),
    b2(b),
    hooke(30.0f),
    damping(1.0f)
{ }

Spring::~Spring() { }

void Spring::updateSpring(atlas::utils::Time const& t)
{
    USING_ATLAS_MATH_NS;
    // Update force of spring
    Vector force, dampingForce;
    Vector b1Pos = b1->getPos();
    Vector b2Pos = b2->getPos();
    Vector b1Vel = b1->getVelocity();
    Vector b2Vel = b2->getVelocity();
    Vector springForceDir = glm::normalize(b2Pos - b1Pos);
    float currLen = glm::length(b2Pos - b1Pos);
    force = hooke * (currLen - mRestLen) * springForceDir;
    dampingForce = damping * (b2Vel - b1Vel);
    Vector internalForce = force + dampingForce;

    // Apply the force to each ball
    b1->addForce(internalForce);
    b2->addForce(-1.0f * internalForce);
}
