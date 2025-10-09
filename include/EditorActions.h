#pragma once
#include "EditorAction.h"
#include "Platform.h"
#include <vector>
#include "TileManager.h"
#include "EnemyManager.h"

struct AddPlatformAction : public EditorAction
{
	AddPlatformAction(std::vector<Platform>& platforms, const Platform& newPlatform, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	Platform platform;
	size_t index;
};

struct DeletePlatformAction : public EditorAction
{
	DeletePlatformAction(std::vector<Platform>& platforms, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	Platform platform;
	size_t index;
};

struct MovePlatformAction : public EditorAction
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

struct ResizePlatformAction : public EditorAction
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

struct ChangeTileAction : public EditorAction
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

struct AddEnemyAction : public EditorAction
{
	AddEnemyAction(std::vector<EnemySpawnPoint>& enemySpawnPoints, const EnemySpawnPoint& enemySpawnPoint, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<EnemySpawnPoint>& enemySpawnPoints;
	EnemySpawnPoint enemySpawnPoint;
	size_t index;
};

struct DeleteEnemyAction : public EditorAction
{
	DeleteEnemyAction(std::vector<EnemySpawnPoint>& enemySpawnPoints, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<EnemySpawnPoint>& enemySpawnPoints;
	size_t index;
	EnemySpawnPoint enemySpawnPoint;
};

struct MoveEnemyAction : public EditorAction
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

struct ChangeEnemyTypeAction : public EditorAction
{
	ChangeEnemyTypeAction(EnemySpawnPoint& enemySpawnPoint, std::string oldName, std::string newName, EnemyManager& enemyManager);

	void undo() override;
	void redo() override;

private:
	EnemySpawnPoint& enemySpawnPoint;
	std::string oldName;
	std::string newName;
	EnemyManager& enemyManager;
};