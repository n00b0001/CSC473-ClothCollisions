#include "Table.hpp"
#include "ShaderPaths.hpp"
#include <atlas/gl/ErrorCheck.hpp>

Table::Table(float r) :
    radius(r),
    currPos(glm::vec3(0.0f,0.0f,0.0f)),
    mSphere(r, 50, 50)
{
    USING_ATLAS_MATH_NS;
    USING_ATLAS_GL_NS;

    std::string shaderDir = generated::ShaderPaths::getShaderDirectory();

    std::vector<ShaderInfo> shaders
    {
        { GL_VERTEX_SHADER, shaderDir + "ball.vs.glsl" },
        { GL_FRAGMENT_SHADER, shaderDir + "ball.fs.glsl" }
    };

    mShaders.push_back(ShaderPointer(new Shader));
    mShaders[0]->compileShaders(shaders);
    mShaders[0]->linkShaders();

    mUniforms.insert(UniformKey("mvpMat",
        mShaders[0]->getUniformVariable("mvpMat")));

    mSphere.createBuffers();

    mModel = glm::translate(Matrix4(1.0f), currPos);

    mShaders[0]->disableShaders();
}

Table::~Table() { }

void Table::updateGeometry(const atlas::utils::Time &t)
{
}

void Table::renderGeometry(atlas::math::Matrix4 projection, atlas::math::Matrix4 view)
{
    mShaders[0]->enableShaders();

    auto mvpMat = projection * view * mModel;
    glUniformMatrix4fv(mUniforms["mvpMat"], 1, GL_FALSE, &mvpMat[0][0]);

    mSphere.drawPrimitive();

    mShaders[0]->disableShaders();
}

void Table::transformGeometry(atlas::math::Matrix4 const& t)
{
    mModel = t;
}

const glm::vec3 Table::getPos()
{
    return currPos;
}

const float Table::getRad()
{
    return radius;
}
