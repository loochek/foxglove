#pragma once

#include <typeindex>
#include <vector>
#include <unordered_map>

namespace foxglove::core {
    class IEventListenerBase {};

    template<typename EventType>
    class IEventListener : public IEventListenerBase {
    public:
        virtual void OnEvent(const EventType& event) = 0;
    };

    template<typename... EventTypes>
    class IEventsListener : public IEventListener<EventTypes>... {};

    class EventBus {
    public:
        template<typename EventType>
        void Subscribe(IEventListener<EventType>* instance) {
            handlers_[typeid(EventType)].push_back(instance);
        }
        
        template<typename EventType>
        void Emit(const EventType& event) {
            for (IEventListenerBase* handler : handlers_[typeid(EventType)]) {
                static_cast<IEventListener<EventType>*>(handler)->OnEvent(event);
            }
        }

    private:
        // Note that different events can be handled by one class thanks to multiple inheritance. 
        // (so pointers to different IEventListener<EventType> subclasses of one class instance
        // can be present simultaneusly and it's not a case of virtual inheritance).
        std::unordered_map<std::type_index, std::vector<IEventListenerBase*>> handlers_;
    };
}
