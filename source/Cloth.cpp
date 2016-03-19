#include "Cloth.hpp"
#include <atlas/core/Float.hpp>
#include <atlas/core/Log.hpp>
#include <cmath>
#include <iostream>

Cloth::Cloth(Table t) :
    numX(0),
    numY(0),
    mSphere(t)
{
    bool firstColumn = true;
    for (float k = -10.0f; k <= 10.0f; k += 1.0f)
    {
        numX++;
        std::vector<PointMass*> currColumn;
        for (float l = 10.0f; l >= -10.0f; l -= 1.0f)
        {
            if (firstColumn) numY++;
            currColumn.push_back(new PointMass(glm::vec3(k,5.0f,l)));
        }
        firstColumn = false;
        mBalls.push_back(currColumn);
    }
    std::cout << "numX: " << numX << ", numY: " << numY << std::endl;
    for (int i = 0; i < numX; i++)
    {
        for (int j = 0; j < numY; j++)
        {
            if (i < numX-1)
                mSprings.push_back(new Spring(1.0f,mBalls[i][j],mBalls[i+1][j]));
            if (j < numY-1)
                mSprings.push_back(new Spring(1.0f,mBalls[i][j],mBalls[i][j+1]));
            float hypotenuse = sqrt(2.0f);
            if(i < numX-1 && j < numY-1)
                mSprings.push_back(new Spring(hypotenuse,mBalls[i][j],mBalls[i+1][j+1]));
            if(i < numX-1 && j > 0)
                mSprings.push_back(new Spring(hypotenuse,mBalls[i][j],mBalls[i+1][j-1]));
            if(i < numX-2)
                mSprings.push_back(new Spring(2.0f,mBalls[i][j],mBalls[i+2][j]));
            if(j < numY-2)
                mSprings.push_back(new Spring(2.0f,mBalls[i][j],mBalls[i][j+2]));
        }
    }
}

Cloth::~Cloth() { }

void Cloth::updateGeometry(const atlas::utils::Time &t)
{
    USING_ATLAS_MATH_NS;
    Vector grav(0.0f, -9.81f, 0.0f);

    // Reset forces on PointMass objects to zero
    for (auto column : mBalls)
        for (PointMass *ball : column)
        {
/*            Vector p = ball->getPos();
            Vector wind(sinf(p.x*p.y*t.currentTime),
                        cosf(p.z*t.currentTime),
                        sinf(cosf(5.0f*p.x*p.y*p.z)));*/
            ball->setForce(grav);
        }

    // Tell the springs to update their forces
    for (Spring *spring : mSprings)
    {
        spring->updateSpring(t);
    }

    // Tell the point mass objects to update their positions based on the spring forces
    for (auto column : mBalls)
        for (PointMass *ball : column)
            if(!ball->isAnchored()) ball->updateGeometry(t);
}

void Cloth::renderGeometry(atlas::math::Matrix4 projection, atlas::math::Matrix4 view)
{
    for (int i = 0; i < numY; i++)
    {
        for (int j = 0; j < numX; j++)
        {
            mBalls[j][i]->renderGeometry(projection, view);
        }
    }
}

void Cloth::resetGeometry()
{ }

bool Cloth::testCollision(PointMass p, Table t)
{
    USING_ATLAS_MATH_NS;
    Vector Tpos = t.getPos();
    Vector Ppos = p.getPos();
    Vector distance = Tpos - Ppos;
    if (distance.length() <= t.getRad())
    {
        p.collides();
        return true;
    }
    return false;
}
