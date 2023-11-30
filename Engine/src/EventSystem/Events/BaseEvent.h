#pragma once

#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include <string>

#include "EventTypes.h"

namespace Picasso::Engine::EventSystem::Events
{
    template<typename T>
    class BaseEvent
    {
    public:
        BaseEvent() = default;
        BaseEvent(T type, const std::string& name = "") : m_type(type), m_eventName(name){};

        inline const T type() const { return m_type;};
        inline const bool IsHandled() const { return m_isHandled; }
    protected:
        T m_type;
        std::string m_eventName;
        bool m_isHandled = false;
    };

    struct BaseEventComparator {
        bool operator()(const BaseEvent<PEvent>& lhs, const BaseEvent<PEvent>& rhs) const {
            return lhs.type() < rhs.type();
        }
    };
    
}

#endif