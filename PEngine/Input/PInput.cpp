#include <PEngine/Input/PInput.h>

namespace Picasso::Engine::Input
{
    void PInput::Init()
    {
        p_InputListener = std::make_unique<InputListener>();
        p_InputListener->Init();

        Picasso::Engine::Logger::Logger::Info("Input system initialized");
    }

    void PInput::Shutdown()
    {
        p_InputListener->Destroy();
    }
}