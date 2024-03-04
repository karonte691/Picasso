#pragma once

#ifndef OPEN_GL_VP_MATRIX_MANAGER_H
#define OPEN_GL_VP_MATRIX_MANAGER_H

#include <memory>
#include <PEngine/Math/Mat4.h>
#include <PEngine/Math/Vector3.h>
#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLVPMatrixManager
    {
    public:
        void CreateViewMatrix();
        void UniformViewMatrix(GLuint shaderId);

        void CreateProjectionMatrix(float width, float height);
        void UniforProjectionMatrix(GLuint shaderId);
        void ResetProjectionMatrix(float width, float height);

        void UniformMatrices(GLuint shaderId);

        void UniformCameraPosition(unsigned int shaderProgram);

    private:
        std::unique_ptr<Math::Mat4> p_ViewMatrix;
        std::unique_ptr<Math::Mat4> p_ProjectionMatrix;
        Math::Vector3 m_CamPosition;
        Math::Vector3 m_WorlUp;
        Math::Vector3 m_CamFront;

        void _initProjectionMatrix(float width, float height);
    };
}
#endif