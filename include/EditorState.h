#pragma once
#include "State.h"
#include "Platform.h"
#include "Enemy.h"
#include "Background.h"
#include "TextureManager.h"
#include <vector>
#include "imgui.h"
#include "imgui-SFML.h"
#include "Serializer.h"
#include <fstream>
#include "misc/cpp/imgui_stdlib.h"
#include "TileManager.h"
#include <iostream>

class EditorState : public State
{
public:
	EditorState(sf::RenderWindow& window);

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	
private:
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	sf::Vector2f snapToGridFunc(const sf::Vector2f& pos, const float& gridSize, bool enabled);
	void drawGrid(sf::RenderWindow& window, const float& gridSize);

private:
	const float VIEW_HEIGHT = 1024.f;

	float panSpeed = 300.f;
	float zoomFactor = 1.1f;
	sf::View view;

	std::vector<Platform> platforms;
	int selectedIndex = -1;

	sf::Vector2f selectPos = {};
	sf::Vector2f selectSize = {100.f, 50.f};

	//Textures
	TextureManager textures;
	std::string playerTexture = "brackeys_platformer_assets/sprites/knight.png";
	std::string platformTexture = "brackeys_platformer_assets/sprites/platforms.png";
	std::string backgroundTexture = "Glacial-mountains-parallax-background_vnitti/background_glacial_mountains.png";
	std::string enemyTexture = "brackeys_platformer_assets/sprites/slime_green.png";

	TileManager tileManager;

	int currentItem = 0;
	std::vector<const char*> tileNames;
	std::vector<std::string> strTileNames;

	//ImGui windows active
	bool platformWindow = false;
	bool platformEditWindow = false;
	bool saveWindow = false;
	bool loadWindow = false;
	bool gridSettingWindow = false;

	//Grid
	bool snapToGrid = true;
	float gridSize = 32.f;

};