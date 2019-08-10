#include "pch.h"
#include "ElectricBat.h"


ElectricBat::ElectricBat(Vector2 spawnPos, Grid * grid, Captain * cap)
	: Enemy(behavior, std::move(behaviorData), State::ElectricBat_Sleep, 1, spawnPos, grid)
{
	animations.emplace(State::ElectricBat_EndFly, Animation(SpriteId::ElectricBat_EndFly, 0.2f));
	animations.emplace(State::ElectricBat_Fly, Animation(SpriteId::ElectricBat_Fly, 0.2f));
	animations.emplace(State::ElectricBat_FlyAttack, Animation(SpriteId::ElectricBat_FlyAttack, 0.23f));
	animations.emplace(State::ElectricBat_Sleep, Animation(SpriteId::ElectricBat_Sleep, 1.0f));
	animations.emplace(State::ElectricBat_StartFly, Animation(SpriteId::ElectricBat_StartFly, 0.2f));

	this->cap = cap;
	curState = State::ElectricBat_Sleep;
	SpawnPos = pos;
}

void ElectricBat::OnAction()
{
	float distanceToCap = sqrt(abs(cap->GetPos().x - pos.x)*abs(cap->GetPos().x - pos.x) + abs(cap->GetPos().y - pos.y)*abs(cap->GetPos().y - pos.y));
	if (distanceToCap < DETECT_CAPTAIN_DISTANCE)
	{
		finishCycle = false;
		if (OnState(curState))
		{
			switch (curState)
			{
			case State::ElectricBat_Sleep:
				SetState(State::ElectricBat_StartFly);
				break;
			case State::ElectricBat_StartFly:
				SetState(State::ElectricBat_Fly);
				break;
			case State::ElectricBat_Fly:
				if (counterFly == 0) {
					counterFly++;
					SetState(State::ElectricBat_FlyAttack);
				}
				else {
					counterFly = 0;
					SetState(State::ElectricBat_EndFly);
				}
				break;
			case State::ElectricBat_FlyAttack:
				SetState(State::ElectricBat_Fly);
				break;
			case State::ElectricBat_EndFly:
				pos = SpawnPos;
				SetState(State::ElectricBat_Sleep);
				finishCycle = true;
				break;
			case State::Explode:
				SetState(State::Destroyed);
			default:
				break;
			}
		}
	}
	else
	{
		if (!finishCycle) {
			if (OnState(curState))
			{
				switch (curState)
				{
				case State::ElectricBat_Sleep:
					SetState(State::ElectricBat_StartFly);
					break;
				case State::ElectricBat_StartFly:
					SetState(State::ElectricBat_Fly);
					break;
				case State::ElectricBat_Fly:
					if (counterFly == 0) {
						counterFly++;
						SetState(State::ElectricBat_FlyAttack);
					}
					else {
						counterFly = 0;
						SetState(State::ElectricBat_EndFly);
					}
					break;
				case State::ElectricBat_FlyAttack:
					SetState(State::ElectricBat_Fly);
					break;
				case State::ElectricBat_EndFly:
					pos = SpawnPos;
					SetState(State::ElectricBat_Sleep);
					finishCycle = true;
					break;
				case State::Explode:
					SetState(State::Destroyed);
				default:
					break;
				}
			}
		}
	}
}

bool ElectricBat::OnState(State state)
{
	//if (curState != state) SetState(state);
	switch (state)
	{
	case State::ElectricBat_Sleep:
		vel.x = 0;
		vel.y = 0;
		if (animations.at(State::ElectricBat_Sleep).IsDoneCycle()) return true;
		break;
	case State::ElectricBat_StartFly:
		vel.x = 0;
		vel.y = 0;
		if (animations.at(State::ElectricBat_StartFly).IsDoneCycle()) return true;
		break;
	case State::ElectricBat_Fly:
	{
		//if (pos.x > cap->GetPos().x) nx = -1;
		//else nx = 1;

		if (std::abs(countHorDistance) < HOR_DISTANCE)
		{
			if (countHorDistance >= 0) {
				countHorDistance += MOVING_SPEED * GameTimer::Dt();
				vel.x = MOVING_SPEED;
				vel.y = 0;
			}
			else {
				countHorDistance -= MOVING_SPEED * GameTimer::Dt();
				vel.x = -MOVING_SPEED;
				vel.y = 0;
			}
		}
		else
		{
			if (std::abs(countVerDistance) < VER_DISTANCE)
			{
				if (countVerDistance >= 0) {
					countVerDistance += MOVING_SPEED * GameTimer::Dt();
					vel.y = MOVING_SPEED;
					vel.x = 0;
				}
				else {
					countVerDistance -= MOVING_SPEED * GameTimer::Dt();
					vel.y = -MOVING_SPEED;
					vel.x = 0;
				}
			}
			else
			{
				if (countHorDistance > 0 && countVerDistance > 0)
				{
					countHorDistance = -1;
					countVerDistance = -1;
					return true;
				}
				else
				{
					countHorDistance = 1;
					countVerDistance = 1;
					return true;
				}
			}
		}
		break;
	case State::ElectricBat_FlyAttack:
	{
		if (pos.x > cap->GetPos().x) nx = -1;
		else nx = 1;

		if (std::abs(countHorDistanceA) < HOR_DISTANCE)
		{
			if (countHorDistanceA >= 0) {
				countHorDistanceA += MOVING_SPEED * GameTimer::Dt();
				vel.x = -MOVING_SPEED;
				vel.y = 0;
			}
			else {
				countHorDistanceA -= MOVING_SPEED * GameTimer::Dt();
				vel.x = MOVING_SPEED;
				vel.y = 0;
			}
		}
		else
		{
			if (std::abs(countVerDistanceA) < VER_DISTANCE)
			{
				if (countVerDistanceA >= 0) {
					countVerDistanceA += MOVING_SPEED * GameTimer::Dt();
					vel.y = MOVING_SPEED;
					vel.x = 0;
				}
				else {
					countVerDistanceA -= MOVING_SPEED * GameTimer::Dt();
					vel.y = -MOVING_SPEED;
					vel.x = 0;
					//return true;
				}
			}
			else
			{
				if (countHorDistanceA > 0 && countVerDistanceA > 0)
				{
					countHorDistanceA = -1;
					countVerDistanceA = -1;
				}
				else
				{
					countHorDistanceA = 1;
					countVerDistanceA = 1;
					return true;
				}
			}
		}
	}
	break;
	case State::ElectricBat_EndFly:
		vel.x = 0;
		vel.y = 0;
		if (animations.at(State::ElectricBat_EndFly).IsDoneCycle()) return true;
		break;
	case State::Explode:
		vel.x = 0;
		vel.y = 0;
		if (animations.at(State::Explode).IsDoneCycle()) return true;
		break;
	}
	default:
		break;
	}
	return false;
}

void ElectricBat::Update(float dt, const std::vector<GameObject*>& coObjects)
{
	if (pos.x > cap->GetPos().x) nx = 1;
	else nx = -1;

	OnAction();

	pos.x += vel.x*dt;
	pos.y += vel.y*dt;

	animations.at(curState).Update(dt);

	HandleCollisions(dt, coObjects);
}

void ElectricBat::TakeDamage(int damage)
{
	assert(damage > 0);
	if (isFlashing) return; // has just being damaged and is flashing, don't be too evil, give me time to recover please
	if (curState == State::ElectricBat_FlyAttack) return;

	health -= damage;
	if (health <= 0) {
		SetState(State::Explode);
	}
	else {
		OnFlashing(true);
	}
}

void ElectricBat::HandleCollisions(float dt, const std::vector<GameObject*>& coObjects)
{
	auto coEvents = CollisionDetector::CalcPotentialCollisions(*this, coObjects, dt);
	float _, __, ___, ____;

	if (coEvents.size()) CollisionDetector::FilterCollisionEvents(coEvents, _, __, ___, ____);

	for (auto& e : coEvents)
	{
		if (auto block = dynamic_cast<Block*>(e.pCoObj)) {

			switch (block->GetType())
			{
			case ClassId::RigidBlock:
				TakeDamage(health);
				return;
			}
		}
	}
}


