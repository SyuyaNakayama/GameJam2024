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
	sprites["white"] = Sprite::Create("white1x1.png");
	sprites["white"]->SetCenterPos();
	sprites["white"]->SetCenterAnchor();
	sprites["white"]->size = constant->GetConstant<Vector2>("WhitePicSize");
}