#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Player.h"

class GameUI {
public:
	GameUI(const sf::View& view, const Player& player);

	void update(float deltaTime);

	void Draw(sf::RenderWindow& window);

private:
	const sf::View& view;
	const Player& player;

	std::map<std::string, sf::RectangleShape> shapes;
};