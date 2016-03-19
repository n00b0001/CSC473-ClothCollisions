#include "ClothCamera.hpp"
#include <atlas/utils/Time.hpp>
#include <math.h>
#include "Quaternion.hpp"

ClothCamera::ClothCamera() :
    cameraPosition(20.0f, 15.0f, 20.0f),
    cameraTarget(0.0f, 0.0f, 0.0f),
    cameraDirection(glm::normalize(cameraPosition - cameraTarget)),
    up(0.0f, 1.0f, 0.0f)
{ }

ClothCamera::~ClothCamera()
{ }

atlas::math::Matrix4 ClothCamera::getCameraMatrix()
{
    return glm::lookAt(cameraPosition, cameraTarget, glm::vec3(0.0f, 1.0f, 0.0f));
}

void ClothCamera::doQuatRotate(atlas::utils::Time const& t)
{
    USING_ATLAS_MATH_NS;
    Vector axis(0.0f, 1.0f, 0.0f);
    float theta = t.deltaTime / (2 * M_PI);

    Quaternion rotation = Quaternion();
    rotation.W = cos(theta / 2.0f);
    rotation.V.x = axis.x * sin(theta / 2.0f);
    rotation.V.y = axis.y * sin(theta / 2.0f);
    rotation.V.z = axis.z * sin(theta / 2.0f);

    Quaternion view(0.0f, cameraPosition);
    Quaternion newView = Quaternion();
    newView = rotation * view * rotation.conjugate();

    cameraPosition = Vector(newView.V.x, newView.V.y, newView.V.z);
}
