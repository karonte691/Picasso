#pragma once

#ifndef OPEN_GL_MATERIAL_H
#define OPEN_GL_MATERIAL_H

#include <PEngine/Render/RCore/MaterialManager.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLMaterialManager : public MaterialManager
    {
    public:
        Material CreateMaterial(const Math::Vector3 &ambient,
                                const Math::Vector3 &diffuse,
                                const Math::Vector3 &specular,
                                float shininess,
                                Texture *diffuseTexture,
                                Texture *specularTexture) override;
        void SendMaterialToShader(Material material, Shader &shader) override;
    };
}

#endif // OPEN_GL_MATERIAL_H