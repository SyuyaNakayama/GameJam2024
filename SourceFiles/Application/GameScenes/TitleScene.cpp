#include "TitleScene.h"
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void TitleScene::Initialize()
{
	// UI•`‰æƒNƒ‰ƒX‚Ì‰Šú‰»
	uiDrawer = std::make_unique<UIDrawerTitleScene>();
	uiDrawer->Initialize();
}

void TitleScene::Update()
{
	if (operate->GetTrigger("SceneChange")) {
		sceneManager->ChangeScene(Scene::Play);
	}
	// UI•`‰æ
	uiDrawer->Update();
}

void UIDrawerTitleScene::Initialize()
{
	sprites["title"] = Sprite::Create("Title.png");
	sprites["title"]->size *= 2.0f;
	sprites["title"]->SetCenterPos();
	sprites["title"]->SetCenterAnchor();
}