#include "TerrainGeneration.h"

TerrainGeneration::TerrainGeneration(sf::Texture* platformTexture, sf::Vector2u imageCount) {
	this->platformTexture = platformTexture;
	this->imageCount = imageCount;
	uvRect.width = this->platformTexture->getSize().x / float(imageCount.x);
	uvRect.height = this->platformTexture->getSize().y / float(imageCount.y);
}

TerrainGeneration::TerrainGeneration(sf::Vector2f start, sf::Vector2f end) {
	GeneratedPlatformsRandom(start, end);
}

void TerrainGeneration::GeneratedPlatformsRandom(sf::Vector2f start, sf::Vector2f end) {
	for (float x = (start.x / platformSize.x); x <= (end.x / platformSize.x); x++) {
		for (float y = (start.y / platformSize.y); y <= (end.y / platformSize.y); y++) {
			if(rand()%3 == 2)
				platforms.push_back(CreatePlatform(x, y));
		}
	}
}

void TerrainGeneration::GeneratedPlatformsSinus(sf::Vector2f start, sf::Vector2f end) {
	for (float x = start.x; x <= end.x; x++) {
		float y = sin(x) * 20;
		
		platforms.push_back(CreatePlatform(x, y));
	}
}

void TerrainGeneration::AddPlatform(Platform platform) {
	platforms.push_back(platform);
}

Platform TerrainGeneration::CreatePlatform(float x, float y) {
	y *= platformSize.y;
	if (y >= 300.f)
		row = 4;
	else if (y <= -300.f)
		row = 6;
	else
		row = 0;

	uvRect.top = row * uvRect.height;

	return Platform(platformSize, sf::Vector2f(platformSize.x * x, y), platformTexture, uvRect);
}