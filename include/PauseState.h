#pragma once
#include "MenuState.h"
#include "MenuButton.h"

class PauseState : public State
{
public:
	PauseState(sf::RenderWindow& window, StateManager& manager);
	~PauseState() = default;

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

private:
	void ResizeView(const sf::RenderWindow& window, sf::View& view);

private:
	StateManager& stateManager;
	sf::RenderWindow& window;

	const float VIEW_HEIGHT = 1024.f;

	TextureManager textures;

	std::unordered_map<std::string, MenuButton> buttons;

	sf::RectangleShape background;
};