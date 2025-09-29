#pragma once
#include "EditorAction.h"
#include "Platform.h"
#include <vector>
#include "TileManager.h"
#include "EnemyManager.h"

struct AddPlatformAction : EditorAction
{
	AddPlatformAction(std::vector<Platform>& platforms, const Platform& newPlatform, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	Platform platform;
	size_t index;
};

struct DeletePlatformAction : EditorAction
{
	DeletePlatformAction(std::vector<Platform>& platforms, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	Platform platform;
	size_t index;
};

struct MovePlatformAction : EditorAction
{
	MovePlatformAction(std::vector<Platform>& platforms, size_t index, sf::Vector2f oldPos, sf::Vector2f newPos);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	size_t index;
	sf::Vector2f oldPos;
	sf::Vector2f newPos;
};

struct ResizePlatformAction : EditorAction
{
	ResizePlatformAction(std::vector<Platform>& platforms, size_t index, sf::Vector2f oldSize, sf::Vector2f newSize);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	size_t index;
	sf::Vector2f oldSize;
	sf::Vector2f newSize;

};

struct ChangeTileAction : EditorAction
{
	ChangeTileAction(std::vector<Platform>& platforms, size_t index, std::string oldTile, std::string newTile, TileManager& tileManager);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	size_t index;
	std::string oldTile;
	std::string newTile;
	TileManager& tileManager;
};

struct AddEnemyAction : EditorAction
{
	AddEnemyAction(std::vector<EnemySpawnPoint>& enemySpawnPoints, const EnemySpawnPoint& enemySpawnPoint, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<EnemySpawnPoint>& enemySpawnPoints;
	EnemySpawnPoint enemySpawnPoint;
	size_t index;
};

struct DeleteEnemyAction : EditorAction
{
	DeleteEnemyAction(std::vector<EnemySpawnPoint>& enemySpawnPoints, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<EnemySpawnPoint>& enemySpawnPoints;
	size_t index;
	EnemySpawnPoint enemySpawnPoint;
};

struct MoveEnemyAction : EditorAction
{
	MoveEnemyAction(std::vector<EnemySpawnPoint>& enemySpawnPoints, size_t index, sf::Vector2f oldPos, sf::Vector2f newPos);

	void undo() override;
	void redo() override;

private:
	std::vector<EnemySpawnPoint>& enemySpawnPoints;
	size_t index;
	sf::Vector2f oldPos;
	sf::Vector2f newPos;
};