#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLTexture.h>

#include <PEngine/Logger/Logger.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    bool OpenGLTexture::ActivateTexture(unsigned int unit)
    {
        if (unit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTexture] Texture unit %u is out of range", unit);
            return false;
        }

        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, Id);

        GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTexture] Exception occurred while activating texture: %u", error);
            return false;
        }

        TextureUnit = unit;

        return true;
    }

    bool OpenGLTexture::UniformTexture(unsigned int unit, unsigned int shaderProgram, const char *samplerName)
    {
        GLint samplerLocation = glGetUniformLocation(shaderProgram, samplerName);

        if (samplerLocation == -1)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTexture] Sampler uniform '%s' not found in shader program", samplerName);
            return false;
        }

        glUniform1i(samplerLocation, unit);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLTexture] Error setting texture sampler '%s': %u", samplerName, error);
            return false;
        }

        return true;
    }
}