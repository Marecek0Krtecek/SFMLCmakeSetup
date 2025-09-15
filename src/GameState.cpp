#include "GameState.h"

GameState::GameState(sf::RenderWindow& window) :
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)),
	player(&textures.get(playerTexture), sf::Vector2u(8, 8), 0.1f, 500.f, 200.f),
	background(&textures.get(backgroundTexture)),
	terrainGeneration(&textures.get(platfomrTexture), sf::Vector2u(4, 8))
{
	ResizeView(window, view);
	
	player.setScale(sf::Vector2f(2.f, 2.f));

	enemies.reserve(10);

	background.SetPosition(0.f, 0.f);
	background.SetScale(sf::Vector2f(15.f, 15.f));
	background.parlaxStrength = 0.5f;

	terrainGeneration.platforms.reserve(5002);
	terrainGeneration.GeneratedPlatformsSinus(sf::Vector2f(0.f, 0.f), sf::Vector2f(5000.f, 2000.f));

}

void GameState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	
	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Escape)
			window.close();
		break;
	case sf::Event::Resized:
		ResizeView(window, view);
		break;
	}
}

void GameState::update(float deltaTime) {
#pragma region updates and colisions


	background.Move(-player.GetVelocity() * background.parlaxStrength * deltaTime);

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

	ImGui::Text("Enemy Direction: (%i,%i)", (int)enemyDirection.x, (int)enemyDirection.y);
	if (enemies.size() > 0)
		ImGui::Text("Enemy (%.1f, %.1f)", enemies[0].getPosition().x, enemies[0].getPosition().y);
	//ImGui::Text("Player Distance From Platform : %.1f", player.GetDistance(terrainGeneration.platforms[0].GetPosition()));
	ImGui::End();


#pragma endregion

}

void GameState::render(sf::RenderWindow& window) {
#pragma region render

	view.setCenter(player.getPosition());
	window.setView(view);

	background.Draw(window);

	for (auto& platform : terrainGeneration.platforms) {
		if (player.GetDistance(platform.GetPosition()) <= view.getSize().x / 1.5f)
			platform.Draw(window);
	}

	for (auto& enemy : enemies) {
		if (player.GetDistance(enemy.getPosition()) <= view.getSize().x / 1.5f)
			enemy.draw(window);
	}

	player.draw(window);

#pragma endregion

}

void GameState::ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void GameState::RestartGame(Player& player, Background& background, std::vector<Enemy>& enemies) {
	player.Restrart();
	background.Restart();
	enemies.erase(enemies.begin(), enemies.end());
}

void GameState::SpawnEnemy(std::vector<Enemy>& enemies, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) {
	enemies.push_back(Enemy(texture, imageCount, switchTime, speed, position));
}