#pragma once

#include "src/Core/Component.h"
#include <vector>

class ComponentList
{
public:
	ComponentList()
	{
	}

	~ComponentList()
	{
		for (auto component : m_Components)
			delete component;
	}

	void AddComponent(Component* component /*new Component*/)
	{
		m_Components.push_back(component);
	}

	std::vector<Component*>::iterator begin() { return m_Components.begin(); }
	std::vector<Component*>::iterator end() { return m_Components.end(); }
	std::vector<Component*>::reverse_iterator rbegin() { return m_Components.rbegin(); }
	std::vector<Component*>::reverse_iterator rend() { return m_Components.rend(); }

private:
	std::vector<Component*> m_Components;

};
