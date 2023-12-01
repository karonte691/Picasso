#pragma once

#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H

#include <memory>

#include "Events/BaseEvent.h"
#include "Events/EventTypes.h"

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;

    class EventFactory
    {
        public:
            std::shared_ptr<BaseEvent<PEvent>> GetEvent(PEvent event);
    };
}

#endif