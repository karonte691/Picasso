#pragma once

#ifndef PIPELINE_DATA_BUILDER_MANAGER_H
#define PIPELINE_DATA_BUILDER_MANAGER_H

#include <PEngine/Render/RCore/Vertex.h>
#include <PEngine/Render/RCore/Shader.h>
#include <PEngine/Render/RCore/Texture.h>
#include <PEngine/Render/RCore/Material.h>
#include <PEngine/Render/RCore/Mesh.h>

#include <PEngine/Render/RCore/Pipeline/PipelineDataBuilderBase.h>

#include <vector>
#include <memory>

namespace Picasso::Engine::Render::Core::Pipeline
{
    class PipelineDataBuilderManager
    {
    public:
        virtual ~PipelineDataBuilderManager(){};

        bool Build();
        PipelineData Get();

    protected:
        PipelineData m_PipelineData;

        std::vector<std::unique_ptr<Pipeline::PipelineDataBuilderBase>> m_Builders;
    };
}

#endif // PIPELINE_DATA_BUILDER_MANAGER_H