#include "Enemy.h"
#include <imgui.h>

using namespace WristerEngine::_2D;

void Enemy::Initialize(const ObjectData& objData)
{
	// 敵
	sprite = Sprite::Create("Enemy/pillar.png");
	BaseEnemy::Initialize(objData);
	sprite->isFlipX = objData.e_flip;

	// ビーム
	eyeBeam = Sprite::Create("Enemy/EyeBeam.png");
	eyeBeam->size.y = 1000;
	eyeBeam->position = objData.e_eyePos;
	eyeBeam->anchorPoint = { 0.5f,0.0f };

	beamRotEasing.Initialize(120, WristerEngine::Easing::Type::Linear);
	beamRotEasing.SetLoop(30);
	beamAngleRange = objData.e_angleRange;

	Option option{};
	option.fov = Const(int, "EnemyEyeFOV");
	AddCollider(eyeBeam.get(), CollisionShapeType::TwoRay, "eyeBeam", &option);

	audio_eyeMove = WristerEngine::AudioManager::Create("enemyEyeMove.mp3");

	eyeBeam->rotation = Angle(beamAngleRange[0]);
}

void Enemy::Update()
{
	eyePreRot = eyeBeam->rotation;

	eyeBeam->rotation = Angle(beamAngleRange[1] - beamAngleRange[0]) *
		beamRotEasing.Update() + Angle(beamAngleRange[0]);

	isEyeMove = false;
	if (std::abs(eyeBeam->rotation - eyePreRot) >= 1e-4f) { isEyeMove = true; }

	if (!isPreEyeMove && isEyeMove) { audio_eyeMove->Play(); }

	isPreEyeMove = isEyeMove;

	// スプライトの更新
	eyeBeam->Update();
	BaseEnemy::Update();
}

void Enemy::Draw()
{
	BaseEnemy::Draw();
	eyeBeam->Draw();
}

void DarumaEnemy::Initialize(const ObjectData& objData)
{
	sprite = Sprite::Create("Enemy/pillar.png");
	BaseEnemy::Initialize(objData);
	sprite->color = { 1.0f,0.5f,0.5f,1.0f };
	sprite->isFlipX = true;

	whiteBody = Sprite::Create("Enemy/pillar_white.png");
	BaseEnemy::Initialize(objData);
	whiteBody->position = sprite->position;
	whiteBody->anchorPoint = sprite->anchorPoint;
	whiteBody->size = sprite->size;
	whiteBody->color.a = 0;
	whiteBody->isFlipX = true;
	whiteAlphaEasing.Initialize(objData.e_attackInterval / 10, WristerEngine::LoopEasing::Type::Cos);

	attack = Sprite::Create("white1x1.png");
	attack->size = WristerEngine::WIN_SIZE;
	attack->isInvisible = true;
	attackTimer = objData.e_attackTime;
	attackInterval = objData.e_attackInterval;
}

void DarumaEnemy::Update()
{
	whiteBody->posOffset = sprite->posOffset;
	if (attackInterval.Update())
	{
		attack->isInvisible = false;
		AddCollider(attack.get(), CollisionShapeType::Box, "attack");
		sprite->isFlipX = false;
		sprite->posOffset.x = 0;
	}
	else
	{
		if (attackInterval.GetRemainTimeRate() <= 0.2f)
		{
			whiteBody->color.a = 1.0f - whiteAlphaEasing.Update();
		}
	}
	if (!attack->isInvisible)
	{
		if (attackTimer.Update())
		{
			sprite->isFlipX = true;
			attack->isInvisible = true;
			DeleteCollider("attack");
		}
	}

	attack->Update();
	whiteBody->Update();
	BaseEnemy::Update();
}

void DarumaEnemy::Draw()
{
	attack->Draw();
	BaseEnemy::Draw();
	whiteBody->Draw();
}
