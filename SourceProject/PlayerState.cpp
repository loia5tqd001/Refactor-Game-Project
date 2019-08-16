#include "pch.h"
#include "PlayerState.h"
#include "Player.h"

Player* PlayerState::player = nullptr;

void PlayerState::Update(float dt, const std::vector<GameObject*>& coObjects)
{
	// Handle for Update:
	// - Handle collision to check if player collide with something, check if player should change to other state or not
	// - If player should change to other state, we should not handle key press, otherwise handle key press (handle input)
	//   - Do that to avoid updating player after being set to another state (which is bad)
	// - Handle key press
	// - Check if player should change to other state again.
	// => nextStateToChange should be reset everywhen Enter to a state, to avoid forgetting due to carelessness, we reset it
	// every frame in the beginning of Update (ONE position for ALL state instead of in EVERY Enter function of EACH state)

	nextStateToChange.reset();
	HandleCollisions(dt, coObjects);
	if (ChangeToNextState()) return; 
	HandleKeyPressed();
	ChangeToNextState();
}

bool PlayerState::ChangeToNextState()
{
	if (nextStateToChange) {
		player->SetState(*nextStateToChange);
	}
	return nextStateToChange.has_value();
}

void PlayerState::HandleCollisions(float dt, const std::vector<GameObject*>& coObjects)
{
	auto coEvents = CollisionDetector::CalcPotentialCollisions(*player, coObjects, dt);
	if (coEvents.size() == 0)
	{
		player->pos.x += player->vel.x * dt;
		player->pos.y += player->vel.y * dt;
		return;
	}

	float min_tx, min_ty, nx, ny;
	CollisionDetector::FilterCollisionEvents(coEvents, min_tx, min_ty, nx, ny);

	if (coEvents.size() == 0) return;

	player->pos.x += min_tx * player->vel.x * dt;
	player->pos.y += min_ty * player->vel.y * dt;

	for (auto& e : coEvents)
	{
		if (auto spawner = dynamic_cast<Spawner*>(e.pCoObj))
			OnCollideWithSpawner(spawner, dt, e);

		else if (auto ambush = dynamic_cast<AmbushTrigger*>(e.pCoObj))
			OnCollideWithAmbushTrigger(ambush, dt, e);

		else if (auto ledge = dynamic_cast<MovingLedge*>(e.pCoObj))
			OnCollideWithMovingLedge(ledge, dt, e);

		else if (auto ledge = dynamic_cast<BreakableLedge*>(e.pCoObj))
			OnCollideWithBreakableLedge(ledge, dt, e);

		else if (auto capsule = dynamic_cast<Capsule*>(e.pCoObj))
			OnCollideWithCapsule(capsule, dt, e);

		else if (auto item = dynamic_cast<Item*>(e.pCoObj))
			OnCollideWithItem(item, dt, e);

		else if (auto enemy = dynamic_cast<Enemy*>(e.pCoObj))
			OnCollideWithEnemy(enemy, dt, e);
		
		else if (auto bullet = dynamic_cast<Bullet*>(e.pCoObj))
			OnCollideWithBullet(bullet, dt, e);
	}
}

void PlayerState::OnCollideWithSpawner(Spawner* spawner, float dt, const CollisionEvent& e)
{
	// common handle collision with spawner
}

void PlayerState::OnCollideWithAmbushTrigger(AmbushTrigger* ambush, float dt, const CollisionEvent& e)
{
	// common handle collision with ambush trigger
}

void PlayerState::OnCollideWithMovingLedge(MovingLedge* ledge, float dt, const CollisionEvent& e)
{
	// common handle collision with moving ledge
}

void PlayerState::OnCollideWithBreakableLedge(BreakableLedge* ledge, float dt, const CollisionEvent& e)
{
	// common handle collision with breakable ledge
}

void PlayerState::OnCollideWithCapsule(Capsule* capsule, float dt, const CollisionEvent& e)
{
	// common handle collision with capsule
}

void PlayerState::OnCollideWithItem(Item* item, float dt, const CollisionEvent& e)
{
	// common handle collision with item
}

void PlayerState::OnCollideWithEnemy(Enemy* enemy, float dt, const CollisionEvent& e)
{
	// common handle collision with enemy
}

void PlayerState::OnCollideWithBullet(Bullet* bullet, float dt, const CollisionEvent& e)
{
	// common handle collision with bullet
}
