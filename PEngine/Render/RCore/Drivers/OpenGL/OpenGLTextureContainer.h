#pragma once

#ifndef OPEN_GL_TEXTURE_CONTAINER_H
#define OPEN_GL_TEXTURE_CONTAINER_H

#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTexture.h>

#include <string>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    struct OpenGLTextureContainer
    {
        std::string name;
        std::unique_ptr<OpenGLTexture> diffuseTexture;
        std::unique_ptr<OpenGLTexture> specularTexture;

        OpenGLTextureContainer() : name("defaultTextureContainer"),
                                   diffuseTexture(std::make_unique<OpenGLTexture>(0, 0, 0, 0)),
                                   specularTexture(std::make_unique<OpenGLTexture>(0, 0, 0, 0)) {}

        OpenGLTextureContainer(std::string name) : name(name),
                                                   diffuseTexture(std::make_unique<OpenGLTexture>(0, 0, 0, 0)),
                                                   specularTexture(std::make_unique<OpenGLTexture>(0, 0, 0, 0)) {}

        void AddDiffuseTexture(unsigned int id, unsigned int textureUnit, unsigned int width, unsigned int height)
        {
            diffuseTexture = std::make_unique<OpenGLTexture>(id, textureUnit, width, height);
        }

        void AddSpecularTexture(unsigned int id, unsigned int textureUnit, unsigned int width, unsigned int height)
        {
            specularTexture = std::make_unique<OpenGLTexture>(id, textureUnit, width, height);
        }
    };
}

#endif // OPEN_GL_TEXTURE_CONTAINER_H