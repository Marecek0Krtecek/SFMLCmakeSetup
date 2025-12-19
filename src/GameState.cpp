#include "GameState.h"

GameState::GameState(sf::RenderWindow& window, StateManager& manager) :
	stateManager(manager),
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)),
	player(&textures.get(playerTexture), sf::Vector2u(8, 4), 0.15f, 500.f, 200.f, 1.f, checkpoints),
	gameUI(view, player)
{
	ResizeView(window, view);

	enemyManager.loadFromFile(RESOURCES_PATH "config.json");
	tiles.loadFromFile(RESOURCES_PATH "config.json");
	
	std::ifstream file(RESOURCES_PATH "levels/level_1.json");
	nlohmann::json j;
	
	file >> j;

	Serializer::loadPlatforms(j, platforms, textures, tiles);
	Serializer::loadEnemySpawnPoints(j, enemySpawnPoints);
	Serializer::loadBackgrounds(j, backgrounds, textures);
	Serializer::loadCheckpoints(j, checkpoints);

	file.close();

	player.setScale(sf::Vector2f(2.f, 2.f));
	player.setPosition(checkpoints["spawn"].GetPosition());

	enemies.reserve(10);

}

void GameState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	
	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyPressed:
		//if (event.key.code == sf::Keyboard::Escape) window.close();

		if (event.key.code == sf::Keyboard::F5) stateManager.changeState<EditorState>(window, stateManager);

		break;
	case sf::Event::Resized:
		ResizeView(window, view);
		break;
	}
}

void GameState::update(float deltaTime) {
#pragma region updates and colisions


	player.Update(deltaTime);

	gameUI.update(deltaTime);
	
	for (size_t i = 0; i < enemies.size(); i++) {
		auto& enemy = enemies[i];

		enemy.UpdateBehavior(deltaTime, platforms, player);

		enemy.Update(deltaTime);

		if (player.GetDistance(enemy.getPosition()) > view.getSize().x / 1.8f) {
			if(enemy.spawnPointID >= 0)
				enemySpawnPoints[enemy.spawnPointID].hasChild = false;

			enemies.erase(enemies.begin() + i);
		}
	}

	///collisions

	sf::Vector2f direction;
	for (auto& platform : platforms) {
		if (player.GetDistance(platform.GetPosition()) <= view.getSize().x / 1.8f) {
			if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.f)) {
				player.OnCollision(direction);
			}
			for (auto& enemy : enemies) {
				if (platform.GetCollider().CheckCollision(enemy.GetCollider(), direction, 1.f)) {
					enemy.OnCollision(direction);
				}
			}
		}

	}

	///spawning enemies
	for (size_t i = 0; i < enemySpawnPoints.size(); i++) {
		const auto& enemySP = enemySpawnPoints[i];

		if (!enemySP.hasChild) {
			if (player.GetDistance(enemySP.GetPosition()) <= view.getSize().x / 1.8f) {
				SpawnEnemy(enemies, enemySP, i);
				enemySpawnPoints[i].hasChild = true;
			}
		}
		
	}

	///checkpoints
	for (const auto& [name, checkpoint] : checkpoints) {
		if (player.GetDistance(checkpoint.GetPosition()) < player.GetSize().x * 2.f) {
			player.setCheckpoint(name);
		}
	}

#pragma endregion

#pragma region ImGui

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
		SpawnEnemy(enemies, EnemySpawnPoint("Green Slime", player.getPosition()), -1);
	if (ImGui::Button("Restart Game"))
		RestartGame(player, enemies);

	ImGui::End();


#pragma endregion

}

void GameState::render(sf::RenderWindow& window) {
#pragma region render

	view.setCenter(player.getPosition());
	window.setView(view);

	for(auto& background : backgrounds) {
		background.Draw(window);
	}

	for (auto& platform : platforms) {
		if (player.GetDistance(platform.GetPosition()) <= view.getSize().x / 1.5f)
			platform.Draw(window);
	}

	for (auto& enemy : enemies) {
		if (player.GetDistance(enemy.getPosition()) <= view.getSize().x / 1.5f)
			enemy.draw(window);
	}

	player.draw(window);

	gameUI.Draw(window);

#pragma endregion

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void GameState::ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void GameState::RestartGame(Player& player, std::vector<Enemy>& enemies) {
	player.Restrart();
	enemies.clear();
	for (auto& enemy : enemySpawnPoints) {
		enemy.hasChild = false;
	}
}

void GameState::SpawnEnemy(std::vector<Enemy>& enemies,const EnemySpawnPoint& spawnPoint, int SPID) {
	enemies.push_back(Enemy(enemyManager, spawnPoint, textures, SPID));
}