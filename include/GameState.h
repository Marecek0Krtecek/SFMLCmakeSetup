#pragma once
#include "State.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "TerrainGeneration.h"

class GameState : public State
{
public:
	GameState(sf::RenderWindow& window);

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

private:
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	void RestartGame(Player& player, Background& background, std::vector<Enemy>& enemies);
	void SpawnEnemy(std::vector<Enemy>& enemies, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);

private:
	const float VIEW_HEIGHT = 1024.f;

	sf::View view;

	//Textures
	TextureManager textures;
	std::string playerTexture = "brackeys_platformer_assets/sprites/knight.png";
	std::string platfomrTexture = "brackeys_platformer_assets/sprites/platforms.png";
	std::string backgroundTexture = "Glacial-mountains-parallax-background_vnitti/background_glacial_mountains.png";
	std::string enemyTexture = "brackeys_platformer_assets/sprites/slime_green.png";

	//Player
	Player player;

	//Enemies
	std::vector<Enemy> enemies;

	//Background
	Background background;

	//Terrain Generation
	TerrainGeneration terrainGeneration;

};
