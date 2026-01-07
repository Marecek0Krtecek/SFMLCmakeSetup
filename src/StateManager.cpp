#include "StateManager.h"

void StateManager::handleEvent(const sf::Event& event, sf::RenderWindow& winodw) {
	if (activeStates[activeStates.size() - 1]) activeStates[activeStates.size() - 1]->handleEvent(event, winodw);
}

void StateManager::update(float deltaTime) {
	if (activeStates[activeStates.size() - 1]) activeStates[activeStates.size() - 1]->update(deltaTime);
}

void StateManager::render(sf::RenderWindow& window) {
	for (auto& state : activeStates) {
		if (state) state->render(window);
	}
}