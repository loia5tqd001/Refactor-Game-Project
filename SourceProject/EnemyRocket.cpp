#include "pch.h"
#include "EnemyRocket.h"
#include "Captain.h"
#include "BulletEnemyRocket.h"
#include "CharlestonScene.h"
#include"PittsburghScene.h"
EnemyRocket::EnemyRocket(Behaviors behavior, Vector2 spawnPos, Captain* cap, Grid* grid) :
	Enemy(behavior, Data{}, State::EnemyRocket_BeforeExplode, 3, spawnPos, grid),
	cap(cap)
{
	if (typeid(SceneManager::Instance().GetCurScene()) != typeid(PittsburghScene{}))
	{
		animations.emplace(State::EnemyRocket_BeforeExplode, Animation(SpriteId::EnemyRocket_BeforeExplode, 0.2f));
		animations.emplace(State::EnemyRocket_Walking, Animation(SpriteId::EnemyRocket_Walking, 0.09f));
		if (behavior == Behaviors::EnemyRocket_BackAndForth)
		{
			animations.emplace(State::EnemyRocket_Stand, Animation(SpriteId::EnemyRocket_Stand, 0.55f));
			animations.emplace(State::EnemyRocket_Sitting, Animation(SpriteId::EnemyRocket_Sitting, 0.55f));
		}
		else
		{
			animations.emplace(State::EnemyRocket_Stand, Animation(SpriteId::EnemyRocket_Stand, 0.75f));
			animations.emplace(State::EnemyRocket_Sitting, Animation(SpriteId::EnemyRocket_Sitting, 0.75f));
		}
	}
	else
	{
		animations.emplace(State::EnemyRocket_BeforeExplode, Animation(SpriteId::EnemyRocket_BeforeExplode_BW, 0.2f));
		animations.emplace(State::EnemyRocket_Walking, Animation(SpriteId::EnemyRocket_Walking_BW, 0.09f));
		if (behavior == Behaviors::EnemyRocket_BackAndForth)
		{
			animations.emplace(State::EnemyRocket_Stand, Animation(SpriteId::EnemyRocket_Stand_BW, 0.55f));
			animations.emplace(State::EnemyRocket_Sitting, Animation(SpriteId::EnemyRocket_Sitting_BW, 0.55f));
		}
		else
		{
			animations.emplace(State::EnemyRocket_Stand, Animation(SpriteId::EnemyRocket_Stand_BW, 0.75f));
			animations.emplace(State::EnemyRocket_Sitting, Animation(SpriteId::EnemyRocket_Sitting_BW, 0.75f));
		}
	}

	if (behavior == Behaviors::EnemyRocket_Ambush) nx = -1;
	else nx = - cap->GetNx();
	groundPosY = spawnPos.y;
	SetState(State::EnemyRocket_Walking);
	switch (behavior)
	{
		case Behaviors::EnemyRocket_ShootStraight:
			break;
		case Behaviors::EnemyRocket_ShootCross:
			rocketType = 1;
			break;
		case Behaviors::EnemyRocket_BackAndForth:
			isInJumpBackNForth = (pos.y + GetHeight() < 437.0f && pos.y > 200.0f);
			if (isInJumpBackNForth) SetState(State::EnemyRocket_Sitting);
			else SetState(State::EnemyRocket_Walking);
			rocketType = 2;
			break;
		case Behaviors::EnemyRocket_Ambush:
			break;
		default:
			AssertUnreachable();
	}
}

void EnemyRocket::OnBehaviorShoot()
{
	assert(behavior == Behaviors::EnemyRocket_ShootStraight ||
	       behavior == Behaviors::EnemyRocket_ShootCross);

	nx = cap->GetPos().x > pos.x ? 1 : -1;
	// Walk -> Stand&Shoot -> Sit&Shoot-> Stand&Shoot -> Repeat
	if (!jumpOnce) {
		if (vel.x != 0) {
			if (cap->IsShieldOn() == false && cap->getDirectionWhenThrow()*nx < 0) {
				DogdeShield = true;
			}
			if (DogdeShield) {
				if (dynamic_cast<CharlestonScene*>(&SceneManager::Instance().GetCurScene())) {
					Jump(groundPosY, 60.0f);
				}
				else {
					Jump(groundPosY, 33.0f);
				}
			}
		}
	}
	if (animations.at(curState).IsDoneCycle())
	switch (curState)
	{
		case State::EnemyRocket_Walking:
			if (!jumpOnce) {
				if (cap->IsShieldOn() == false && cap->getDirectionWhenThrow()) {
					DogdeShield = true;
				}
				if (DogdeShield) {
					if (dynamic_cast<CharlestonScene*>(&SceneManager::Instance().GetCurScene())) {
						Jump(groundPosY, 60.0f);
					}
					else {
						Jump(groundPosY, 33.0f);
					}
				}
			}
			if (++countWalkStep >= 4) 
				SetState(State::EnemyRocket_Stand);
			break;

		case State::EnemyRocket_Stand:
			if (!justShoot) {
				SpawnRocket();
				justShoot = true;
			}
			else {
				SetState(State::EnemyRocket_Sitting);
				justShoot = false;
			}
			break;

		case State::EnemyRocket_Sitting:
			if (DogdeShield) {
				Jump(groundPosY, 60.0f);
				return;
			}
			if (!justShoot) {
				SpawnRocket();
				justShoot = true;
			}
			else {
				SetState(State::EnemyRocket_Stand);
				justShoot = false;
			}
			break;

		case State::EnemyRocket_BeforeExplode:
		case State::Explode:
		case State::Destroyed:
			break;
		default:
			AssertUnreachable();
	}
}

void EnemyRocket::BackAndForthJump()
{
	static constexpr float JUMP_HOR = 20.0f;
	static constexpr float GRAVITY = 140.0f;

	vel.x = -JUMP_HOR;

	if (bnf_dirY == -1) // jump up
	{
		pos.x += vel.x * GameTimer::Dt() * 2;
		pos.y -= GRAVITY * GameTimer::Dt();
		if (pos.y < 275.0f) // 270 is the highest position of jump
			bnf_dirY = 0;
	}
	else if (bnf_dirY == 0) // kinda holding in the air
	{
		bnf_accelerator += 1.0f * GameTimer::Dt();
		pos.x += vel.x * GameTimer::Dt();
		if (pos.y > 275.0f) 
			pos.y -= GRAVITY * GameTimer::Dt() * 0.25f - bnf_accelerator;
		else if (pos.y < 270.0f)
			pos.y += GRAVITY * GameTimer::Dt() * 0.25f - bnf_accelerator;
		else
			bnf_dirY = 1; // falling
	}
	else // falling
	{
		pos.x += vel.x * GameTimer::Dt() * 2.0f;
		pos.y += GRAVITY * GameTimer::Dt() + bnf_accelerator;
		if (pos.y + GetHeight() >= 437.0f) // 437 is the ground
		{
			pos.y = 437.0f - GetHeight(); 
			VisibleObject::SetState(State::EnemyRocket_Sitting);
			if (animations.at(State::EnemyRocket_Sitting).IsDoneCycle())
			{
				lastState = State::EnemyRocket_Walking;
				SetState(State::EnemyRocket_Stand);
				justShoot = false;
				isLastForth = !isLastForth;
				isInJumpBackNForth = false;
			}
		}
	}
}

void EnemyRocket::OnBehaviorBackAndForth()
{
	assert(behavior == Behaviors::EnemyRocket_BackAndForth);
	assert(rocketType == 2); // straight rocket only

	if (isInJumpBackNForth) {
		BackAndForthJump();
		return;
	}

	if (animations.at(curState).IsDoneCycle())
	switch (curState)
	{
		case State::EnemyRocket_Walking:
			if (++countWalkStep >= 4) {
				lastState = State::EnemyRocket_Walking;
				SetState(State::EnemyRocket_Stand);
				countWalkStep = 0;
				isLastForth = !isLastForth;
			}
			break;

		case State::EnemyRocket_Stand:
			if (lastState == State::EnemyRocket_Sitting) 
				SetState(State::EnemyRocket_Walking);
			else
				SetState(State::EnemyRocket_Sitting);
			break;

		case State::EnemyRocket_Sitting:
			if (!justShoot) {
				SpawnRocket();
				justShoot = true;
			}
			else {
				lastState = State::EnemyRocket_Sitting;
				SetState(State::EnemyRocket_Stand);
				justShoot = false;
			}
			break;

		case State::EnemyRocket_BeforeExplode:
		case State::Explode:
		case State::Destroyed:
			break;
		default:
			AssertUnreachable();
	}
}

void EnemyRocket::OnBehaviorAmbush()
{
	// Walking left only
	assert(behavior == Behaviors::EnemyRocket_Ambush);
	assert(curState == State::EnemyRocket_Walking ||
		   curState == State::EnemyRocket_BeforeExplode ||
		   curState == State::Explode ||
		   curState == State::EnemyRocket_Sitting ||
		   curState == State::Destroyed);
	if (cap->IsShieldOn() == false && cap->getDirectionWhenThrow()*nx < 0 && cap->GetPos().x < pos.x) {
		DogdeShield = true;
	}
	if (DogdeShield) {
		if (dynamic_cast<CharlestonScene*>(&SceneManager::Instance().GetCurScene())) {
			Jump(groundPosY, 60.0f);
		}
		else {
			Jump(groundPosY, 33.0f);
		}
	}
	//else
	//{
	//	pos.x += vel.x * GameTimer::Dt(); //HACK: to slow, need another buff speed
	//}
}
void EnemyRocket::Jump(float posy, float height) //use this function in any height, just give it the ground pos and the height to jump
{
	if (health <= 0) return;
	static constexpr float JUMP_HOR = 55.0f;
	static constexpr float GRAVITY = 140.0f;

	VisibleObject::SetState(State::EnemyRocket_Sitting);
	vel.x = nx*JUMP_HOR;
	if (dirYJump == -1) // jump up
	{
		pos.y -= GRAVITY * GameTimer::Dt();// - accelerator;
		if (pos.y < posy - height) {
			dirYJump = 0;
		}
	}
	else if (dirYJump == 0) // kinda holding in the air
	{
		accelerator += 0.01f * GameTimer::Dt();
		pos.y += GRAVITY * GameTimer::Dt();
		if (pos.y > posy - height + 5) {
			dirYJump = 1; // falling
		}
	}
	else // falling
	{
		pos.y += GRAVITY * GameTimer::Dt() + accelerator;
		if (pos.y >= posy + 9) //why 9? it is the different in 2 sprite
		{
			pos.y = posy + 9;
			VisibleObject::SetState(State::EnemyRocket_Walking);
			DogdeShield = false;
			jumpOnce = true;
			vel.x = nx * WALKING_SPEED;
		}
	}
	//pos.x += vel.x * 2 * GameTimer::Dt();
}

void EnemyRocket::SetState(State state)
{
	VisibleObject::SetState(state); 

	switch (state)
	{
	case State::EnemyRocket_Stand:
		vel.x = 0.0f;
		break;
	case State::EnemyRocket_Walking:
		vel.x = (isLastForth ? -1 : 1) * nx * WALKING_SPEED;
		break;
	case State::EnemyRocket_Sitting:
		vel.x = 0.0f;
		break;
	case State::EnemyRocket_BeforeExplode:
		vel.x = -nx * FALL_BACK;
		break;
	case State::Explode:
		vel.x = 0;
		break;
	}
}

void EnemyRocket::SpawnRocket()
{
	if (isFlashing) return;
	if (curState == State::Explode || curState == State::EnemyRocket_BeforeExplode) return;
	if (curState == State::EnemyRocket_Sitting)
	{
		auto bulletPos = pos + Vector2{ 15.0f, -4.0f };
		grid->SpawnObject(std::make_unique<BulletEnemyRocket>(nx, rocketType, this, bulletPos));
		Sounds::PlayAt(SoundId::BulletNormal);
	}
	else if (curState == State::EnemyRocket_Stand)
	{
		auto bulletPos = pos + Vector2{ 14.0f, -4.0f };
		grid->SpawnObject(std::make_unique<BulletEnemyRocket>(nx, rocketType, this, bulletPos));
		Sounds::PlayAt(SoundId::BulletNormal);
	}
}

void EnemyRocket::Update(float dt, const std::vector<GameObject*>& coObjects)
{
	UpdateAnimation(dt);

	if (curState == State::Explode) return;
	switch (behavior)
	{
		case Behaviors::EnemyRocket_ShootStraight:
		case Behaviors::EnemyRocket_ShootCross:
			OnBehaviorShoot();
			break;
		case Behaviors::EnemyRocket_BackAndForth:
			OnBehaviorBackAndForth();
			break;
		case Behaviors::EnemyRocket_Ambush:
			OnBehaviorAmbush();
			break;
		default:
			AssertUnreachable();
	}

	pos.x += vel.x*dt;
	pos.y += vel.y*dt;
}
