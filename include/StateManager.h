#pragma once
#include "State.h"
#include <memory>

class StateManager
{
public:
	StateManager() = default;

	template <typename T, typename... Args>
	void changeState(Args&&... args) {
		currentState = std::make_unique<T>(std::forward<Args>(args)...);
	}

	void handleEvent(const sf::Event& event, sf::RenderWindow& window);
	void update(float deltaTime);
	void render(sf::RenderWindow& window);

private:
	std::unique_ptr<State> currentState;
};