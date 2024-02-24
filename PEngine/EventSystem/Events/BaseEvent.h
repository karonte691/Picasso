#pragma once

#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include <string>
#include <PEngine/EventSystem/Events/EventTypes.h>

namespace Picasso::Engine::EventSystem::Events
{
    template <typename T>
    class BaseEvent
    {
    public:
        BaseEvent() = default;
        BaseEvent(T type, const std::string &name = "") : m_type(type), m_eventName(name){};
        virtual ~BaseEvent() = default;

        inline const T type() const { return m_type; };
        inline const std::string GetEventName() const { return m_eventName; }
        inline const bool IsHandled() const { return m_isHandled; }
        inline const PEventData GetData() const { return m_data; }

        void SetData(PEventData data) { m_data = data; }

    protected:
        T m_type;
        std::string m_eventName;
        bool m_isHandled = false;
        PEventData m_data;
    };

    struct BaseEventComparator
    {
        bool operator()(const BaseEvent<PEvent> &lhs, const BaseEvent<PEvent> &rhs) const
        {
            return lhs.type() < rhs.type();
        }
    };

}

#endif