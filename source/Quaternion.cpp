#include "Quaternion.hpp"

Quaternion::Quaternion() :
    W(0.0f),
    V(0.0f)
{}

Quaternion::Quaternion(float w, glm::vec3 v) :
    W(w),
    V(v)
{}

Quaternion::~Quaternion()
{ }

float Quaternion::length()
{
    return sqrt(V.x * V.x + V.y * V.y + V.z * V.z + W * W);
}

Quaternion Quaternion::normalize()
{
    float L = length();
    Quaternion q = Quaternion();
    q.V.x /= L;
    q.V.y /= L;
    q.V.z /= L;
    q.W /= L;

    return q;
}

Quaternion Quaternion::conjugate()
{
    return Quaternion(W, -1.0f * V);
}

Quaternion Quaternion::operator* (Quaternion const& q)
{
    Quaternion R;
    R.V.x = W*q.V.x + V.x*q.W + V.y*q.V.z - V.z*q.V.y;
    R.V.y = W*q.V.y + V.y*q.W + V.z*q.V.x - V.x*q.V.z;
    R.V.z = W*q.V.z + V.z*q.W + V.x*q.V.y - V.y*q.V.x;
    R.W = W*q.W - V.x*q.V.x - V.y*q.V.y - V.z*q.V.z;
    return R;
}
