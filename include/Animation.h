#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	//~Animation();

	void Update(int row, float deltaTime, bool faceRight, unsigned int amount);

	sf::Vector2u GetImageCount() { return imageCount; }
	sf::Vector2u GetCurrentImageValue() { return currentImage; }
	float GetSwitchTime() { return switchTime; }

public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime = 0;
	float switchTime = 0;
};
