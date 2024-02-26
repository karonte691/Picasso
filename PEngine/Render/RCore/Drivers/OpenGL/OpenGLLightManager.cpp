#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLLightManager.h>

#include <Glew/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    void OpenGLLightManager::SetLightPosition(const Math::Vector3 position)
    {
        m_LightPosition = position;
    }

    void OpenGLLightManager::UniformLightPosition(unsigned int shaderProgram)
    {
        int lightPositionLocation = glGetUniformLocation(shaderProgram, "lightPosition");
        glUniform3fv(lightPositionLocation, 1, &m_LightPosition.x);
    }
}