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
	dive->position.x = sprite->position.x;
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

void Player::Dive()
{
	sprite->isFlipY = true;
	walk->isFlipY = true;
	dive->isFlipY = false;
	dive->isFlipX = sprite->isFlipX;
	if (diveTimer.Update())
	{
		Action = nullptr;
		sprite->isFlipY = false;
		walk->isFlipY = false;
		dive->isFlipY = true;
		isCanUseDive = false;
		diveCoolTimer = Const(int, "PlayerDiveTime");
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

	dive = Sprite::Create("Player/dive.png");
	dive->SetAnimation(2, 10);
	dive->size = objData.size;
	dive->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	dive->anchorPoint = { 0.5f,1.0f };
	dive->isFlipY = true;

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
	//UI_MOVE
	ui_move = Sprite::Create("UI/key_move.png");
	ui_move->size = Const(Vector2, "KeyMoveUISize");
	ui_move->position = Vector2(WristerEngine::WIN_SIZE.x - Const(float, "PlayerSize") * 2.5f, WristerEngine::WIN_SIZE.y / 2 + Const(float, "PlayerSize") * 1.25f);
	//テキストボックス
	textBox = Sprite::Create("UI/textbox.png");
	textBox->SetRect(Const(Vector2, "TextBoxSize"), { 0,0 });
	textBox->position.x = 40.0f;
	isExplanation = true;
}

void Player::Update()
{
	if (!isExplanation) {
		Move();
	}
	walk->position = sprite->position;
	isAttack->position = sprite->position;

	if (!isCanUseDive)
	{
		isCanUseDive = diveCoolTimer.Update();
	}
	if (!isCanUseAttack)
	{
		isCanUseAttack = attackCoolTimer.Update();
	}

	UITimer();
	if (!isExplanation) {
		if (!Action)
		{
			// 地面に隠れる
			if (operate->GetTrigger("Down") && isCanUseDive)
			{
				ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 32,0 });
				Action = &Player::Dive;
				diveTimer = Const(int, "PlayerDiveTime");
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

	Tutorial();

	// スプライトの更新
	sprite->Update();
	attack->Update();
	dive->Update();
	ui_attack->Update();
	ui_dive->Update();
	ui_coolTime1->Update();
	ui_coolTime2->Update();
	ui_key_space->Update();
	ui_key_down->Update();
	ui_move->Update();
	walk->Update();
	drill->Update();
	isAttack->Update();
	textBox->Update();
}

void Player::Draw()
{
	//アニメーション切り替え
	if (!isExplanation) {
		if (operate->GetPush("Right") || operate->GetPush("Left")) {
			walk->Draw();
		}
		else {
			sprite->Draw();
		}
	}
	else {
		sprite->Draw();
	}
	isAttack->Draw();
	drill->Draw();
	attack->Draw();
	dive->Draw();
	ui_attack->Draw();
	ui_dive->Draw();
	ui_key_space->Draw();
	ui_key_down->Draw();
	ui_move->Draw();
	if (coolTimeCountStartA) {
		ui_coolTime1->Draw();
	}
	if (coolTimeCountStartH) {
		ui_coolTime2->Draw();
	}
	if (isExplanation) {
		textBox->Draw();
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
		if (!IsDive())
		{
			// ゴール
			if (pairName == "Goal")
			{
				ShareValue::GetInstance()->isGoal = true;
			}
			// ゲームオーバー
			if (pairName == "eyeBeam" || pairName == "attack")
			{
				audio_attack->Stop();
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
	if (!isCanUseDive) {
		if (Const(int, "PlayerDiveTime") / 3 >= diveCoolTimer.GetRemainTime() && 1 < diveCoolTimer.GetRemainTime()) {
			ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 96,0 });
		}
		else if (Const(int, "PlayerDiveTime") / 3 * 2 >= diveCoolTimer.GetRemainTime() && Const(int, "PlayerDiveTime") / 3 < diveCoolTimer.GetRemainTime()) {
			ui_dive->SetRect(Const(Vector2, "UIIconSize"), { 64,0 });
		}
		else if (Const(int, "PlayerDiveTime") / 3 * 2 < diveCoolTimer.GetRemainTime()) {
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

void Player::Tutorial() {
	if (GetNowScene() != Scene::Tutorial) {
		isExplanation = false;
	}
	else {
		if (operate->GetTrigger("SceneChange")) {
			page += 1.0f;
			textBox->SetRect(Const(Vector2,"TextBoxSize"), {Const(float,"PageSize") * page,0});
			if (page > 2.0f) {
				isExplanation = false;
			}
		}
	}
}
