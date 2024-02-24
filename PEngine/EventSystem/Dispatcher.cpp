#include <PEngine/EventSystem/Dispatcher.h>

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;
    using Events::PEventData;

    Dispatcher *Dispatcher::Instance = nullptr;

    Dispatcher::Dispatcher()
    {
        m_eventFactory = std::make_unique<EventFactory>();
    }

    void Dispatcher::Subscribe(const PEvent &eventName, SlotType &&slot)
    {
        m_listeners[eventName].push_back(slot);
    }

    void Dispatcher::Post(const PEvent eventType) const
    {
        BaseEvent<PEvent> *event = m_eventFactory->GetEvent(eventType);

        if (!event)
        {
            Picasso::Engine::Logger::Logger::Fatal("Error while trying to factor event");
            return;
        }

        PEvent type = event->type();

        if (m_listeners.find(type) == m_listeners.end())
        {
            delete event;
            return;
        }

        auto &&observers = m_listeners.at(type);

        for (auto &&observer : observers)
        {
            observer(event);

            if (event->IsHandled())
            {
                break;
            }
        }

        delete event;
    }

    void Dispatcher::Post(const PEvent eventType, PEventData eventData) const
    {
        BaseEvent<PEvent> *event = m_eventFactory->GetEvent(eventType);

        if (!event)
        {
            Picasso::Engine::Logger::Logger::Fatal("Error while trying to factor event");
            return;
        }

        event->SetData(eventData);

        PEvent type = event->type();

        if (m_listeners.find(type) == m_listeners.end())
        {
            if (event != nullptr)
            {
                delete event;
            }
            return;
        }

        auto &&observers = m_listeners.at(type);

        for (auto &&observer : observers)
        {
            observer(event);

            if (event->IsHandled())
            {
                break;
            }
        }

        delete event;
    }
}