#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTextureManager.h>

#include <SOIL/SOIL.h>
#include <PEngine/File/PFLoader.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLError.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTexture.h>
#include <memory>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    bool OpenGLTextureManager::LoadTextures(const std::vector<std::string> textures)
    {
        unsigned int tSize = textures.size();

        if (tSize == 0)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureLoader] no textures to load");
            return false;
        }

        for (unsigned int i = 0; i < tSize; ++i)
        {
            if (!_LoadTexture(textures[i].c_str(), i))
            {
                return false;
            }
        }

        Picasso::Engine::Logger::Logger::Debug("Textures loaded correctly");

        return true;
    }

    bool OpenGLTextureManager::ActivateTextures(const unsigned int shaderProgram, Texture **textures, int tSize)
    {
        if (tSize == 0)
        {
            // no texture to activate, quit
            return false;
        }

        for (unsigned int i = 0; i < tSize; ++i)
        {
            if (!textures[i]->ActivateTexture(i))
            {
                Picasso::Engine::Logger::Logger::Error("[OpenGLTextureLoader] unable to activate texture %d", i);
                return false;
            }
        }

        return true;
    }

    bool OpenGLTextureManager::BindTextures(const unsigned int shaderProgram)
    {
        unsigned int tSize = m_Textures.size();

        if (tSize == 0)
        {
            // no texture to bind, quit
            return true;
        }

        for (unsigned int i = 0; i < tSize; ++i)
        {
            std::string samplerName = "texture" + std::to_string(i);

            m_Textures[i].UniformTexture(i, shaderProgram, samplerName.c_str());
        }

        return true;
    }

    std::vector<std::unique_ptr<Texture>> OpenGLTextureManager::GetTextures()
    {
        std::vector<std::unique_ptr<Texture>> textures;

        for (unsigned int i = 0; i < m_Textures.size(); ++i)
        {
            textures.push_back(std::make_unique<OpenGLTexture>(m_Textures[i].Id,
                                                               m_Textures[i].TextureUnit,
                                                               m_Textures[i].Width,
                                                               m_Textures[i].Height));
        }

        return textures;
    }

    /**
     * Loads a texture from a file and stores it in the m_Textures vector.
     *
     * @param textureName The name of the texture file to load.
     * @param textureUnit The texture unit to bind the texture to.
     * @return True if the texture was successfully loaded and stored, false otherwise.
     */
    bool OpenGLTextureManager::_LoadTexture(const char *textureName, const unsigned int textureUnit)
    {
        std::unique_ptr<File::PFLoader> fileLoader = std::make_unique<File::PFLoader>();
        GLuint textureId;

        Picasso::Engine::Logger::Logger::Debug("[OpenGLTextureManager] loading texture %s", textureName);

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

        SOIL_free_image_data(image);

        GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureLoader] OpenGL error occurred while loading texture %s: %u", textureName, error);
            return false;
        }

        m_Textures.push_back(OpenGLTexture(textureId, textureUnit, imageWidth, imageHeight));

        return true;
    }
}