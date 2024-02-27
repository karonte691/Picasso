#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include <PEngine/Math/Vector3.h>
#include <PEngine/Render/RCore/Texture.h>

namespace Picasso::Engine::Render::Core
{
    struct Material
    {
        Math::Vector3 Ambient;
        Math::Vector3 Diffuse;
        Math::Vector3 Specular;
        float Shininess;
        Texture *DiffuseTexture;
        Texture *SpecularTexture;
    };
}

#endif // MATERIAL_H