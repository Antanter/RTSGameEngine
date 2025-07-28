#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>

class Event {
    public:
    virtual ~Event() = default;
};

class EventBus {
    private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const Event&)>>> subscribers;

    public:
    template<typename EventType>
    void Subscribe(std::function<void(const EventType&)> callback);

    template<typename EventType>
    void Publish(const EventType& event);
};

class CollisionEvent : public Event {
    public:
    size_t entityA;
    size_t entityB;
};
    