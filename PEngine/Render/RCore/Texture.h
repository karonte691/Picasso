#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

namespace Picasso::Engine::Render::Core
{
    struct PTexture
    {
        int imageWidth;
        int imageHeight;
        unsigned char *image;
    };

    class Texture
    {
    public:
        virtual ~Texture(){};

        virtual bool LoadTexture(const char *textureName) = 0;
        virtual bool ActivateTexture() = 0;

    protected:
        PTexture m_Texture;
    };
}

#endif