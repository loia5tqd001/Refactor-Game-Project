#pragma once
#include "Enemy.h"
class ElectricBat :
	public Enemy
{
private:
	static constexpr float HOR_DISTANCE = 60.0f;
	static constexpr float VER_DISTANCE = 40.0f;
	static constexpr float DETECT_CAPTAIN_DISTANCE = 90.0f;
	static constexpr float MOVING_SPEED = 100.0f;

	Captain *cap;
	float countHorDistance = 0;
	float countVerDistance = 0;
	float countHorDistanceA = 0;
	float countVerDistanceA = 0;
	Vector2 SpawnPos;
	bool finishCycle = false;
	int counterFly = 0;

	void OnAction();
	bool OnState(State state);
public:
	ElectricBat(Vector2 spawnPos, Grid* grid, Captain *cap);
	void Update(float dt, const std::vector<GameObject*>& coObjects) override;
	void TakeDamage(int damage) override;
	void HandleCollisions(float dt, const std::vector<GameObject*>& coObjects);
};

