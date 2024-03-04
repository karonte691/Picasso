#include <PEngine/Render/RCore/Pipeline/PipelineDataBuilderManager.h>

namespace Picasso::Engine::Render::Core::Pipeline
{
    bool PipelineDataBuilderManager::Build()
    {
        m_PipelineData = {};

        for (auto &builder : m_Builders)
        {
            if (!builder->Build(&m_PipelineData))
            {
                return false;
            }
        }

        return true;
    }

    PipelineData PipelineDataBuilderManager::Get()
    {
        PipelineData tmpData = std::move(m_PipelineData);

        m_PipelineData = {}; // reset it after getting the data

        return tmpData;
    }
}