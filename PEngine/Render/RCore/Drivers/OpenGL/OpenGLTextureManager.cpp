#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTextureManager.h>

#include <SOIL/SOIL.h>
#include <PEngine/File/PFLoader.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLError.h>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    bool OpenGLTextureManager::LoadTextures(std::vector<std::string> textures)
    {
        unsigned int tSize = textures.size();

        if (tSize == 0)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureLoader] no textures to load");
            return false;
        }

        for (unsigned int i = 0; i < tSize; ++i)
        {
            if (!_LoadTexture(textures[i].c_str()))
            {
                return false;
            }
        }

        Picasso::Engine::Logger::Logger::Error("Textures loaded correctly");

        return true;
    }

    bool OpenGLTextureManager::ActivateTextures(unsigned int shaderProgram)
    {
        unsigned int tSize = m_Textures.size();

        if (tSize == 0)
        {
            // no texture to activate, quit
            return true;
        }

        for (unsigned int i = 0; i < tSize; ++i)
        {
            if (!m_Textures[i].ActivateTexture(i))
            {
                return false;
            }

            const char *samplerName = "texture" + i;

            if (!_SetTextureSampler(shaderProgram, samplerName, i))
            {
                return false;
            }
        }

        return true;
    }

    bool OpenGLTextureManager::_SetTextureSampler(GLuint shaderProgram, const char *samplerName, int textureUnit)
    {
        GLint samplerLocation = glGetUniformLocation(shaderProgram, samplerName);

        if (samplerLocation == -1)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTexture] Sampler uniform '%s' not found in shader program", samplerName);
            return false;
        }

        glUniform1i(samplerLocation, textureUnit);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTexture] Error setting texture sampler '%s': %u", samplerName, error);
            return false;
        }

        return true;
    }

    bool OpenGLTextureManager::_LoadTexture(const char *textureName)
    {
        std::unique_ptr<File::PFLoader> fileLoader = std::make_unique<File::PFLoader>();
        GLuint textureId;

        File::PFile textureFile = fileLoader->LoadTexture(textureName);

        if (textureFile.fileName.empty())
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureManager] unable to load the texture %s", textureName);
            return false;
        }

        int imageWidth = 0;
        int imageHeight = 0;
        unsigned char *image = SOIL_load_image(textureFile.absolutePath.c_str(), &imageWidth, &imageHeight, 0, SOIL_LOAD_RGBA);

        if (!image)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureManager] unable to load the image from texture %s", textureName);
            return false;
        }

        CHECK_GL_ERROR(glGenTextures(1, &textureId));
        CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, textureId));

        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

        CHECK_GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image));
        CHECK_GL_ERROR(glGenerateMipmap(GL_TEXTURE_2D));

        glBindTexture(GL_TEXTURE_2D, 0);

        SOIL_free_image_data(image);

        GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureLoader] OpenGL error occurred while loading texture %s: %u", textureName, error);
            return false;
        }

        OpenGLTexture texture(textureId);
        texture.Width = imageWidth;
        texture.Height = imageHeight;

        m_Textures.push_back(texture);

        return true;
    }

}