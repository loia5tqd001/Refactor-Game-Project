#pragma once

class Captain;
class CaptainState
{
protected:
	// reference for more convenient reference in subclasses
	Data data;
	Window& wnd = Window::Instance();
	Settings& setting = Settings::Instance();
	SceneManager& sceneManager = SceneManager::Instance();
public:
	virtual void Enter(Captain& cap, State fromState, Data&& data = {}) = 0; // handle when change to this state
	virtual Data Exit(Captain& cap, State toState) = 0; // handle when change to other state
	virtual void OnKeyUp(Captain& cap, BYTE keyCode) = 0;
	virtual void OnKeyDown(Captain& cap, BYTE keyCode) = 0;
	virtual void Update(Captain& cap, float dt, const std::vector<GameObject*>& coObjects) = 0; // captain delegates his update call to this function
	virtual void HandleCollisions(Captain& cap, float dt, const std::vector<GameObject*>& coObjects) = 0;
	virtual ~CaptainState() = default;

protected:
	// define properties for subclasses here. Those states need to communicate via Data, which need unified property name
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
	static constexpr auto MIN_JUMP_HEIGHT = 35.0f;

	static constexpr auto FALL_SPEED_VER = 190.0f;
	static constexpr auto FALL_SPEED_VER_MAX = 210.0f;
	static constexpr auto FALL_SPEED_VER_MIN = 70.0f;
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
};

