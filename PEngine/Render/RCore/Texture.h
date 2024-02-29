#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

namespace Picasso::Engine::Render::Core
{
    /**
     *  Each driver has it's own children implementation of Texture.
     *  This class serve the purpose to abstract the low level code
     *  from this layer of Picasso
     */
    class Texture
    {
    public:
        unsigned int Id;
        unsigned int TextureUnit;
        unsigned int Width;
        unsigned int Height;

        Texture(unsigned int id, unsigned int textureUnit, unsigned int width, unsigned int height)
            : Id(id), TextureUnit(textureUnit), Width(width), Height(height){};

        virtual ~Texture(){};

        virtual bool ActivateTexture(unsigned int unit) = 0;
        virtual bool UniformTexture(unsigned int unit, unsigned int shaderProgram, const char *samplerName) = 0;
    };
}

#endif // TEXTURE_H