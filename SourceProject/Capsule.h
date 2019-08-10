#pragma once

class Capsule :	public VisibleObject
{
private:
	const SpriteId realItemType;
	const float maxY; // maxY of items to spawn
	Grid* grid;
	int countRealItem = 1;

public:
	Capsule(Vector2 pos, SpriteId itemType, float maxY, Grid* grid, bool isNoBackground = false);
	void Update(float dt, const std::vector<GameObject*>& coObjects = {}) override;
	void BeingHit();
	void OnItemNotCollected() { countRealItem++; }
};

