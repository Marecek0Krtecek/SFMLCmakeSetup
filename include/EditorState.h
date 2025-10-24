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
#include <stack>
#include "EditorAction.h"
#include "EditorActions.h"
#include "EnemyManager.h"
#include "ImGuiFileDialog.h"
#include <filesystem>
#include "StateManager.h"
#include "GameState.h"
	
class EditorState : public State
{
public:
	EditorState(sf::RenderWindow& window, StateManager& manager);

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	
private:
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	sf::Vector2f snapToGridFunc(const sf::Vector2f& pos, const float& gridSize, bool enabled);
	void drawGrid(sf::RenderWindow& window, const float& gridSize);
	std::string normalizePath(std::string& path);
	std::string fileFinding(const std::string& filePathName);
	
	void clearLevel();
	void save();
	void saveAs();
	
	void loadLevel();
	void load();
	
	void selectTexture(const std::string& dirPath);

	void addAction(std::unique_ptr<EditorAction> action);

	void undo();
	void redo();

	void addPlatform(const Platform& platform);
	void duplicatePlatform(int& selectedIndex);
	void deletePlatform(int& selectedIndex);
	void movePlatform(const int& selectedIndex, sf::Vector2f oldPos, sf::Vector2f newPos);
	void resizePlatform(const int& selectedIndex, sf::Vector2f oldSize, sf::Vector2f newSize);
	void changePlatformTile(const int& selectedIndex, const std::string& oldTile, const std::string& newTile);

	void addEnemy(const EnemySpawnPoint& enemySpawnPoint);
	void moveEnemy(const int& selectedIndex, sf::Vector2f oldPos, sf::Vector2f newPos);
	void deleteEnemy(int& selectedIndex);
	void changeEnemyType(const int& selectedIndex, const std::string& oldType, const std::string& newType);
	void duplicateEnemy(int& selectedIndex);

private:
	//State references
	StateManager& stateManager;

	//Editor variables
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

	TileManager tileManager;

	int currentItem = 0;
	std::vector<const char*> tileNames;
	std::vector<std::string> strTileNames;

	//Enemies
	EnemyManager enemyManager;

	std::vector<const char*> enemyTxNames;
	std::vector<std::string> strEnemyTxNames;
	
	std::vector<EnemySpawnPoint> enemySpawnPoints;

	int eSelectedIndex = -1;

	//Backgrounds
	std::vector<Background> backgrounds;

	int bSelectedIndex = -1;

	//ImGui windows active
	bool platformWindow = false;
	bool platformEditWindow = false;
	bool saveWindow = false;
	bool loadWindow = false;
	bool gridSettingWindow = false;

	bool enemyWindow = false;
	bool enemyEditWindow = false;

	bool newLevelIsNotSaved = false;

	bool showHelpWindow = false;

	bool backgroundWindow = false;

	//Grid
	bool snapToGrid = true;
	float gridSize = 32.f;

	//Undo / Redo action variables
	std::stack<std::unique_ptr<EditorAction>> undoStack;
	std::stack<std::unique_ptr<EditorAction>> redoStack;

	//Saving / Loading
	std::string currentFilePath;
	bool isSaved = true;

#if PRODUCTION_BUILD 
	const char* resourcesPath = RESOURCES_PATH;
#else
	const char* resourcesPath = "../../../resources/";
#endif

};