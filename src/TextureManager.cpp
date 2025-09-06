#include "TextureManager.h"

sf::Texture& TextureManager::get(const std::string& fileName) {
	if (textures.find(fileName) == textures.end()) {
		sf::Texture tex;
		if (!tex.loadFromFile(RESOURCES_PATH + fileName))
			throw std::runtime_error("Failed to load texture: " + fileName);

		textures[fileName] = std::move(tex);	
	}

	return textures[fileName];
}