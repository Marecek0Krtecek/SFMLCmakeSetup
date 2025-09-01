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
#pragma region SetupStuf

	sf::RenderWindow window(sf::VideoMode(1080, 720), "myGame", sf::Style::Default);

	window.setFramerateLimit(60);
	
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	ResizeView(window, view);

	ImGui::SFML::Init(window);

#pragma region Textures and sprites

	sf::Texture playerTexture;
	//playerTexture.loadFromFile(RESOURCES_PATH "snake.png");
	//playerTexture.loadFromFile(RESOURCES_PATH "brackeys_platformer_assets/sprites/knight.png", sf::IntRect(10, 9, 12, 19));
	//playerTexture.loadFromFile(RESOURCES_PATH "brackeys_platformer_assets/sprites/knight.png", sf::IntRect(0, 0, 256 / 8, 256 / 8));
	if (!playerTexture.loadFromFile(RESOURCES_PATH "brackeys_platformer_assets/sprites/knight.png"))
		std::cout << "playerTexture not loaded\n";

	sf::Texture platfomrTexture;
	if (!platfomrTexture.loadFromFile(RESOURCES_PATH "brackeys_platformer_assets/sprites/platforms.png"/*, sf::IntRect(0, 0, 64 / 4, 64 / 8)*/))
		std::cout << "platfomrTexture not loaded\n";

	sf::Texture backgroungTexture;
	if (!backgroungTexture.loadFromFile(RESOURCES_PATH "Glacial-mountains-parallax-background_vnitti/background_glacial_mountains.png"))
		std::cout << "backgroungTexture not loaded\n";

	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile(RESOURCES_PATH "brackeys_platformer_assets/sprites/slime_green.png"))
		std::cout << "enemyTexture not loaded\n";


#pragma endregion


	//Player player(sf::Vector2f(12.f * 5.f, 19.f * 5.f), &playerTexture);
	//Player player(sf::Vector2f(50.f, 50.f), &playerTexture);
	Player player(&playerTexture, sf::Vector2u(8, 8), 0.1f, 500.f, 200.f);
	player.setScale(sf::Vector2f(2.f, 2.f));
	player.setPosition(0.f, -1050.f);

	std::vector<Enemy> enemies;
	enemies.reserve(10);

	float deltaTime = 0;
	sf::Clock clock;

	Background background(&backgroungTexture);
	background.SetPosition(0.f, 0.f);
	background.SetScale(sf::Vector2f(15.f, 15.f));
	background.parlaxStrength = 0.5f;

	TerrainGeneration terrainGeneration(&platfomrTexture, sf::Vector2u(4, 8));
	terrainGeneration.platforms.reserve(5002);
	
	terrainGeneration.AddPlatform(Platform(sf::Vector2f(1000.f, 50.f), sf::Vector2f(100.f, -1000.f)));

	terrainGeneration.GeneratedPlatformsSinus(sf::Vector2f(0.f, 0.f), sf::Vector2f(5000.f, 2000.f));

	//for (int i = rand() % 20; i < terrainGeneration.platforms.size(); i += rand() % 20) {
	//	SpawnEnemy(enemies, &enemyTexture, sf::Vector2u(4, 3), 0.1f, 250.f, sf::Vector2f(terrainGeneration.platforms[i].GetPosition().x, terrainGeneration.platforms[i].GetPosition().y - terrainGeneration.platforms[i].GetSize().y / 2.f));
	//}

	//for (auto& enemy : enemies) {
	//	enemy.setScale(sf::Vector2f(10.f, 10.f));
	//}

	//terrainGeneration.AddPlatform(Platform(sf::Vector2f(100.f, 50.f), sf::Vector2f(-10.f, 200.f), &platfomrTexture));

	//terrainGeneration.GeneratedPlatformsRandom(sf::Vector2f(0.f, 0.f), sf::Vector2f(3000.f, 3000.f));
	//std::vector<std::string> mapMatrix = {
	//	"Z      ",
	//	"       ",
	//	"Y      ",
	//	" XXYXX ",
	//	"XX   XX",
	//	"X X X X",
	//	"Y  Y  Y",
	//	"X X X X",
	//	"XX   XX",
	//	" XX XX ",
	//	"   Z   "
	//};

	//std::vector<Platform> solidPlatforms;
	//std::vector<Platform> pasiblePlatforms;
	//std::vector<Platform> pushiblePlatform;

	//for (int y = 0;y < mapMatrix.size(); y++) {
	//	for (int x = 0;x < mapMatrix[0].size(); x++) {
	//		if (mapMatrix[y][x] == 'X')
	//			solidPlatforms.push_back(Platform(sf::Vector2f(100.f, 100.f), sf::Vector2f(x * 100.f, y * 100.f)));
	//		else if (mapMatrix[y][x] == 'Y') {
	//			pasiblePlatforms.push_back(Platform(sf::Vector2f(100.f, 100.f), sf::Vector2f(x * 100.f, y * 100.f)));
	//		}
	//		else if (mapMatrix[y][x] == 'Z') {
	//			pushiblePlatform.push_back(Platform(sf::Vector2f(100.f, 100.f), sf::Vector2f(x * 100.f, y * 100.f)));
	//		}
	//	}
	//}

	//for (auto& platform : pasiblePlatforms) {
	//	platform.SetColor(sf::Color::Blue);
	//}
	//for (auto& platform : pushiblePlatform) {
	//	platform.SetColor(sf::Color::Cyan);
	//}

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

		//for (auto& enemy : enemies) {
		//	if(player.GetDistance(enemy.getPosition()) <= 2000.f)
		//		enemy.Update(deltaTime);
		//}

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
		
		//for (auto& platform : pushiblePlatform) {
		//	platform.GetCollider().CheckCollision(player.GetCollider(), 0.2f);
		//}

		//for (auto& platform : solidPlatforms) {
		//	platform.GetCollider().CheckCollision(player.GetCollider(), 1.f);
		//	for (auto& other : pushiblePlatform) {
		//		platform.GetCollider().CheckCollision(other.GetCollider(), 1.f);
		//	}
		//}

		///collisions

		sf::Vector2f direction;
		sf::Vector2f enemyDirection;
		for (auto& platform : terrainGeneration.platforms) {
			if (player.GetDistance(platform.GetPosition()) <= player.GetSize().x * 5.f) {
				if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.f)) {
					player.OnCollision(direction);
				}
			}

			if (player.GetDistance(platform.GetPosition()) <= view.getSize().x / 1.8f) {
				if (platform.canHaveEnemy && !platform.hasEnemy) {
					SpawnEnemy(enemies, &enemyTexture, sf::Vector2u(4, 3), 0.1f, 250.f, sf::Vector2f(platform.GetPosition().x, platform.GetPosition().y - platform.GetSize().y / 2.f));
					platform.hasEnemy = true;
					enemies[enemies.size() - 1].thisPlatformHasMe = &platform.hasEnemy;
				}
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
		

#pragma endregion

#pragma region ImGui
		
	#pragma region ImGui update

		ImGui::SFML::Update(window, clock.restart());
		//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	#pragma endregion

		//ImGui::ShowDemoWindow();

		ImGui::Begin("Debug");
		ImGui::Text("FPS: %.1f", 1.f / deltaTime);
		ImGui::Text("Player: (%.1f, %.1f)", player.getPosition().x, player.getPosition().y);
		if (ImGui::SliderFloat("Gravity", &player.gravity, 10.f, 500.f))
			for (auto& enemy : enemies)
				enemy.gravity = player.gravity;
		ImGui::Text("Enemies Count: %i", (int)enemies.size());
		if(ImGui::Button("Spawn Enemy"))
			SpawnEnemy(enemies, &enemyTexture, sf::Vector2u(4, 3), 0.1f, 250.f, player.getPosition());
		if (ImGui::Button("Restart Game"))
			RestartGame(player, background, enemies);
		if (ImGui::Button("Stop Game")){
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


		//for (auto& platform : solidPlatforms) {
		//	platform.Draw(window);
		//}
		//for (auto& platform : pasiblePlatforms) {
		//	platform.Draw(window);
		//}
		//for (auto& platform : pushiblePlatform) {
		//	platform.Draw(window);
		//}

		background.Draw(window);

		for (auto& platform : terrainGeneration.platforms) {
			if (player.GetDistance(platform.GetPosition()) <= 2000.f) 
				platform.Draw(window);
		}

		for (auto& enemy : enemies) {
			if (player.GetDistance(enemy.getPosition()) <= 2000.f) 
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