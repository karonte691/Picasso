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
        unsigned int Width;
        unsigned int Height;

        Texture(unsigned int id) : Id(id){};
        virtual ~Texture(){};
    };
}

#endif // TEXTURE_H