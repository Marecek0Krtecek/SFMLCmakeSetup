#pragma once
#include "State.h"
#include <memory>

class StateManager
{
public:
	StateManager() = default;

	template <typename T, typename... Args>
	void changeState(Args&&... args) {
		activeStates.clear();
		activeStates.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		//currentState = std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename... Args>
	void addState(Args&&... args) {
		activeStates.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}

	void popState() { activeStates.pop_back(); }

	void handleEvent(const sf::Event& event, sf::RenderWindow& window);
	void update(float deltaTime);
	void render(sf::RenderWindow& window);

private:
	std::vector<std::unique_ptr<State>> activeStates;
	//std::unique_ptr<State> currentState;
};