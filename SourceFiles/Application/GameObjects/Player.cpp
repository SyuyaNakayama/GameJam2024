#include "Player.h"
#include <imgui.h>
#include <cmath>
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void Player::Move()
{
	const float MOVE_SPD = Const(float, "PlayerMoveSpd");
	float moveDir = (float)operate->GetPush("Right") - operate->GetPush("Left");
	sprite->position += moveDir * MOVE_SPD;
}

void Player::Initialize()
{
	// 初期化
	sprite = Sprite::Create("TestPlayer.png");
	sprite->size = Const(Vector2, "PlayerSize");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
	sprite->color = { 1.0f,1.0f,1.0f,1.0f };
}

void Player::Update()
{
	Move();
	Vector2 toEyePlayer = sprite->position - Const(Vector2, "EnemyBeamStartPos");
	float dot = Dot({ -1,0 }, Normalize(toEyePlayer));
	Angle theta = Half(PI) - std::acos(dot);

	theta = std::abs(theta - Angle(60));
	if (theta <= Angle(4)) { WristerEngine::SceneManager::GetInstance()->ChangeScene(Scene::GameOver); }
	// スプライトの更新
	sprite->Update();
}
