#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include <vector>
#include <iostream>
#include "TerrainGeneration.h"
#include "Animation.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Background.h"
#include "Enemy.h"
#include <fstream>
#include "Serializer.h"
#include "json.hpp"
#include "TextureManager.h"

using json = nlohmann::json;

const float VIEW_HEIGHT = 1024.f;

void ResizeView(const sf::RenderWindow& window, sf::View& view) 
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void RestartGame(Player& player, Background& background, std::vector<Enemy>& enemies) {
	player.Restrart();
	background.Restart();
	enemies.erase(enemies.begin(), enemies.end());
}

void SpawnEnemy(std::vector<Enemy>& enemies, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) {
	enemies.push_back(Enemy(texture, imageCount, switchTime, speed, position));
}

int main() 
{

#pragma region Testing


	//std::ofstream file(RESOURCES_PATH "level.json");

	//file << Serializer::toJSON(Platform(sf::Vector2f(50.f, 100.f), sf::Vector2f(0.f, 100.f))).dump(4);

	//file.close();

	//std::ifstream read(RESOURCES_PATH "level.json");

	//static json j;
	//read >> j;

	//std::ofstream file(RESOURCES_PATH "test.json");

	//json j;
	//j["Hello"] = "World";

	//file << j.dump(4);

	//file.close();

	//j = {};

	//std::ifstream read(RESOURCES_PATH "test.json");
	//read >> j;

	//std::cout << j["Hello"] << '\n';

#pragma endregion


#pragma region SetupStuf

	sf::RenderWindow window(sf::VideoMode(1080, 720), "myGame", sf::Style::Default);

	window.setFramerateLimit(60);
	
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	ResizeView(window, view);

	ImGui::SFML::Init(window);

#pragma region Textures and sprites

	TextureManager textures;

	//sf::Texture playerTexture;
	//if (!playerTexture.loadFromFile(RESOURCES_PATH "brackeys_platformer_assets/sprites/knight.png"))
	//	std::cout << "playerTexture not loaded\n";
	std::string playerTexture = "brackeys_platformer_assets/sprites/knight.png";

	//sf::Texture platfomrTexture;
	//if (!platfomrTexture.loadFromFile(RESOURCES_PATH "brackeys_platformer_assets/sprites/platforms.png"))
	//	std::cout << "platfomrTexture not loaded\n";
	std::string platfomrTexture = "brackeys_platformer_assets/sprites/platforms.png";

	//sf::Texture backgroungTexture;
	//if (!backgroungTexture.loadFromFile(RESOURCES_PATH "Glacial-mountains-parallax-background_vnitti/background_glacial_mountains.png"))
	//	std::cout << "backgroungTexture not loaded\n";
	std::string backgroundTexture = "Glacial-mountains-parallax-background_vnitti/background_glacial_mountains.png";

	//sf::Texture enemyTexture;
	//if (!enemyTexture.loadFromFile(RESOURCES_PATH "brackeys_platformer_assets/sprites/slime_green.png"))
	//	std::cout << "enemyTexture not loaded\n";
	std::string enemyTexture = "brackeys_platformer_assets/sprites/slime_green.png";

#pragma endregion

	Player player(&textures.get(playerTexture), sf::Vector2u(8, 8), 0.1f, 500.f, 200.f);
	//Player player(&playerTexture, sf::Vector2u(8, 8), 0.1f, 500.f, 200.f);
	player.setScale(sf::Vector2f(2.f, 2.f));
	//player.setPosition(0.f, -1050.f);

	std::vector<Enemy> enemies;
	enemies.reserve(10);

	float deltaTime = 0;
	sf::Clock clock;

	Background background(&textures.get(backgroundTexture));
	//Background background(&backgroungTexture);
	background.SetPosition(0.f, 0.f);
	background.SetScale(sf::Vector2f(15.f, 15.f));
	background.parlaxStrength = 0.5f;

	TerrainGeneration terrainGeneration(&textures.get(platfomrTexture), sf::Vector2u(4, 8));
	//TerrainGeneration terrainGeneration(&platfomrTexture, sf::Vector2u(4, 8));
	terrainGeneration.platforms.reserve(5002);
	
	//terrainGeneration.AddPlatform(Platform(sf::Vector2f(1000.f, 50.f), sf::Vector2f(100.f, -1000.f)));

	terrainGeneration.GeneratedPlatformsSinus(sf::Vector2f(0.f, 0.f), sf::Vector2f(5000.f, 2000.f));

	//std::vector<Platform> platforms;
	//platforms.reserve(3);

	//platforms.push_back(Platform(sf::Vector2f(100.f, 50.f), sf::Vector2f(100.f, -1000.f), &textures.get(platfomrTexture), sf::IntRect(0, 0, textures.get(platfomrTexture).getSize().x / 4, textures.get(platfomrTexture).getSize().y / 8), platfomrTexture));
	//platforms.push_back(Platform(sf::Vector2f(100.f, 50.f), sf::Vector2f(100.f, -1100.f), &textures.get(platfomrTexture), sf::IntRect(0, 0, textures.get(platfomrTexture).getSize().x / 4, textures.get(platfomrTexture).getSize().y / 8), platfomrTexture));
	//platforms.push_back(Platform(sf::Vector2f(100.f, 50.f), sf::Vector2f(100.f, -1200.f), &textures.get(platfomrTexture), sf::IntRect(0, 0, textures.get(platfomrTexture).getSize().x / 4, textures.get(platfomrTexture).getSize().y / 8), platfomrTexture));
	//std::ofstream levelfile(RESOURCES_PATH "level.json");
	//levelfile << Serializer::savePlatforms(platforms).dump(4);
	
	//std::ifstream read(RESOURCES_PATH "level.json");
	//json j;
	//read >> j;
	//Serializer::loadPlatforms(j, platforms, textures);
#pragma endregion

#pragma region ImGui

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.FontGlobalScale = 1.5f;

#pragma endregion

	while (window.isOpen()) {

		deltaTime = clock.restart().asSeconds();

#pragma region poll events

		sf::Event ev;
		while (window.pollEvent(ev)) {

			ImGui::SFML::ProcessEvent(window, ev);

			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}

#pragma endregion

#pragma region updates and colisions



		player.Update(deltaTime);

		for (int i = 0; i < enemies.size(); i++) {
			if (player.GetDistance(enemies[i].getPosition()) <= (view.getSize().x + terrainGeneration.GetStandardPlatformSize().x) / 2.f) {
				enemies[i].Update(deltaTime);
			}
			else {
				if (enemies[i].thisPlatformHasMe != nullptr)
					*enemies[i].thisPlatformHasMe = false;
				enemies.erase(enemies.begin() + i);
				--i;
				continue;
			}

		}

		background.Move(-player.GetVelocity() * background.parlaxStrength * deltaTime);

		///collisions

		sf::Vector2f direction;
		sf::Vector2f enemyDirection;
		for (auto& platform : terrainGeneration.platforms) {
			if (player.GetDistance(platform.GetPosition()) <= view.getSize().x / 1.8f) {
				if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.f)) {
					player.OnCollision(direction);
				}
				if (platform.canHaveEnemy && !platform.hasEnemy) {
					SpawnEnemy(enemies, &textures.get(enemyTexture), sf::Vector2u(4, 3), 0.1f, 250.f, sf::Vector2f(platform.GetPosition().x, platform.GetPosition().y - platform.GetSize().y / 2.f));
					platform.hasEnemy = true;
					enemies[enemies.size() - 1].thisPlatformHasMe = &platform.hasEnemy;
				}
				for (auto& enemy : enemies) {
					if (platform.GetCollider().CheckCollision(enemy.GetCollider(), enemyDirection, 1.f)) {
						enemy.OnCollision(enemyDirection);
						float maxX = platform.GetPosition().x + (platform.GetSize().x / 2.f), minX = platform.GetPosition().x - (platform.GetSize().x / 2.f);
						if (enemy.getPosition().x <= minX || enemy.getPosition().x >= maxX)
							enemy.SetDirection(sf::Vector2f(-1.f, 1.f));
					}

					if (enemy.GetCollider().CheckCollision(player.GetCollider(), sf::Vector2f(), 0.5f)) {
						if (enemy.OnPlayerColision(player)) {
							background.Restart();
						}
					}
				}
			}

		}


#pragma endregion

#pragma region ImGui

#pragma region ImGui update

		ImGui::SFML::Update(window, clock.restart());
		//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

#pragma endregion

	//ImGui::ShowDemoWindow();

		ImGui::Begin("Debug");
		ImGui::Text("FPS: %.1f", 1.f / deltaTime);
		ImGui::Text("Player Velocity (%.1f/%.1f)", player.GetVelocity().x, player.GetVelocity().y);
		ImGui::Text("Player: (%.1f, %.1f)", player.getPosition().x, player.getPosition().y);
		if (ImGui::SliderFloat("Gravity", &player.gravity, 10.f, 500.f))
			for (auto& enemy : enemies)
				enemy.gravity = player.gravity;
		ImGui::Text("Enemies Count: %i", (int)enemies.size());
		if (ImGui::Button("Spawn Enemy"))
			SpawnEnemy(enemies, &textures.get(enemyTexture), sf::Vector2u(4, 3), 0.1f, 250.f, player.getPosition());
		if (ImGui::Button("Restart Game"))
			RestartGame(player, background, enemies);
		if (ImGui::Button("Stop Game")) {
			window.close();
			break;
		}
		ImGui::Text("Enemy Direction: (%i,%i)", (int)enemyDirection.x, (int)enemyDirection.y);
		if (enemies.size() > 0)
			ImGui::Text("Enemy (%.1f, %.1f)", enemies[0].getPosition().x, enemies[0].getPosition().y);
		//ImGui::Text("Player Distance From Platform : %.1f", player.GetDistance(terrainGeneration.platforms[0].GetPosition()));
		ImGui::End();


#pragma endregion

#pragma region render

		window.clear();

		view.setCenter(player.getPosition());
		window.setView(view);

		background.Draw(window);

		for (auto& platform : terrainGeneration.platforms) {
			if (player.GetDistance(platform.GetPosition()) <= view.getSize().x / 1.5f)
				platform.Draw(window);
		}

		//for (auto& platform : platforms) {
		//	platform.Draw(window);
		//}

		for (auto& enemy : enemies) {
			if (player.GetDistance(enemy.getPosition()) <= view.getSize().x / 1.5f) 
				enemy.draw(window);
		}

		player.draw(window);

		ImGui::SFML::Render(window);

		window.display();

#pragma endregion



	}

	ImGui::SFML::Shutdown();
	return 0;

}