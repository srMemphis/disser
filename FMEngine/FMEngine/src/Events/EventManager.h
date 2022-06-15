#pragma once
#include "src/Events/Event.h"

#include <vector>
#include <map>
#include <functional>
#include <memory>

class EventListener;
class EventManager
{
public:

    static EventManager& GetInstance()
    {
        static EventManager instance;
        return instance;
    }

    void PushEvent(Event* /*owns event*/);
    void ProcessEvents();
    
    void AddListener(EventType, std::shared_ptr<EventListener>);

private:
	EventManager() {}
	~EventManager();
    EventManager(const EventManager&) = delete;
    EventManager& operator=(EventManager&) = delete;

    void RemoveInactiveListners();
    void ClearEventArray();

	std::vector<Event*> m_EventArray;
    std::multimap<EventType, std::shared_ptr<EventListener>> m_ListenersMap;
};


class EventListener
{
public:
    EventListener(std::function<void(Event&)> oneventfunc)
        : OnEventFunction(oneventfunc) {}
    ~EventListener() { m_Active = false; }

    bool IsActive() { return m_Active; }
    void SetActive(bool active) { m_Active = active; }
    void ProcessEvent(Event& event) { OnEventFunction(event); };

private:
    std::function<void(Event&)> OnEventFunction;
    bool m_Active = true;
};
