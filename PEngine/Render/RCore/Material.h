#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include <PEngine/Math/Vector3.h>
#include <PEngine/Render/RCore/Texture.h>

namespace Picasso::Engine::Render::Core
{
    class Material
    {
    public:
        Math::Vector3 Ambient;
        Math::Vector3 Diffuse;
        Math::Vector3 Specular;
        float Shininess;
        Texture *DiffuseTexture;
        Texture *SpecularTexture;

        Material(const Math::Vector3 &ambient,
                 const Math::Vector3 &diffuse,
                 const Math::Vector3 &specular,
                 float shininess,
                 Texture *diffuseTexture,
                 Texture *specularTexture)
            : Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess), DiffuseTexture(diffuseTexture), SpecularTexture(specularTexture) {}
    };
}

#endif // MATERIAL_H