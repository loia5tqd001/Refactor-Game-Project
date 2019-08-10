#include "pch.h"
#include "BulletDynamite.h"


BulletDynamite::BulletDynamite(int nx, Enemy *enemy, const Vector2& spawnPos, Vector2 vel, int farLevel) :
	Bullet(State::DynamiteNapalm_Dynamite, 3, spawnPos, { nx * BULLET_MOVING, 0.0f }, nx, enemy)
{
	animations.emplace(State::DynamiteNapalm_Dynamite, Animation(SpriteId::DynamiteNapalm_Dynamite, 0.1f));
	animations.emplace(State::Explode, Animation(SpriteId::Explode, 0.2f));
	if (nx < 0) GameObject::FlipPosXToLeft(pos.x, enemy->GetPosX(), this->GetWidth(), enemy->GetWidth());
	Target(farLevel);
}

void BulletDynamite::Update(float dt, const std::vector<GameObject*>& coObjects)
{
	if (holdtime < TIME_TO_THROW)
	{
		holdtime += dt;
		if (triggered)
		{
			SetState(State::Explode);
			holdtime = TIME_TO_THROW;
		}
		return;
	}

	if (curState == State::Explode)
	{
		if (animations.at(curState).IsDoneCycle())
		{
			SetState(State::Destroyed);
			if (triggered)
			{
				auto boss = dynamic_cast<DynamiteNapalm*>(enemy);
				boss->TakeDinamiteDamage(4);
			}
			return;
		}
		vel.x = 0;
		vel.y = 0;
		animations.at(curState).Update(dt);
		return;
	}

	holdtime += dt;
	vel.x = nx * Speed * cos(pi / 180 * Alpha);
	vel.y = (holdtime - TIME_TO_THROW) * Gravity - Speed * sin(pi / 180 * Alpha);


	HandleCollisions(dt, coObjects);
	animations.at(curState).Update(dt);
}

RectF BulletDynamite::GetBBox() const
{
	return VisibleObject::GetBBox();
}

void BulletDynamite::HandleCollisions(float dt, const std::vector<GameObject*>& coObjects)
{
	auto coEvents = CollisionDetector::CalcPotentialCollisions(*this, coObjects, dt);
	if (coEvents.size() == 0)
	{
		pos.x += vel.x*dt;
		pos.y += vel.y*dt;
		return;
	}

	float min_tx, min_ty, nx, ny;
	CollisionDetector::FilterCollisionEvents(coEvents, min_tx, min_ty, nx, ny);
	if (coEvents.size() == 0)
		return;

	for (auto&e : coEvents)
	{
		if (auto block = dynamic_cast<Block*>(e.pCoObj))
		{
			switch (block->GetType())
			{
			case ClassId::RigidBlock:
			{
				if (e.ny != 0)
					SetState(State::Explode);
				if (e.nx != 0)
				{
					this->nx = -this->nx;
				}
			}
			default:
				break;
			}
		}
		else if (dynamic_cast<Enemy*>(e.pCoObj))
		{
			pos.x += vel.x*dt;
			pos.y += vel.y*dt;
		}
		else
			AssertUnreachable();
	}
}

void BulletDynamite::Trigger()
{
	if (holdtime < TIME_TO_THROW)
	{
		triggered = true;
	}
	
	vel.x = 0;
	vel.y = 0;
	SetState(State::Explode);
}

void BulletDynamite::HitCaptain()
{
	vel = Vector2{ 0,0 };
	Trigger();
}

inline void BulletDynamite::Target(int farLevel)
{
	if (farLevel == 3)
	{
		Alpha = 70.0f;
		Speed = 331.92f;
	}
	else if(farLevel == 2)
	{
		Alpha = 70.0f;
		Speed = 287.45f;
	}
	else if(farLevel == 1)
	{
		Alpha = 70.0f;
		Speed = 234.7f;
	}
	else
	{
		Alpha = 70.0f;
		Speed = 165.96f;
	}
}
