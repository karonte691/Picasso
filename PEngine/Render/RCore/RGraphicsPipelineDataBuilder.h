#pragma once

#ifndef RGRAPHICS_PIPELINE_DATA_BUILDER_H
#define RGRAPHICS_PIPELINE_DATA_BUILDER_H

#include <PEngine/Render/RCore/Vertex.h>

#include <PEngine/Render/RCore/Shader.h>
#include <PEngine/Render/RCore/Texture.h>
#include <PEngine/Render/RCore/Material.h>
#include <PEngine/Render/RCore/Mesh.h>

#include <vector>
#include <memory>

namespace Picasso::Engine::Render::Core
{
    class RGraphicsPipelineDataBuilder
    {
    public:
        virtual ~RGraphicsPipelineDataBuilder(){};

        virtual bool Build() = 0;
        virtual PipelineData Get() = 0;

    protected:
        PipelineData m_PipelineData;

        virtual bool _GenerateShaders() = 0;
        virtual bool _GenerateTextures() = 0;
        virtual bool _GenerateMaterials() = 0;
        virtual bool _GenerateMesh() = 0;
    };
}

#endif