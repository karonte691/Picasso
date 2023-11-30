#pragma once

#ifndef PICASSO_REGISTRY_H
#define PICASSO_REGISTRY_H

#include "Events/BaseEvent.h"
#include "Events/EventTypes.h"
#include "Dispatcher.h"

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;

    class PicassoRegistry
    {
        public:
            static void Init()
            {
                Dispatcher::Instance = new Dispatcher();
            }
            static void Dispatch(PEvent event)
            {
                Dispatcher::Instance->Post(event);
            }
            static void Reset()
            {
                Dispatcher::Instance = nullptr;
            }
    };
}
#endif