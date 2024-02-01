#pragma once

#ifndef R_SHADER_H
#define R_SHADER_H

namespace Picasso::Engine::Render::Core
{
    /**
     *  Each driver has it's own children implementation of tshaders.
     *  This class serve the purpose to abstract the low level code
     *  from this layer of Picasso
     */
    class RShader
    {
    public:
        virtual ~RShader(){};

        virtual void Use() = 0;
        virtual void Destroy() = 0;
    };
}

#endif