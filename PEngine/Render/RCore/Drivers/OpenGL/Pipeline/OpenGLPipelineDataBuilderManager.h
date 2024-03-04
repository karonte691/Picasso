#pragma once

#ifndef OPEN_GL_PIPELINE_DATA_BUILDER_MANAGER_H
#define OPEN_GL_PIPELINE_DATA_BUILDER_MANAGER_H

#include <PEngine/Render/RCore/Pipeline/PipelineDataBuilderManager.h>

namespace Picasso::Engine::Render::Core::Drivers::OpenGL
{
    class OpenGLPipelineDataBuilderManager : public Pipeline::PipelineDataBuilderManager
    {
    public:
        OpenGLPipelineDataBuilderManager();
    };
}

#endif // OPEN_GL_PIPELINE_DATA_BUILDER_MANAGER_H