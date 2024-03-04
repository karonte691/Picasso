#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLPipelineDataBuilderManager.h>

#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLTextureBuilder.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLShadersBuilder.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLMaterialBuilder.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLMeshBuilder.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    OpenGLPipelineDataBuilderManager::OpenGLPipelineDataBuilderManager()
    {
        m_Builders.push_back(std::make_unique<OpenGLShadersBuilder>());
        m_Builders.push_back(std::make_unique<OpenGLTextureBuilder>());
        m_Builders.push_back(std::make_unique<OpenGLMaterialBuilder>());
        m_Builders.push_back(std::make_unique<OpenGLMeshBuilder>());
    }
}