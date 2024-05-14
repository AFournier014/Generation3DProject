#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "events/Events.h"

class InputManager : public EventPublisher
{
public:
    InputManager();

	void subscribe(const EventID& id, std::shared_ptr<EventSubscriber> subscriber) override;
	void unsubscribe(const EventID& id, std::shared_ptr<EventSubscriber> subscriber) override;
    void notify(const EventID& id) override;
    void update();

private:
    std::shared_ptr<sf::RenderWindow> m_window;
};

#endif // INPUT_MANAGER_H
