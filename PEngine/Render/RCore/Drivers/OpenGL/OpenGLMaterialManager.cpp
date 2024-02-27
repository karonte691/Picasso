#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMaterialManager.h>

#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    Material OpenGLMaterialManager::CreateMaterial(const Math::Vector3 &ambient,
                                                   const Math::Vector3 &diffuse,
                                                   const Math::Vector3 &specular,
                                                   float shininess,
                                                   Texture *diffuseTexture,
                                                   Texture *specularTexture)
    {
        return Material{ambient, diffuse, specular, shininess, diffuseTexture, specularTexture};
    }

    void OpenGLMaterialManager::SendMaterialToShader(Material material, Shader &shader)
    {
        shader.SetVector("material.ambient", material.Ambient);
        shader.SetVector("material.diffuse", material.Diffuse);
        shader.SetVector("material.specular", material.Specular);
        shader.SetVector("material.shininess", material.Shininess);
        shader.setTexture("material.diffuseTexture", material.DiffuseTexture->Id);
        shader.setTexture("material.specularTexture", material.SpecularTexture->Id);
    }
}