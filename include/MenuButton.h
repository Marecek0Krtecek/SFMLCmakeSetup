#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MenuButton
{
public:
	MenuButton() = default;
	MenuButton(sf::Vector2f pos, sf::Vector2f size, sf::Color backgroundColor);
	MenuButton(sf::Vector2f pos, sf::Vector2f size, sf::Texture* texture, sf::IntRect textureRect = sf::IntRect());
	~MenuButton() = default;

	bool Update(sf::Vector2f cursorPos);

	void Hower(sf::Color color = sf::Color(50, 50, 50, 127));
	void Hower(sf::IntRect hoverTextureRect);

	void Draw(sf::RenderWindow& window) const { window.draw(body); }

	sf::IntRect GetUvRect() const { return uvRect; }

private:
	sf::RectangleShape body;

	sf::Color defaultColor = sf::Color::Transparent;
	sf::IntRect uvRect;
};