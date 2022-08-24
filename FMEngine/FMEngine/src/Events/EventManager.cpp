#include "src/Events/EventManager.h"

void EventManager::ProcessEvents()
{
	RemoveInactiveListners();
	// loop through events
	for (auto event : m_EventArray)
	{
		// find iterator to first matching listener
		auto it = m_ListenersMap.find(event->GetType());
		// iterating through all mathing listeners
		for (int i = 0; i < m_ListenersMap.count(event->GetType()); i++)
		{	
			// processing event on mathing listener
			it->second->ProcessEvent(*event);
			it++;
		}
	}
	ClearEventArray();
}

void EventManager::PushEvent(Event *event)
{
	m_EventArray.push_back(event);
}

void EventManager::ClearEventArray()
{	
	for (Event* event : m_EventArray)
		delete event;
	m_EventArray.clear();
}

void EventManager::AddListener(EventType evetype, std::shared_ptr<EventListener> listener )
{
	m_ListenersMap.emplace(evetype, listener);
}

void EventManager::RemoveInactiveListners()
{
	for (auto it = m_ListenersMap.begin(); it != m_ListenersMap.end(); it++)
	{
		if (!it->second->IsActive())
			m_ListenersMap.erase(it);
	}
}

EventManager::~EventManager()
{
	ClearEventArray();
}
