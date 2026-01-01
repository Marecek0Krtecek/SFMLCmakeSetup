#pragma once
#include "EditorState.h"
#include "Player.h"

class GameState : public State
{
public:
	GameState(sf::RenderWindow& window, StateManager& manager);

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

private:
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	void RestartGame(Player& player, std::vector<Enemy>& enemies);
	void SpawnEnemy(std::vector<Enemy>& enemies, const EnemySpawnPoint& spawnPoint, int SPID);

private:
	//State references
	StateManager& stateManager;

	//Game variables
	const float VIEW_HEIGHT = 1024.f;

	sf::View view;

	//Textures
	TextureManager textures;
	TileManager tiles;
	std::string playerTexture = "sprites_piskel_file/knight_1.png";
	std::string platfomrTexture = "brackeys_platformer_assets/sprites/platforms.png";
	std::string backgroundTexture = "Glacial-mountains-parallax-background_vnitti/background_glacial_mountains.png";
	std::string enemyTexture = "brackeys_platformer_assets/sprites/slime_green.png";

	//Player
	Player player;
	std::unordered_map<std::string, Checkpoint> checkpoints;

	//Enemies
	EnemyManager enemyManager;
	std::vector<EnemySpawnPoint> enemySpawnPoints;
	std::vector<Enemy> enemies;

	//Platforms
	std::vector<Platform> platforms;

	//Background
	std::vector<Background> backgrounds;

};
