#include "GameOverScene.h"
#include "SceneManager.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void GameOverScene::Initialize()
{
	// UI•`‰æƒNƒ‰ƒX‚Ì‰Šú‰»
	uiDrawer = std::make_unique<UIDrawerGameOverScene>();
	uiDrawer->Initialize();
}

void GameOverScene::Update()
{
	if (operate->GetTrigger("SceneChange")) {
		sceneManager->ChangeScene(Scene::Title);
	}
	// UI•`‰æ
	uiDrawer->Update();
}

void UIDrawerGameOverScene::Initialize()
{
	sprites["death"] = Sprite::Create("GameOver.png");
	sprites["death"]->size *= 4.0f;
	sprites["death"]->SetCenterPos();
	sprites["death"]->SetCenterAnchor();
}
