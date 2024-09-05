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

void Player::Initialize()
{
	// ������
	sprite = Sprite::Create("TestPlayer.png");
	sprite->size = Const(Vector2, "PlayerSize");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
	sprite->color = { 1.0f,1.0f,1.0f,1.0f };
}

void Player::Update()
{
	Move();

	// �n�ʂɉB���
	if (operate->GetTrigger("Down")) 
	{
		Action = &Player::Hide; 
		hideTimer = Const(int, "PlayerHideTime");
	}
	if (Action) { (this->*Action)(); }
	else
	{
		Vector2 toEyePlayer = sprite->position - Const(Vector2, "EnemyBeamStartPos");
		float dot = Dot({ -1,0 }, Normalize(toEyePlayer));
		Angle theta = Half(PI) - std::acos(dot);

		theta = std::abs(theta - Angle(60));

		// �Q�[���I�[�o�[
		if (theta <= Angle(4)) { WristerEngine::SceneManager::GetInstance()->ChangeScene(Scene::GameOver); }
	}

	// �X�v���C�g�̍X�V
	sprite->Update();
}
