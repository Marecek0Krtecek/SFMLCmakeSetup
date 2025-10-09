#include "StateManager.h"

void StateManager::handleEvent(const sf::Event& event, sf::RenderWindow& winodw) {
	if (currentState) currentState->handleEvent(event, winodw);
}

void StateManager::update(float deltaTime) {
	if (currentState) currentState->update(deltaTime);
}

void StateManager::render(sf::RenderWindow& window) {
	if (currentState) currentState->render(window);
}