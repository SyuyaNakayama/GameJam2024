#include "Player.h"
#include <imgui.h>
#include <cmath>
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void Player::Move()
{
	// �ړ����x���v�Z
	const float MOVE_SPD = Const(float, "PlayerMoveSpd");
	float moveDir = (float)operate->GetPush("Right") - operate->GetPush("Left");
	sprite->position += moveDir * MOVE_SPD;

	// ������ς���
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
	}
}

void Player::Attack()
{
	attackArea->isInvisible = false;
	attackArea->position = sprite->position;
	attackArea->isFlipX = sprite->isFlipX;
	if (hideTimer.Update())
	{
		attackArea->isInvisible = true;
		Action = nullptr;
	}
}

void Player::Initialize()
{
	// ������
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
}

void Player::Update()
{
	Move();

	if (!Action)
	{
		// �n�ʂɉB���
		if (operate->GetTrigger("Down"))
		{
			Action = &Player::Hide;
			hideTimer = Const(int, "PlayerHideTime");
		}

		// �U��
		if (operate->GetTrigger("Attack"))
		{
			Action = &Player::Attack;
			hideTimer = Const(int, "PlayerAttackTime");
		}
	}
	if (Action) { (this->*Action)(); }

	// �X�v���C�g�̍X�V
	sprite->Update();
	attackArea->Update();
}
