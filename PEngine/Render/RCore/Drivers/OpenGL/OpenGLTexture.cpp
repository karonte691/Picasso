#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTexture.h>

#include <SOIL/SOIL.h>
#include <PEngine/File/PFLoader.h>
#include <PEngine/Logger/Logger.h>
#include <memory>
#include <stdexcept>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    bool OpenGLTexture::LoadTexture(const char *textureName)
    {
        std::unique_ptr<File::PFLoader> fileLoader = std::make_unique<File::PFLoader>();

        File::PFile textureFile = fileLoader->LoadTexture(textureName);

        if (textureFile.fileName.empty())
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureLoader] unable to load the texture %s", textureName);
            return false;
        }

        m_Texture.imageWidth = 0;
        m_Texture.imageHeight = 0;

        m_Texture.image = SOIL_load_image(textureFile.absolutePath.c_str(), &m_Texture.imageWidth, &m_Texture.imageHeight, 0, SOIL_LOAD_RGBA);

        if (!m_Texture.image)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureLoader] unable to load the image from texture %s", textureName);
            return false;
        }

        glGenTextures(1, &m_TextureMemId);
        glBindTexture(GL_TEXTURE_2D, m_TextureMemId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Texture.imageWidth, m_Texture.imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Texture.image);
        glGenerateMipmap(GL_TEXTURE_2D);

        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        SOIL_free_image_data(m_Texture.image);

        GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureLoader] OpenGL error occurred while loading texture %s: %u", textureName, error);
            return false;
        }

        return true;
    }

    bool OpenGLTexture::ActivateTexture()
    {
        try
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_TextureMemId);
        }
        catch (std::exception &e)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTextureLoader] Exception occurred while activating texture: %s", e.what());
            return false;
        }

        return true;
    }
}