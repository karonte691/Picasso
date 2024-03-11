#pragma once

#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <PEngine/Controller/PicassoController.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Input/InputState.h>
#include <PEngine/Camera/Camera.h>

#include <memory>
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
        void Update() override;
        void Destroy();

    private:
        unsigned int m_PrevX;
        unsigned int m_PrevY;

        void _OnCameraUpdateView(BaseEvent<PEvent> *&event);
        void _OnCameraUpdatePosition(BaseEvent<PEvent> *&event);
    };
}

#endif // CAMERA_CONTROLLER_H