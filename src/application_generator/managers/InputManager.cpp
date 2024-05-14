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

void InputManager::handle(sf::Event& event)
{

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
		else if (event.type == sf::Event::MouseMoved)
        {
			notify("MouseMoved");
		}

        else if (event.type == sf::Event::KeyPressed)
        {
			if (event.key.code == sf::Keyboard::A)
				notify("A_KeyPressed");

            if (event.key.code == sf::Keyboard::Z)
                notify("Z_KeyPressed");

			if (event.key.code == sf::Keyboard::Q)
                notify("Q_KeyPressed");

            if (event.key.code == sf::Keyboard::S)
				notify("S_KeyPressed");

			if (event.key.code == sf::Keyboard::D)
				notify("D_KeyPressed");

			if (event.key.code == sf::Keyboard::Space)
				notify("Space_KeyPressed");

			if (event.key.code == sf::Keyboard::LShift)
				notify("LShift_KeyPressed");
        }   
}