#include "TitleScene.h"
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void TitleScene::Initialize()
{
	// UI描画クラスの初期化
	uiDrawer = std::make_unique<UIDrawerTitleScene>();
	uiDrawer->Initialize();
}

void TitleScene::Update()
{
	if (operate->GetTrigger("SceneChange")) {
		sceneManager->ChangeScene(Scene::Tutorial);
	}
	// UI描画
	uiDrawer->Update();
}

void UIDrawerTitleScene::Initialize()
{
	sprites["title"] = Sprite::Create("Title.png");
	sprites["title"]->size *= 2.0f;
	sprites["title"]->SetCenterPos();
	sprites["title"]->SetCenterAnchor();
}