#pragma once

#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include <PEngine/Math/Vector3.h>

namespace Picasso::Engine::Render::Core
{
    class LightManager
    {
    public:
        virtual ~LightManager(){};

        virtual void SetLightPosition(const Math::Vector3 position) = 0;
        virtual void UniformLightPosition(unsigned int shaderProgram) = 0;

    protected:
        Math::Vector3 m_LightPosition;
    };
}

#endif // LIGHT_MANAGER_H