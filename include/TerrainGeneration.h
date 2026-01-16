#pragma once
#include <SFML/Graphics.hpp>
#include <Platform.h>
#include <vector>
class TerrainGeneration
{
public:
	TerrainGeneration(sf::Texture* platformTexture, sf::Vector2u imageCount);
	TerrainGeneration(sf::Vector2f start, sf::Vector2f end);

	void GeneratedPlatformsRandom(sf::Vector2f start, sf::Vector2f end);
	void GeneratedPlatformsSinus(sf::Vector2f start, sf::Vector2f end);
	void AddPlatform(Platform platform);

	sf::Vector2f GetStandardPlatformSize() { return platformSize; }

public:
	std::vector<Platform> platforms;

private:
	Platform CreatePlatform(float x, float y);
private:
	sf::Vector2f platformSize = { 100.f, 50.f };
	sf::Texture* platformTexture = nullptr;
	sf::Vector2u imageCount;
	unsigned int row = 0;
	sf::IntRect uvRect;
}
;
