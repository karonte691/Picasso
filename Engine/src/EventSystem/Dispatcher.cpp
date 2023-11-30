#include "Dispatcher.h"

namespace Picasso::Engine::EventSystem
{
    using Events::PEvent;
    using Events::BaseEvent;

    Dispatcher* Dispatcher::Instance = nullptr;

    Dispatcher::Dispatcher()
    {
        m_eventFactory = std::make_unique<EventFactory>();
    }

    void Dispatcher::Subscribe(const PEvent& eventName, SlotType&& slot)
    {
        m_listeners[eventName].push_back(slot);   
    }

    void Dispatcher::Post(const PEvent eventType) const
    {
        std::shared_ptr<BaseEvent<PEvent>> event = m_eventFactory->GetEvent(eventType);
        
        if(event == nullptr){
            Picasso::Logger::Logger::Fatal("Error while trying to factor event");
            return;
        }

        PEvent type = event->type();

        if(m_listeners.find(type) == m_listeners.end()){
                return;
        }

        auto&& observers = m_listeners.at(type);

        for( auto&& observer : observers ){
            observer(event);

            if(event->IsHandled())
            {
                break;
            }
        }
    }
}