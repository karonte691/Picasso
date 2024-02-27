#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <PEngine/Math/Vector2.h>
#include <PEngine/Math/Vector3.h>
#include <PEngine/Math/Vector4.h>
#include <PEngine/Math/Mat4.h>

namespace Picasso::Engine::Render::Core
{
    /**
     *  Each driver has it's own children implementation of shader.
     *  This class serve the purpose to abstract the low level code
     *  from this layer of Picasso
     */
    class Shader
    {
    public:
        virtual ~Shader(){};

        virtual void Use() = 0;
        virtual void Clear() = 0;
        virtual void Destroy() = 0;

        // vector operations
        virtual void SetVector(const char *name, const float value) = 0;
        virtual void SetVector(const char *name, const Math::Vector2 value) = 0;
        virtual void SetVector(const char *name, const Math::Vector3 value) = 0;
        virtual void SetVector(const char *name, const Math::Vector4 value) = 0;

        virtual void SetMatrix(const char *name, const Math::Mat4 value) = 0;

        virtual void setTexture(const char *name, const int value) = 0;
    };
}

#endif