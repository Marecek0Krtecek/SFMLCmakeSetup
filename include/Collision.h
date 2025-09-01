#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
public:
	Collision(sf::RectangleShape& body);

	bool CheckCollision(Collision& other, sf::Vector2f& direction, float weight);

	void Move(float dx, float dy) { body.move(dx, dy); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.f; }

private:
	sf::RectangleShape& body;
};
