#pragma once
#include "GameState.h"
#include "MenuButton.h"

class MenuState : public State {
public:
	MenuState(sf::RenderWindow& window, StateManager& manager);


	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

private:
	void ResizeView(const sf::RenderWindow& window, sf::View& view);

private:
	StateManager& manager;
	sf::RenderWindow& window;

	sf::View view;
	const float VIEW_HEIGHT = 1024.f;

	sf::Sprite background;

	sf::Vector2i mousePos;
	sf::Vector2f cursorPos;

	MenuButton GameButton;
	MenuButton EditorButton;
};