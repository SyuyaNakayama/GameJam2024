#include "Player.h"
#include <imgui.h>
#include <cmath>
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void Player::Move()
{
	// 移動速度を計算
	const float MOVE_SPD = Const(float, "PlayerMoveSpd");
	float moveDir = (float)operate->GetPush("Right") - operate->GetPush("Left");
	sprite->position += moveDir * MOVE_SPD;

	// 向きを変える
	if (moveDir < 0) { sprite->isFlipX = true; }
	else if (moveDir > 0) { sprite->isFlipX = false; }
}

void Player::Hide()
{
	sprite->isFlipY = true;
	if (hideTimer.Update())
	{
		Action = nullptr;
		sprite->isFlipY = false;
		isCanUseHide = false;
		hideCoolTimer = Const(int, "PlayerHideTime");
	}
}

void Player::Attack()
{
	attackArea->isInvisible = false;
	attackArea->position = sprite->position;
	attackArea->isFlipX = sprite->isFlipX;
	if (attackTimer.Update())
	{
		attackArea->isInvisible = true;
		Action = nullptr;
		isCanUseAttack = false;
		attackCoolTimer = Const(int, "PlayerAttackTime");
		DeleteCollider("attack");
	}
}

void Player::Initialize()
{
	sprites = Sprite::Create("background.png");
	sprites->size.x = WristerEngine::WIN_SIZE.x;
	sprites->size.y = WristerEngine::WIN_SIZE.y;
	sprites->isInvisible = false;
	// 初期化
	sprite = Sprite::Create("TestPlayer.png");
	sprite->size = Const(Vector2, "PlayerSize");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
	sprite->color = { 1.0f,1.0f,1.0f,1.0f };

	attackArea = Sprite::Create("white1x1.png");
	attackArea->size = Const(Vector2, "PlayerSize");
	attackArea->anchorPoint = { -0.5f,1.0f };
	attackArea->color = { 1.0f,0.5f,0.5f,1.0f };
	attackArea->isInvisible = true;

	// コライダーの設定
	collisionAttribute = CollisionAttribute::Player;
	collisionMask = CollisionMask::Player;
	AddCollider(sprite.get(), CollisionShapeType::Box, "body");

}

void Player::Update()
{
	Move();

	if (!isCanUseHide)
	{
		isCanUseHide = hideCoolTimer.Update();
	}
	if (!isCanUseAttack)
	{
		isCanUseAttack = attackCoolTimer.Update();
	}

	if (!Action)
	{
		// 地面に隠れる
		if (operate->GetTrigger("Down") && isCanUseHide)
		{
			Action = &Player::Hide;
			hideTimer = Const(int, "PlayerHideTime");
		}

		// 攻撃
		if (operate->GetTrigger("Attack") && isCanUseAttack)
		{
			Action = &Player::Attack;
			attackTimer = Const(int, "PlayerAttackTime");
			AddCollider(attackArea.get(), CollisionShapeType::Box, "attack");
		}
	}
	if (Action) { (this->*Action)(); }

	// スプライトの更新
	sprites->Update();
	sprite->Update();
	attackArea->Update();

	ImGui::Text("%d", colliders.size());
}

void Player::OnCollision([[maybe_unused]] WristerEngine::_2D::ColliderGroup* group)
{
}
