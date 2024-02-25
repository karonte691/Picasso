#include <PEngine/Input/PInput.h>

namespace Picasso::Engine::Input
{
    void PInput::Init()
    {
        m_inputState = {};
        p_InputListener = std::make_unique<InputListener>();

        p_InputListener->Init();

        Picasso::Engine::Logger::Logger::Info("Input system initialized");
    }

    void PInput::Shutdown()
    {
        return;
    }
}