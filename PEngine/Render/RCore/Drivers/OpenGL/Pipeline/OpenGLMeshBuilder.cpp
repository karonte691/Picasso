#include <PEngine/Render/RCore/Drivers/OpenGL/Pipeline/OpenGLMeshBuilder.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMeshManager.h>
#include <PEngine/Render/RCore/Primitives/Quad.h>
#include <PEngine/Render/RCore/Drivers/OpenGL/OpenGLMesh.h>

#include <PEngine/Logger/Logger.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    OpenGLMeshBuilder::OpenGLMeshBuilder()
    {
        p_MeshManager = std::make_unique<OpenGLMeshManager>();
    }

    /**
     * @brief Builds a new mesh.
     *
     * @param pipelineData A pointer to the PipelineData object.
     * @return True if the mesh is successfully built, false otherwise.
     */
    bool OpenGLMeshBuilder::Build(Pipeline::PipelineData *pipelineData)
    {
        Primitives::Quad *pQuad = new Primitives::Quad();
        std::unique_ptr<Mesh> p_Mesh = p_MeshManager->Create(pQuad,
                                                             Math::Vector3(0.0f, 0.0f, 0.0f),
                                                             Math::Vector3(0.0f, 0.0f, 0.0f),
                                                             Math::Vector3(1.0f, 1.0f, 1.0f));

        if (p_Mesh == nullptr)
        {
            Picasso::Engine::Logger::Logger::Error("[OpenGLMeshBuilder]: Failed to create mesh");
            return false;
        }

        delete pQuad;
        pipelineData->meshes.push_back(std::move(p_Mesh));

        return true;
    }

} // namespace Picasso::Engine::Render::Core::Drivers::OpenGL