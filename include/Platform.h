#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include <string>

class Platform
{
public:
	Platform(sf::Vector2f size, sf::Vector2f position);
	Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture);
	Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, const sf::IntRect& uvRect);
	Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, const sf::IntRect& uvRect, const std::string& platfomTexture);

	void Draw(sf::RenderWindow& window) { window.draw(body); }
	void SetColor(sf::Color& color) { body.setFillColor(color); }
	void SetPosition(sf::Vector2f& position) { body.setPosition(position); }
	void SetSize(sf::Vector2f& size) { body.setSize(size); body.setOrigin(size / 2.f); }
	void SetTextureRect(const sf::IntRect& rect) { body.setTextureRect(rect); }
	void SetTileName(const std::string& tile) { platformTexture = tile; }

	Collision GetCollider() { return Collision(body); }
	sf::Vector2f GetPosition() const { return body.getPosition(); }
	sf::Vector2f GetSize() const { return body.getSize(); }
	std::string GetTexture() const { return platformTexture; }
	sf::IntRect GetUvRect() const { return uvRect; }
	sf::FloatRect GetGlobalBounds() const { return body.getGlobalBounds(); }

public:
	bool canHaveEnemy = false;
	bool hasEnemy = false;

private:
	sf::RectangleShape body;
	std::string platformTexture;
	sf::IntRect uvRect;

};
