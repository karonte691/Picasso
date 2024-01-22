#pragma once

#ifndef PICASSO_REGISTRY_H
#define PICASSO_REGISTRY_H

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>
#include <PEngine/EventSystem/Dispatcher.h>

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;
    using Events::PEventData;

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
        static void Dispatch(PEvent event, PEventData eventData)
        {
            Dispatcher::Instance->Post(event, eventData);
        }
        static void Reset()
        {
            Dispatcher::Instance = nullptr;
        }
    };
}
#endif