#pragma once
#include "CaptainState.h"

class CaptainClimbing : public CaptainState
{
	int ClimbingLevel = std::numeric_limits<int>::infinity();
	std::vector<BYTE> KeyBuffer;
	int bufferSize = 20;
	void ProcessInput(Captain& cap);
	Block* climbBar = nullptr;
public:
	void Enter(Captain& cap, State fromState, Data&& data) override;
	Data Exit(Captain& cap, State toState) override;
	void OnKeyUp(Captain& cap, BYTE keyCode) override;
	void OnKeyDown(Captain& cap, BYTE keyCode) override;
	void Update(Captain& cap, float dt, const std::vector<GameObject*>& coObjects) override;
	void HandleCollisions(Captain& cap, float dt, const std::vector<GameObject*>& coObjects) override;
	auto GetClimbBar() { return climbBar; }
	void SetClimbBar(Block* climb) { climbBar = climb; }
};

