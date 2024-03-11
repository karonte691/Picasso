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
        void UniformViewMatrix(GLuint shaderId);

        void UniformCameraPosition(GLuint shaderId);

        void CreateProjectionMatrix(float width, float height);
        void UniforProjectionMatrix(GLuint shaderId);
        void ResetProjectionMatrix(float width, float height);

        void UniformMatrices(GLuint shaderId);

    private:
        std::unique_ptr<Math::Mat4> p_ProjectionMatrix;

        void _initProjectionMatrix(float width, float height);
    };
}
#endif