#include "Player.h"
#include <imgui.h>
#include <cmath>
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void Player::Move()
{
	// �ړ����x���v�Z
	float moveDir = (float)operate->GetPush("Right") - operate->GetPush("Left");
	sprite->position += moveDir * Const(float, "PlayerMoveSpd");
	hide->position.x = sprite->position.x;
	// ������ς���
	if (moveDir < 0) { sprite->isFlipX = true; }
	else if (moveDir > 0) { sprite->isFlipX = false; }
}

void Player::Hide()
{
	sprite->isFlipY = true;
	hide->isFlipY = false;
	if (hideTimer.Update())
	{
		Action = nullptr;
		sprite->isFlipY = false;
		hide->isFlipY = true;
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
	// ������
	sprite = Sprite::Create("TestPlayer.png");
	sprite->size = Const(Vector2, "PlayerSize");
	sprite->position.x = Const(float, "PlayerStartPosX");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
	sprite->color = { 1.0f,1.0f,1.0f,1.0f };

	attackArea = Sprite::Create("white1x1.png");
	attackArea->size = Const(Vector2, "PlayerSize");
	attackArea->anchorPoint = { -0.5f,1.0f };
	attackArea->color = { 1.0f,0.5f,0.5f,1.0f };
	attackArea->isInvisible = true;

	hide = Sprite::Create("Dive.png");
	hide->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	hide->size = Const(Vector2, "PlayerSize");
	hide->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	hide->anchorPoint = { 0.5f,1.0f };
	hide->isFlipY = true;

	//UI�̃X�v���C�g�������ݒ�
	ui_attack = Sprite::Create("ui_attack.png");
	ui_attack->size = Const(Vector2, "UIAllSize");
	ui_attack->SetRect(Const(Vector2,"UIIconSize"), {0,0});
	ui_attack->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float,"PlayerSize"), WristerEngine::WIN_SIZE.y / 2 - Const(float, "PlayerSize"));
	ui_attack->anchorPoint = { 0.5f,1.0f };

	ui_dive = Sprite::Create("ui_dive.png");
	ui_dive->size = Const(Vector2, "UIAllSize");
	ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	ui_dive->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize"), WristerEngine::WIN_SIZE.y / 2 + Const(float, "PlayerSize"));
	ui_dive->anchorPoint = { 0.5f,1.0f };

	// �R���C�_�[�̐ݒ�
	collisionAttribute = CollisionAttribute::Player;
	collisionMask = CollisionMask::Player;
	AddCollider(sprite.get(), CollisionShapeType::Box, "body");

	//�A�j���[�V��������
	animTime = Const(int, "PlayerAnimationTimer");
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

	UITimer();

	if (!Action)
	{
		// �n�ʂɉB���
		if (operate->GetTrigger("Down") && isCanUseHide)
		{
			ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
			Action = &Player::Hide;
			hideTimer = Const(int, "PlayerHideTime");
		}

		// �U��
		if (operate->GetTrigger("Attack") && isCanUseAttack)
		{
			ui_attack->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
			Action = &Player::Attack;
			attackTimer = Const(int, "PlayerAttackTime");
			AddCollider(attackArea.get(), CollisionShapeType::Box, "attack");
		}
	}
	if (Action) { (this->*Action)(); }

	Animations();

	// �X�v���C�g�̍X�V
	sprites->Update();
	sprite->Update();
	attackArea->Update();
	hide->Update();
	ui_attack->Update();
	ui_dive->Update();
}

void Player::OnCollision([[maybe_unused]] WristerEngine::_2D::ColliderGroup* group)
{
	for (auto pair : collisionPair[0])
	{
		if (group->GetColliderName(pair) == "body")
		{
			sprite->position -= Const(float, "PlayerMoveSpd");
		}
	}
}

void Player::UITimer() {
	if (!isCanUseAttack) {
		if (Const(int, "PlayerAttackTime") / 3 >= attackCoolTimer.GetRemainTime() && 1 < attackCoolTimer.GetRemainTime()) {
			ui_attack->SetRect(Const(Vector2, "UIIconSize"), { 96,0 });
		}
		else if (Const(int, "PlayerAttackTime") / 3 * 2 >= attackCoolTimer.GetRemainTime() && Const(int, "PlayerAttackTime") / 3 < attackCoolTimer.GetRemainTime()) {
			ui_attack->SetRect(Const(Vector2, "UIIconSize"), { 64,0 });
		}
		else if (Const(int, "PlayerAttackTime") / 3 * 2 < attackCoolTimer.GetRemainTime()) {
			ui_attack->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
		}
		else {
			ui_attack->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
		}
	}
	if (!isCanUseHide) {
		if (Const(int, "PlayerHideTime") / 3 >= hideCoolTimer.GetRemainTime() && 1 < hideCoolTimer.GetRemainTime()) {
			ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 96,0 });
		}
		else if (Const(int, "PlayerHideTime") / 3 * 2 >= hideCoolTimer.GetRemainTime() && Const(int, "PlayerHideTime") / 3 < hideCoolTimer.GetRemainTime()) {
			ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 64,0 });
		}
		else if (Const(int, "PlayerHideTime") / 3 * 2 < hideCoolTimer.GetRemainTime()) {
			ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
		}
		else {
			ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
		}
	}
}

void Player::Animations() {
	animTime--;
	if (animTime < 31) {
		hide->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	}
	else {
		hide->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
	}

	if (animTime < 0) {
		animTime = Const(int, "PlayerAnimationTimer");
	}
}
