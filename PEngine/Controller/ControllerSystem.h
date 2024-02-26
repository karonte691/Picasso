#pragma once

#ifndef CONTROLLER_SYSTEM_H
#define CONTROLLER_SYSTEM_H

#include <PEngine/Controller/PicassoController.h>
#include <memory>
#include <vector>

namespace Picasso::Engine::Controller
{
    class ControllerSystem
    {
    public:
        ControllerSystem();

        bool LoadControllers();
        void UpdateControllers();

    private:
        std::vector<std::unique_ptr<PicassoController>> p_Controllers;
    };
}

#endif // CONTROLLER_SYSTEM_H