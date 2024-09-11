#include "Player.h"
#include <imgui.h>
#include <cmath>
#include "SceneManager.h"
#include "ShareValue.h"

using namespace WristerEngine::_2D;

void Player::Move()
{
	// 移動速度を計算
	float moveDir = (float)operate->GetPush("Right") - operate->GetPush("Left");
	sprite->position += moveDir * Const(float, "PlayerMoveSpd");
	hide->position.x = sprite->position.x;
	// 向きを変える
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
	// 初期化
	sprite = Sprite::Create("player.png");
	sprite->size = Const(Vector2, "PlayerSize");
	sprite->position.x = Const(float, "PlayerStartPosX");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
	sprite->color = { 1.0f,1.0f,1.0f,1.0f };

	attackArea = Sprite::Create("attack_effect.png");
	attackArea->size = Const(Vector2, "EffectSize");
	attackArea->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	attackArea->anchorPoint = { -0.5f,1.0f };
	attackArea->color = { 1.0f,0.5f,0.5f,1.0f };
	attackArea->isInvisible = true;

	hide = Sprite::Create("Dive.png");
	hide->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	hide->size = Const(Vector2, "PlayerSize");
	hide->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	hide->anchorPoint = { 0.5f,1.0f };
	hide->isFlipY = true;

	InitializeUI();

	// コライダーの設定
	collisionAttribute = CollisionAttribute::Player;
	collisionMask = CollisionMask::Player;
	AddCollider(sprite.get(), CollisionShapeType::Box, "body");

	//アニメーション時間
	animTime = Const(int, "PlayerAnimationTimer");
}

void Player::InitializeUI() {
	//UIのスプライト初期化設定
	//攻撃アイコン
	ui_attack = Sprite::Create("ui_attack.png");
	ui_attack->size = Const(Vector2, "UIAllSize");
	ui_attack->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	ui_attack->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize"), WristerEngine::WIN_SIZE.y / 2 - Const(float, "PlayerSize"));
	ui_attack->anchorPoint = { 0.5f,1.0f };
	//潜るアイコン
	ui_dive = Sprite::Create("ui_dive.png");
	ui_dive->size = Const(Vector2, "UIAllSize");
	ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	ui_dive->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize"), WristerEngine::WIN_SIZE.y / 2 + Const(float, "PlayerSize"));
	ui_dive->anchorPoint = { 0.5f,1.0f };
	//攻撃アイコンのクールタイム
	ui_coolTime1 = Sprite::Create("num.png");
	ui_coolTime1->size = Const(Vector2, "CoolTimeAllSize");
	ui_coolTime1->SetRect(Const(Vector2, "UIIconSize"), { 0, 0 });
	ui_coolTime1->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize"), WristerEngine::WIN_SIZE.y / 2 - Const(float, "PlayerSize"));
	ui_coolTime1->anchorPoint = { 0.5f,1.25f };
	
	//潜るアイコンのクールタイム
	ui_coolTime2 = Sprite::Create("num.png");
	ui_coolTime2->size = Const(Vector2, "CoolTimeAllSize");
	ui_coolTime2->SetRect(Const(Vector2, "UIIconSize"), { 0, 0 });
	ui_coolTime2->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize"), WristerEngine::WIN_SIZE.y / 2 + Const(float, "PlayerSize"));
	ui_coolTime2->anchorPoint = { 0.5f,1.25f };
	//クールタイムカウントダウン
	coolCutPosA = 1.0f;
	coolCutPosH = 3.0f;
	countCoolTimeA = 0;
	countCoolTimeH = 0;;
	coolTimeCountStartA = false;
	coolTimeCountStartH = false;
	//UI SPACE
	ui_key_space = Sprite::Create("key.png");
	ui_key_space->size = Const(Vector2, "KeyAllSize");
	ui_key_space->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	ui_key_space->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize") * 2, WristerEngine::WIN_SIZE.y / 2 - Const(float, "PlayerSize"));
	ui_key_space->anchorPoint = { 1.0f,1.0f };
	//UI DOWN
	ui_key_down = Sprite::Create("key.png");
	ui_key_down->size = Const(Vector2, "KeyAllSize");
	ui_key_down->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
	ui_key_down->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize") * 2, WristerEngine::WIN_SIZE.y / 2 + Const(float, "PlayerSize"));
	ui_key_down->anchorPoint = { 1.0f,1.0f };
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
		// 地面に隠れる
		if (operate->GetTrigger("Down") && isCanUseHide)
		{
			ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
			Action = &Player::Hide;
			hideTimer = Const(int, "PlayerHideTime");
			coolTimeCountStartH = true;
		}

		// 攻撃
		if (operate->GetTrigger("SceneChange") && isCanUseAttack)
		{
			ui_attack->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
			Action = &Player::Attack;
			attackTimer = Const(int, "PlayerAttackTime");
			AddCollider(attackArea.get(), CollisionShapeType::Box, "attack");
			coolTimeCountStartA = true;
		}
	}
	if (Action) { (this->*Action)(); }

	if (coolTimeCountStartH) {
		countCoolTimeH++;
		if (countCoolTimeH >= 60) {
			countCoolTimeH = 0;
			coolCutPosH -= 1.0f;
		}
	}
	if (coolTimeCountStartA) {
		countCoolTimeA++;
		if (countCoolTimeA >= 60) {
			countCoolTimeA = 0;
			coolCutPosA -= 1.0f;
		}
	}

	Animations();

	// スプライトの更新
	sprites->Update();
	sprite->Update();
	attackArea->Update();
	hide->Update();
	ui_attack->Update();
	ui_dive->Update();
	ui_coolTime1->Update();
	ui_coolTime2->Update();
	ui_key_space->Update();
	ui_key_down->Update();
}

void Player::Draw() 
{ 
	sprites->Draw();
	sprite->Draw();
	attackArea->Draw();
	hide->Draw(); 
	ui_attack->Draw();
	ui_dive->Draw(); 
	ui_key_space->Draw();
	ui_key_down->Draw();
	if (coolTimeCountStartA) {
		ui_coolTime1->Draw();
	}
	if (coolTimeCountStartH) {
		ui_coolTime2->Draw();
	}
}

void Player::OnCollision([[maybe_unused]] WristerEngine::_2D::ColliderGroup* group)
{
	for (auto pair : collisionPair[0])
	{
		// 敵との接触
		if (group->GetColliderName(pair) == "body")
		{
			sprite->position -= Const(float, "PlayerMoveSpd");
		}
		// ゴール
		if (group->GetColliderName(pair) == "Goal" && !IsHide())
		{
			ShareValue::GetInstance()->isGoal = true;
		}
	}
}

void Player::UITimer() {
	if (coolTimeCountStartA) {
		ui_coolTime1->SetRect(Const(Vector2, "UIIconSize"), { coolCutPosA * 32,0 });
	}
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
			coolCutPosA = 1.0f;
			countCoolTimeA = 0;
			coolTimeCountStartA = false;

		}
	}
	if (coolTimeCountStartH) {
		ui_coolTime2->SetRect(Const(Vector2, "UIIconSize"), { coolCutPosH * 32,0 });
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
			coolTimeCountStartH = false;
			countCoolTimeH = 0;
			coolCutPosH = 3.0f;
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