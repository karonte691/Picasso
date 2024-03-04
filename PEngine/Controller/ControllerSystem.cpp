/**
 * @file ControllerSystem.cpp
 * @brief Implementation of the ControllerSystem class.
 */
#include <PEngine/Controller/ControllerSystem.h>

#include <PEngine/Logger/Logger.h>
#include <PEngine/Controller/MovementController.h>
#include <PEngine/Controller/CameraController.h>

namespace Picasso::Engine::Controller
{
    /**
     * @brief Default constructor for the ControllerSystem class.
     */
    ControllerSystem::ControllerSystem()
    {
        p_Controllers.push_back(std::make_unique<MovementController>());
        p_Controllers.push_back(std::make_unique<CameraController>());
    }

    /**
     * @brief Loads and initializes the controllers.
     * @return True if all controllers are successfully initialized, false otherwise.
     */
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

    /**
     * @brief Updates all the controllers.
     */
    void ControllerSystem::UpdateControllers()
    {
        for (auto &controller : p_Controllers)
        {
            controller->Update();
        }
    }
}