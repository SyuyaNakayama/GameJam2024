#include "GamePlayScene.h"
#include "ShareValue.h"
#include "CollisionManager.h"

using namespace WristerEngine::_2D;

void GamePlayScene::Initialize()
{
	stage.Initialize();
	// UI�`��N���X�̏�����
	uiDrawer = std::make_unique<UIDrawerGamePlayScene>();
	uiDrawer->Initialize();
}

void GamePlayScene::Update()
{
	// ���Z�b�g
	if (OperateConfig::GetInstance()->GetTrigger("Pause"))
	{
		sceneManager->ChangeScene(Scene::Play);
		WristerEngine::Constant::GetInstance()->LoadConstants();
		return;
	}

	if (ShareValue::GetInstance()->isGoal)
	{
		ShareValue::GetInstance()->isGoal = false;
		sceneManager->ChangeScene(Scene::Clear);
		return;
	}

	if (ShareValue::GetInstance()->isGameOver)
	{
		sceneManager->ChangeScene(Scene::GameOver);
		return;
	}



	stage.Update();
	// UI�`��
	uiDrawer->Update();
}

void GamePlayScene::Draw()
{
	stage.Draw();
	// UI�`��
	uiDrawer->Draw();
}

void UIDrawerGamePlayScene::Initialize()
{
	// �n�ʂ�UI�̏�����
	sprites["Ground"] = Sprite::Create("brick.png");
	std::unique_ptr<Sprite>& s = sprites["Ground"];
	s->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	s->textureSize.x *= (WristerEngine::WIN_SIZE.x / s->size.x);
	s->textureSize.y *= (Const(float, "GroundHeight") / s->size.y);
	s->size.x = WristerEngine::WIN_SIZE.x;
	s->size.y = Const(float, "GroundHeight");
}
