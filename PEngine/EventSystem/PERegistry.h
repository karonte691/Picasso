#pragma once

#ifndef PICASSO_REGISTRY_H
#define PICASSO_REGISTRY_H

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>
#include <PEngine/EventSystem/Dispatcher.h>

#include <vector>
#include <unordered_map>
#include <sstream>
#include <iomanip>

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;
    using Events::PEventData;

    /**
     * @brief The PicassoRegistry class provides a registry for event handling in the Picasso Engine.
     *
     * The registry allows subscribing to events, dispatching events, and unsubscribing from events.
     */
    class PicassoRegistry
    {
    public:
        /**
         * @brief Initializes the PicassoRegistry by creating a new Dispatcher instance.
         */
        static void Init()
        {
            Dispatcher::Instance = new Dispatcher();
        }

        /**
         * @brief Dispatches an event to be processed by the registered event handlers.
         *
         * @param event The event to be dispatched.
         */
        static void Dispatch(PEvent event)
        {
            Dispatcher::Instance->Post(event);
        }

        /**
         * @brief Dispatches an event with additional event data to be processed by the registered event handlers.
         *
         * @param event The event to be dispatched.
         * @param eventData The additional event data associated with the event.
         */
        static void Dispatch(PEvent event, PEventData eventData)
        {
            Dispatcher::Instance->Post(event, eventData);
        }

        /**
         * @brief Subscribes an instance to an event with a specified event name and slot.
         *
         * @tparam T The type of the instance.
         * @param instance The instance to be subscribed.
         * @param eventName The name of the event to subscribe to.
         * @param slot The slot (event handler) to be called when the event is dispatched.
         */
        template <typename T>
        static void Subscribe(T *instance, const PEvent &eventName, SlotType &&slot)
        {
            std::string key = _GetRegistryKey(instance, eventName);
            std::size_t slotId = Dispatcher::Instance->Subscribe(eventName, std::move(slot));
            m_slotIdsMap[key].push_back(slotId);
        }

        /**
         * @brief Unsubscribes an instance from an event with a specified event name.
         *
         * @tparam T The type of the instance.
         * @param instance The instance to be unsubscribed.
         * @param eventName The name of the event to unsubscribe from.
         */
        template <typename T>
        static void Unsubscribe(T *instance, const PEvent &eventName)
        {
            std::string key = _GetRegistryKey(instance, eventName);
            if (m_slotIdsMap.find(key) != m_slotIdsMap.end())
            {
                for (auto &slotId : m_slotIdsMap[key])
                {
                    Dispatcher::Instance->Unsubscribe(eventName, slotId);
                }
                m_slotIdsMap.erase(key);
            }
        }

        /**
         * @brief Resets the PicassoRegistry by deleting the Dispatcher instance.
         */
        static void Reset()
        {
            delete Dispatcher::Instance;
            Dispatcher::Instance = nullptr;
        }

    private:
        static std::unordered_map<std::string, std::vector<std::size_t>> m_slotIdsMap;

        /**
         * @brief Generates a unique registry key for an instance and event name combination.
         *
         * @tparam T The type of the instance.
         * @param instance The instance for which the key is generated.
         * @param eventName The name of the event.
         * @return The generated registry key.
         */
        template <typename T>
        static std::string _GetRegistryKey(T *instance, const PEvent &eventName)
        {
            std::ostringstream oss;
            std::hash<std::string> hasher;
            auto eventNameStr = _PEventToString(eventName);
            auto eventNameHash = hasher(eventNameStr);
            oss << typeid(T).name() << "@" << std::hex << reinterpret_cast<uintptr_t>(instance) << "#" << eventNameHash;
            return oss.str();
        }

        std::string _PEventToString(PEvent event)
        {
            switch (event)
            {
            case PEvent::APPLICATION_QUIT:
                return "APPLICATION_QUIT";
            case PEvent::RESIZED:
                return "RESIZED";
            case PEvent::PLATFORM_EXPOSE:
                return "PLATFORM_EXPOSE";
            case PEvent::CAMERA_UPDATE_VIEW:
                return "CAMERA_UPDATE_VIEW";
            case PEvent::CAMERA_UPDATE_POSITION:
                return "CAMERA_UPDATE_POSITION";
            case PEvent::RENDERER_UPDATE:
                return "RENDERER_UPDATE";
            case PEvent::KEY_PRESSED:
                return "KEY_PRESSED";
            case PEvent::KEY_RELEASED:
                return "KEY_RELEASED";
            case PEvent::BUTTON_PRESSED:
                return "BUTTON_PRESSED";
            case PEvent::BUTTON_RELEASED:
                return "BUTTON_RELEASED";
            case PEvent::MOUSE_MOVED:
                return "MOUSE_MOVED";
            case PEvent::MOUSE_WHEEL:
                return "MOUSE_WHEEL";
            case PEvent::CONTROLLER_MOVEMENT:
                return "CONTROLLER_MOVEMENT";
            case PEvent::CONTROLLER_SCALE:
                return "CONTROLLER_SCALE";
            default:
                return "UNKNOWN_EVENT";
            }
        }
    };
}
#endif