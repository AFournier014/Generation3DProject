#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using EventID = std::string;

struct EventBase
{
    explicit EventBase(const EventID& _id)
        : id(_id)
    {}


    virtual ~EventBase() = default;

    EventID id;
};

class EventSubscriber
{
public:
    using callback = std::function<void()>;

    EventSubscriber() = default;
    virtual ~EventSubscriber() = default;
    virtual void on_notify(const EventBase& _eventB) = 0;
    void subscribe(callback const& callback) { m_callbacks.push_back(callback); }

protected:
    std::vector<callback> m_callbacks;
};

class EventPublisher
{
public:
    virtual ~EventPublisher() = default;
	virtual void subscribe(const EventID& id, std::shared_ptr<EventSubscriber> subscriber) = 0;
	virtual void unsubscribe(const EventID& id, std::shared_ptr<EventSubscriber> subscriber) = 0;
    virtual void notify(const EventID& id) = 0;

protected:
	std::unordered_map<EventID, std::vector<std::shared_ptr<EventSubscriber>>> m_hashSubscribers;
};

#endif // EVENTS_H
