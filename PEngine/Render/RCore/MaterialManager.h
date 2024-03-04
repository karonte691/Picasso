#pragma once

#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include <PEngine/Render/RCore/Material.h>
#include <PEngine/Render/RCore/Shader.h>
#include <PEngine/Math/Vector3.h>

#include <memory>

namespace Picasso::Engine::Render::Core
{
    /**
     *  Each driver has it's own children implementation of MaterialManager
     *  but the struct(Material) is defined at this level.
     *  This class serve the purpose to abstract the low level code
     *  from this layer of Picasso
     */
    class MaterialManager
    {
    public:
        virtual ~MaterialManager(){};

        virtual std::unique_ptr<Material> CreateMaterial(const Math::Vector3 &ambient,
                                                         const Math::Vector3 &diffuse,
                                                         const Math::Vector3 &specular,
                                                         float shininess,
                                                         Texture *diffuseTexture,
                                                         Texture *specularTexture) = 0;
        virtual void SendMaterialToShader(const Material *material, Shader *shader) = 0;
    };
}

#endif