#pragma once

class Item : public VisibleObject
{
private:
	static constexpr float FALLING_SPEED = 150.0f;
	static constexpr float TIME_TO_DISAPPEAR = 5.0f;

	float maxY; // max position falling, being set from database
	float minY; // to bounce before falling
	float timeOnGround = 0.0f;
	SoundId sound;
	SpriteId itemType; // use SpriteId to represent item type
	class Capsule* parent;

	void OnItemNotCollected();

public:
	Item(Vector2 pos, float maxY, SpriteId itemType, Capsule* parent);
	void Update(float dt, const std::vector<GameObject*>& coObjects = {}) override;
	void BeingHit(); // call when captain use force to collide with capsule
	void BeingCollected(); 
	void OnOutOfViewPort() override; 
};

