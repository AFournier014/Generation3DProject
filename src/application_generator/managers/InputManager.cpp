#include "managers/InputManager.h"

#include <SFML/Window/Event.hpp>

InputManager::InputManager() = default;

void InputManager::subscribe(const EventID& id, std::shared_ptr<EventSubscriber> subscriber)
{
	m_hashSubscribers[id].push_back(subscriber);
}

void InputManager::unsubscribe(const EventID& id, std::shared_ptr<EventSubscriber> subscriber)
{
    auto& subscribers = m_hashSubscribers[id];
    std::erase(subscribers, subscriber);
}

void InputManager::notify(const EventID& id)
{
    if (m_hashSubscribers.contains(id))
	{
		for (auto& subscriber : m_hashSubscribers[id])
		{
			subscriber->on_notify(EventBase(id));
		}
	}
}

void InputManager::update()
{
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window->close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                notify("LeftClick");
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                notify("RightClick");
            }
            
        }
    }
}