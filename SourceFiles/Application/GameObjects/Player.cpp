#include "Player.h"
#include <imgui.h>
#include <cmath>
#include "SceneManager.h"
#include "ShareValue.h"
#include <algorithm>
#include "AudioManager.h"

using namespace WristerEngine::_2D;

void Player::Move()
{
	// 移動速度を計算
	float moveDir = (float)operate->GetPush("Right") - operate->GetPush("Left");
	sprite->position += moveDir * Const(float, "PlayerMoveSpd");
	sprite->position.x = std::clamp(sprite->position.x, sprite->size.x / 2.0f,
		WristerEngine::WIN_SIZE.x - sprite->size.x / 2.0f);
	hide->position.x = sprite->position.x;
	// 向きを変える
	if (moveDir < 0) {
		sprite->isFlipX = true;
		walk->isFlipX = true;
		isAttack->isFlipX = true;
	}
	else if (moveDir > 0) {
		sprite->isFlipX = false;
		walk->isFlipX = false;
		isAttack->isFlipX = false;
	}
}

void Player::Hide()
{
	sprite->isFlipY = true;
	walk->isFlipY = true;
	hide->isFlipY = false;
	hide->isFlipX = sprite->isFlipX;
	if (hideTimer.Update())
	{
		Action = nullptr;
		sprite->isFlipY = false;
		walk->isFlipY = false;
		hide->isFlipY = true;
		isCanUseHide = false;
		hideCoolTimer = Const(int, "PlayerHideTime");
	}
}

void Player::Attack()
{
	isAttack->posOffset = { shakeBody(),shakeBody() };
	drill->posOffset = { shakeBody(),shakeBody() };
	attack->posOffset = { shakeBody(),shakeBody() };
	attack->isInvisible = false;
	drill->isInvisible = false;
	isAttack->isInvisible = false;
	sprite->isInvisible = true;
	walk->isInvisible = true;
	attack->position = sprite->position;
	drill->position = sprite->position;
	attack->isFlipX = sprite->isFlipX;
	drill->isFlipX = sprite->isFlipX;
	if (attackTimer.Update())
	{
		sprite->posOffset = {};
		attack->isInvisible = true;
		drill->isInvisible = true;
		isAttack->isInvisible = true;
		sprite->isInvisible = false;
		walk->isInvisible = false;
		Action = nullptr;
		isCanUseAttack = false;
		attackCoolTimer = Const(int, "PlayerAttackTime");
		DeleteCollider("attack");
		audio_attack->Stop();
	}
}

void Player::Initialize(const ObjectData& objData)
{
	// 初期化
	sprite = Sprite::Create("Player/drill_girl.png");
	sprite->size = Const(Vector2, "EffectSize");
	sprite->SetAnimation(4, 60);
	MyGameObject::Initialize(objData);
	shakeBody = { -2,2 };

	walk = Sprite::Create("Player/drill_girl_walk.png");
	walk->size = Const(Vector2, "WalkSize");
	walk->SetAnimation(6, 5);
	walk->anchorPoint = { 0.5f, 1.0f };
	walk->position = sprite->position;

	isAttack = Sprite::Create("Player/drill_girl_attack.png");
	isAttack->size = Const(Vector2, "PlayerSize");
	isAttack->anchorPoint = { 0.5f, 1.0f };
	isAttack->position = sprite->position;
	isAttack->isInvisible = true;

	attack = Sprite::Create("Player/attack_effect.png");
	attack->size = Const(Vector2, "EffectSize");
	attack->SetAnimation(4, 1);
	attack->anchorPoint = { -0.5f,1.0f };
	attack->color = { 1.0f,0.5f,0.5f,1.0f };
	attack->isInvisible = true;

	drill = Sprite::Create("Player/drill.png");
	drill->size = Const(Vector2, "PlayerSize");
	drill->anchorPoint = { -0.5f,1.0f };
	drill->isInvisible = true;

	hide = Sprite::Create("Player/dive.png");
	hide->SetAnimation(2, 30);
	hide->size = objData.size;
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

	// 音
	audio_attack = WristerEngine::AudioManager::Create("attack.mp3");
	audio_dive = WristerEngine::AudioManager::Create("dive.mp3");
}

void Player::InitializeUI() {
	//UIのスプライト初期化設定
	//攻撃アイコン
	ui_attack = Sprite::Create("UI/attack.png");
	ui_attack->size = Const(Vector2, "UIAllSize");
	ui_attack->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	ui_attack->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize"), WristerEngine::WIN_SIZE.y / 2 - Const(float, "PlayerSize"));
	ui_attack->anchorPoint = { 0.5f,1.0f };
	//潜るアイコン
	ui_dive = Sprite::Create("UI/dive.png");
	ui_dive->size = Const(Vector2, "UIAllSize");
	ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	ui_dive->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize"), WristerEngine::WIN_SIZE.y / 2 + Const(float, "PlayerSize"));
	ui_dive->anchorPoint = { 0.5f,1.0f };
	//攻撃アイコンのクールタイム
	ui_coolTime1 = Sprite::Create("UI/num.png");
	ui_coolTime1->size = Const(Vector2, "CoolTimeAllSize");
	ui_coolTime1->SetRect(Const(Vector2, "UIIconSize"), { 0, 0 });
	ui_coolTime1->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize"), WristerEngine::WIN_SIZE.y / 2 - Const(float, "PlayerSize"));
	ui_coolTime1->anchorPoint = { 0.5f,1.25f };

	//潜るアイコンのクールタイム
	ui_coolTime2 = Sprite::Create("UI/num.png");
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
	ui_key_space = Sprite::Create("UI/key.png");
	ui_key_space->size = Const(Vector2, "KeyAllSize");
	ui_key_space->SetRect(Const(Vector2, "UIIconSize"), { 0,0 });
	ui_key_space->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize") * 2, WristerEngine::WIN_SIZE.y / 2 - Const(float, "PlayerSize"));
	ui_key_space->anchorPoint = { 1.0f,1.0f };
	//UI DOWN
	ui_key_down = Sprite::Create("UI/key.png");
	ui_key_down->size = Const(Vector2, "KeyAllSize");
	ui_key_down->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
	ui_key_down->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize") * 2, WristerEngine::WIN_SIZE.y / 2 + Const(float, "PlayerSize"));
	ui_key_down->anchorPoint = { 1.0f,1.0f };
}

void Player::Update()
{
	Move();
	walk->position = sprite->position;
	isAttack->position = sprite->position;

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
			audio_dive->Play();
		}

		// 攻撃
		if (operate->GetTrigger("SceneChange") && isCanUseAttack)
		{
			ui_attack->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
			Action = &Player::Attack;
			attackTimer = Const(int, "PlayerAttackTime");
			AddCollider(attack.get(), CollisionShapeType::Box, "attack");
			coolTimeCountStartA = true;
			audio_attack->Play();
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
	sprite->Update();
	attack->Update();
	hide->Update();
	ui_attack->Update();
	ui_dive->Update();
	ui_coolTime1->Update();
	ui_coolTime2->Update();
	ui_key_space->Update();
	ui_key_down->Update();
	walk->Update();
	drill->Update();
	isAttack->Update();
}

void Player::Draw()
{
	//アニメーション切り替え
	if (operate->GetPush("Right") || operate->GetPush("Left")) {
		walk->Draw();
	}
	else {
		sprite->Draw();
	}
	isAttack->Draw();
	drill->Draw();
	attack->Draw();
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

void Player::OnCollision(WristerEngine::_2D::ColliderGroup* group)
{
	for (auto pair : collisionPair[0])
	{
		std::string pairName = group->GetColliderName(pair);
		// 敵との接触
		if (pairName == "body")
		{
			float move = Const(float, "PlayerMoveSpd");
			if (sprite->isFlipX) { move = -move; }
			sprite->position -= move;
		}
		if (!IsHide())
		{
			// ゴール
			if (pairName == "Goal")
			{
				ShareValue::GetInstance()->isGoal = true;
			}
			// ゲームオーバー
			if (pairName == "eyeBeam" || pairName == "attack")
			{
				ShareValue::GetInstance()->isGameOver = true;
			}
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

}