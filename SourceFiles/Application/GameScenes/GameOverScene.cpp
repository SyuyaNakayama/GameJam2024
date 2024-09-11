#include "GameOverScene.h"
#include "SceneManager.h"
#include "ShareValue.h"

using namespace WristerEngine::_2D;

void GameOverScene::Initialize()
{
	ShareValue::GetInstance()->isGameOver = false;
	// UI描画クラスの初期化
	uiDrawer = std::make_unique<UIDrawerGameOverScene>();
	uiDrawer->Initialize();
}

void GameOverScene::Update()
{
	if (operate->GetTrigger("SceneChange")) {
		sceneManager->ChangeScene(Scene::Title);
	}
	// UI描画
	uiDrawer->Update();
}

void UIDrawerGameOverScene::Initialize()
{
	sprites["death"] = Sprite::Create("GameOver.png");
	sprites["death"]->size *= 3.0f;
	sprites["death"]->SetCenterPos();
	sprites["death"]->SetCenterAnchor();
}
