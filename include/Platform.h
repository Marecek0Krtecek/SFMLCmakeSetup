#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"

class Platform
{
public:
	Platform(sf::Vector2f size, sf::Vector2f position);
	Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture);
	Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::IntRect& uvRect);

	void Draw(sf::RenderWindow& window) { window.draw(body); }
	void SetColor(sf::Color color) { body.setFillColor(color); }

	Collision GetCollider() { return Collision(body); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetSize() { return body.getSize(); }

public:
	bool canHaveEnemy = false;
	bool hasEnemy = false;

private:
	sf::RectangleShape body;
};
