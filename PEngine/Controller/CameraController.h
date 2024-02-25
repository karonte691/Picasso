#pragma once

#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <PEngine/Controller/PicassoController.h>
#include <PEngine/EventSystem/PERegistry.h>

namespace Picasso::Engine::Controller
{
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::Events::PEvent;

    class CameraController : public PicassoController
    {
    public:
        CameraController() : PicassoController("CameraController"){};
        bool InitController() override;

    private:
        void _onCameraUpdate(BaseEvent<PEvent> *&event);
    };
}

#endif // CAMERA_CONTROLLER_H