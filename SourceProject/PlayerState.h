#pragma once

class PlayerState
{
protected:
#pragma region reference for more convenient reference in subclasses
	Window& wnd = Window::Instance();
	Settings& setting = Settings::Instance();
	SceneManager& sceneManager = SceneManager::Instance();
#pragma endregion

#pragma region common properties
	std::optional<State> nextStateToChange;
	static class Player* player;
#pragma endregion

#pragma region common methods
	bool ChangeToNextState();
	void HandleCollisions(float dt, const std::vector<GameObject*>& coObjects);
	virtual void HandleKeyPressed() = 0;

	virtual void OnCollideWithSpawner(class Spawner* spawner, float dt, const CollisionEvent& e);
	virtual void OnCollideWithAmbushTrigger(class AmbushTrigger* ambush, float dt, const CollisionEvent& e);
	virtual void OnCollideWithMovingLedge(class MovingLedge* ledge, float dt, const CollisionEvent& e);
	virtual void OnCollideWithBreakableLedge(class BreakableLedge* ledge, float dt, const CollisionEvent& e);
	virtual void OnCollideWithCapsule(class Capsule* capsule, float dt, const CollisionEvent& e);
	virtual void OnCollideWithItem(class Item* item, float dt, const CollisionEvent& e);
	virtual void OnCollideWithEnemy(class Enemy* enemy, float dt, const CollisionEvent& e);
	virtual void OnCollideWithBullet(class Bullet* bullet, float dt, const CollisionEvent& e);
	// and so on...
	// Explanation:
	// - In PlayerState (base class), we deliver common responsiveness when collide with objects
	// - If any subclass should have different respond than the base class, it should override corresponding OnCollideWith function
#pragma endregion

public:
#pragma region public methods 
	static void SetPlayer(Player* player) { PlayerState::player = player; } // being called only once after constructed
	void Update(float dt, const std::vector<GameObject*>& coObjects); // player delegates his update call to this function
	virtual void Enter(State fromState, Data&& data = {}) = 0; // call when change to this state
	virtual Data Exit(State toState) = 0; // call when change to other state
	virtual void OnKeyUp(BYTE keyCode) = 0;
	virtual void OnKeyDown(BYTE keyCode) = 0;
	virtual ~PlayerState() = default;
#pragma endregion

protected:
#pragma region define property-strings for subclasses here. Those states need to communicate via Data, which need unified property name
	static constexpr auto IS_JUMP_RELEASED = "is-jump-released";
	static constexpr auto IS_KICKED = "is-jump-kicked-once-at-jumping-and-falling";
	static constexpr auto JUMP_HEIGHT_RealCounter = "JumpHeightRealCounter";
	static constexpr auto JUMP_HEIGHT_NeedCounter = "JumpHeightNeedCounter";
	static constexpr auto IS_TO_SIT_TACKLE = "is-to-sit-tackle";
	static constexpr auto SPIN_TIME_UP = "spin-up-time-counter";
	static constexpr auto SPIN_TIME_DOWN = "spin-down-time-counter";
	static constexpr auto IS_JUMP_FROM_WATER = "is-jump-from-water";
	static constexpr float WATER_FLOW_SPEED = -20.0f;
	static constexpr float CAP_SWIMMING_SPEED = 50.0f;
	static constexpr auto TACKLE_SPEED = 200.0f;
	static constexpr auto MOVING_HOR = 60.0f;
	static constexpr auto JUMP_SPEED_VER = 180.0f;
	static constexpr auto JUMP_SPEED_VER_MAX = 210.0f;
	static constexpr auto JUMP_SPEED_VER_MIN = 120.0f;
	static constexpr auto JUMP_SPEED_HOR = MOVING_HOR;
	static constexpr auto GRAVITY = 550.0f;
	static constexpr auto MAX_JUMP_HEIGHT = 80.0f;
	static constexpr auto FALL_SPEED_HOR = MOVING_HOR;
	static constexpr auto INJURE_FALL_SPEED = 40.0f;
	static constexpr auto INJURE_DISTANCE = 10.0f;
	static constexpr auto SPIN_SPEED_VER = 120.0f;
	static constexpr auto SPIN_SPEED_HOR = JUMP_SPEED_HOR;
	static constexpr auto TIME_KEEP_SPIN = 0.13f;
	static constexpr auto WATER_LEVEL = 454.0f;
	static constexpr auto COLLISION_OBJECT = "COLLISION_OBJECT";
	static constexpr auto CLIMBBAR = "CLIMBBAR";
	static constexpr auto ELECTRIC_SHOCK_TIME = 1.5f;
	static constexpr auto ELECTRIC_SHOCK = "ELECTRIC-SHOCK";
#pragma endregion
};


