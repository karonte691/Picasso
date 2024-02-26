#pragma once

#ifndef OPEN_GL_LIGHT_MANAGER_H
#define OPEN_GL_LIGHT_MANAGER_H

#include <PEngine/Render/RCore/LightManager.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLLightManager : public LightManager
    {
    public:
        void SetLightPosition(const Math::Vector3 position) override;
        void UniformLightPosition(unsigned int shaderProgram) override;
    };
}

#endif // OPEN_GL_LIGHT_MANAGER_H