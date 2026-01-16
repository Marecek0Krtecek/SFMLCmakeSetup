#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Checkpoint
{
public:
	Checkpoint() {};
	Checkpoint(sf::Vector2f position, const std::string& name);
	~Checkpoint() = default;

	void Draw(sf::RenderWindow& window) { window.draw(point); }

	void SetPosition(const sf::Vector2f& position) { point.setPosition(position.x - point.getRadius(), position.y - point.getRadius()); }
	void SetName(std::string name) { this->name = name; }

	const sf::Vector2f GetPosition() const { return sf::Vector2f(point.getPosition().x + point.getRadius(), point.getPosition().y + point.getRadius()); }
	const std::string GetName() const { return name; }
	const sf::FloatRect GetGlobalBounds() const { return point.getGlobalBounds(); }

private:
	std::string name;
	sf::CircleShape point;
};