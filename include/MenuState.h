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
	TextureManager textures;

	sf::View view;
	const float VIEW_HEIGHT = 596.f;

	sf::RectangleShape background;

	sf::Vector2i mousePos;
	sf::Vector2f cursorPos;

	sf::Vector2f backgroundSize = sf::Vector2f(843.f, 596.f);
	sf::IntRect defRect;

	std::unordered_map<std::string, MenuButton> buttons;
};