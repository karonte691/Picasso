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

        return true;
    }
}