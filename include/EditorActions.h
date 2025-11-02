#pragma once
#include "EditorAction.h"
#include "Platform.h"
#include <vector>
#include "TileManager.h"
#include "EnemyManager.h"
#include "Background.h"
#include "Checkpoint.h"

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

struct AddBackgroundAction : public EditorAction
{
	AddBackgroundAction(std::vector<Background>& backgrounds, const Background& background, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Background>& backgrounds;
	Background background;
	size_t index;
};

struct DeleteBackgroundAction : public EditorAction
{
	DeleteBackgroundAction(std::vector<Background>& backgrounds, const Background& background, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Background>& backgrounds;
	Background background;
	size_t index;
};

struct ChangeBackgroundSizeAction : public EditorAction
{
	ChangeBackgroundSizeAction(Background& background, const sf::Vector2f& oldSize, const sf::Vector2f& newSize);

	void undo() override;
	void redo() override;

private:
	Background& background;
	sf::Vector2f oldSize;
	sf::Vector2f newSize;
};

struct ChangeParllaxStrengthAction : public EditorAction
{
	ChangeParllaxStrengthAction(Background& background, const float& oldParllax, const float& newParllax);

	void undo() override;
	void redo() override;

private:
	Background& background;
	float oldParllax;
	float newParllax;
};

struct AddCheckpointAction : public EditorAction
{
	AddCheckpointAction(std::vector<Checkpoint>& checkpoints, const Checkpoint& checkpoint, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Checkpoint>& checkpoints;
	Checkpoint checkpoint;
	size_t index;
};

struct DeleteCheckpointAction : public EditorAction
{
	DeleteCheckpointAction(std::vector<Checkpoint>& checkpoints, const Checkpoint& checkpoint, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Checkpoint>& checkpoints;
	Checkpoint checkpoint;
	size_t index;
};

struct MoveCheckpointAction : public EditorAction
{
	MoveCheckpointAction(Checkpoint& checkpoint, const sf::Vector2f& oldPos, const sf::Vector2f& newPos);

	void undo() override;
	void redo() override;

private:
	Checkpoint& checkpoint;
	sf::Vector2f oldPos;
	sf::Vector2f newPos;
};

struct ChangeCheckpointNameAction : public EditorAction
{
	ChangeCheckpointNameAction(Checkpoint& checkpoint, const std::string& oldName, const std::string& newName);

	void undo() override;
	void redo() override;

private:
	Checkpoint& checkpoint;
	std::string oldName;
	std::string newName;
};