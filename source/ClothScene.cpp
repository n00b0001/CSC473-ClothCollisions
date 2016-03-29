#include "ClothScene.hpp"

#include <atlas/core/GLFW.hpp>
#include <atlas/core/Log.hpp>
#include <atlas/core/Macros.hpp>
#include <atlas/core/Float.hpp>
#include <iostream>

ClothScene::ClothScene() :
    mIsPlaying(false),
    mLastTime(0.0f),
    mFPS(60.0f),
    mTick(1.0f / mFPS),
    mAnimTime(0.0f),
    mAnimLength(10.0f),
    mTable(4.0f),
    mCloth(mTable)
{
    glEnable(GL_DEPTH_TEST);
}

ClothScene::~ClothScene()
{ }

// Comment out mousePressEvent and mouseMoveEvent if using a Quaternion Camera
void ClothScene::mousePressEvent(int button, int action, int modifiers,
    double xPos, double yPos)
{
    USING_ATLAS_MATH_NS;

    if (button == GLFW_MOUSE_BUTTON_LEFT && modifiers == GLFW_MOD_ALT)
    {
        if (action == GLFW_PRESS)
        {
            mIsDragging = true;
            mCamera.mouseDown(Point2(xPos, yPos),
                MayaCamera::CameraMovements::TUMBLE);
        }
        else
        {
            mIsDragging = false;
            mCamera.mouseUp();
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE && modifiers == GLFW_MOD_ALT)
    {
        if (action == GLFW_PRESS)
        {
            mIsDragging = true;
            mCamera.mouseDown(Point2(xPos, yPos),
                MayaCamera::CameraMovements::TRACK);
        }
        else
        {
            mIsDragging = false;
            mCamera.mouseUp();
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && modifiers == GLFW_MOD_ALT)
    {
        if (action == GLFW_PRESS)
        {
            // first click.
            mIsDragging = true;
            mCamera.mouseDown(Point2(xPos, yPos),
                MayaCamera::CameraMovements::DOLLY);
        }
        else
        {
            mIsDragging = false;
            mCamera.mouseUp();
        }
    }
    else if (action != GLFW_PRESS)
    {
        mIsDragging = false;
        mCamera.mouseUp();
    }
}

void ClothScene::mouseMoveEvent(double xPos, double yPos)
{
    if (mIsDragging)
    {
        mCamera.mouseDrag(atlas::math::Point2(xPos, yPos));
    }
}

void ClothScene::keyPressEvent(int key, int scancode, int action, int mods)
{
    UNUSED(scancode);
    UNUSED(mods);

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_R:
            mCamera.resetCamera();
            break;
/*
        case GLFW_KEY_S:
            mSpline.showSpline();
            break;

        case GLFW_KEY_C:
            mSpline.showControlPoints();
            break;

        case GLFW_KEY_G:
            mSpline.showCage();
            break;

        case GLFW_KEY_P:
            mSpline.showSplinePoints();
            break;
*/
        case GLFW_KEY_SPACE:
            mIsPlaying = !mIsPlaying;


        default:
            break;
        }
    }
}

void ClothScene::screenResizeEvent(int width, int height)
{
    glViewport(0, 0, width, height);
    mProjection = glm::perspective(glm::radians(45.0),
        (double)width / height, 1.0, 1000.0);
}

void ClothScene::renderScene()
{
    float grey = 161.0f / 255.0f;
    glClearColor(grey, grey, grey, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    mView = mCamera.getCameraMatrix();
    mGrid.renderGeometry(mProjection, mView);
    mCloth.renderGeometry(mProjection, mView);
    mTable.renderGeometry(mProjection, mView);
}

void ClothScene::updateScene(double time)
{
    if (mIsPlaying)
        {
            // Handle the timing stuff here.
            mTime.deltaTime = (float)time - mTime.currentTime;
            mTime.totalTime += mTime.deltaTime;
            mTime.currentTime = (float)time;

            mTime.deltaTime *= 2.0f;

            // Tell our cloth to update itself.
            mCloth.updateGeometry(mTime);

            // Do some quaternion magic here to move camera
//            mCamera.doQuatRotate(mTime);

        }
}
