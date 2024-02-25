#include <PEngine/Controller/ControllerSystem.h>

#include <PEngine/Logger/Logger.h>
#include <PEngine/Controller/MovementController.h>
#include <PEngine/Controller/CameraController.h>

namespace Picasso::Engine::Controller
{
    ControllerSystem::ControllerSystem()
    {
        p_Controllers.push_back(std::make_unique<MovementController>());
        p_Controllers.push_back(std::make_unique<CameraController>());
    }

    bool ControllerSystem::LoadControllers()
    {
        for (auto &controller : p_Controllers)
        {
            if (!controller->InitController())
            {
                Picasso::Engine::Logger::Logger::Error("Failed to initialize controller: %s", controller->GeControllerName());
                return false;
            }
        }
        return true;
    }
}