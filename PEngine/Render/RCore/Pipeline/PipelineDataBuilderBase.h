#pragma once

#ifndef PIPELINE_DATA_BUILDER_BASE_H
#define PIPELINE_DATA_BUILDER_BASE_H

#include <PEngine/Render/RCore/Vertex.h>
#include <PEngine/Render/RCore/Shader.h>
#include <PEngine/Render/RCore/Texture.h>
#include <PEngine/Render/RCore/Material.h>
#include <PEngine/Render/RCore/Mesh.h>

#include <vector>
#include <memory>

namespace Picasso::Engine::Render::Core::Pipeline
{
    struct PipelineData
    {
        std::unique_ptr<Shader> shader;
        std::vector<std::unique_ptr<Mesh>> meshes;
        std::vector<std::unique_ptr<Texture>> textures;
        std::vector<std::unique_ptr<Material>> materials;
    };

    class PipelineDataBuilderBase
    {
    public:
        virtual ~PipelineDataBuilderBase(){};

        virtual bool Build(PipelineData *pipelineData) = 0;
    };
}

#endif // PIPELINE_DATA_BUILDER_BASE_H