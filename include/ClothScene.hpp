#ifndef ASS02_INCLUDE_SPLINE_SCENE_HPP
#define ASS02_INCLUDE_SPLINE_SCENE_HPP

#pragma once

#include <atlas/utils/Scene.hpp>
#include "MayaCamera.hpp"
#include "Grid.hpp"
#include "Cloth.hpp"
#include "Table.hpp"

class ClothScene : public atlas::utils::Scene
{
public:
    ClothScene();
    ~ClothScene();

    void keyPressEvent(int key, int scancode, int action, int mods) override;
    void mousePressEvent(int button, int action, int modifiers,
        double xPos, double yPos) override;
    void mouseMoveEvent(double xPos, double yPos) override;
    void screenResizeEvent(int width, int height) override;
    void renderScene() override;
    void updateScene(double time) override;

private:
    bool mIsDragging;
    bool mIsPlaying;

    float mLastTime;
    float mFPS;
    float mTick;

    float mAnimTime;
    float mAnimLength;
//  ClothCamera mCamera;
    MayaCamera mCamera;
    Grid mGrid;
    Table mTable;
    Cloth mCloth;
};

#endif
