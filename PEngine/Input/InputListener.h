#pragma once

#ifndef INPUT_LISTENER_H
#define INPUT_LISTENER_H

#include <PEngine/EventSystem/PERegistry.h>

namespace Picasso::Engine::Input
{
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::Events::PEvent;
    using Picasso::Engine::EventSystem::Events::PEventData;

    class InputListener
    {
    public:
        void Init();

    private:
        void _ProcessInput(BaseEvent<PEvent> *&event);

        void _ProcessKeyInput(PEventData &eData, bool pressed);
    };
}
#endif // INPUT_LISTENER_H