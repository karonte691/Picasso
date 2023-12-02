#include <PEngine/Input/PInput.h>

namespace Picasso::Engine::Input
{
    void PInput::Init()
    {
        m_inputState = {};
        Picasso::Logger::Logger::Info("Input system initialized");
    }

    void PInput::Shutdown()
    {
        return;
    }

    void PInput::Update(double deltaTime)
    {
        
    }
}