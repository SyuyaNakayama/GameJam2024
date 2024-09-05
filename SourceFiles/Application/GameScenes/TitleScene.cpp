#include "TitleScene.h"

using namespace WristerEngine::_2D;

void TitleScene::Initialize()
{
	// UI描画クラスの初期化
	uiDrawer = std::make_unique<UIDrawerTitleScene>();
	uiDrawer->Initialize();
}

void TitleScene::Update()
{
	// UI描画
	uiDrawer->Update();
}

void UIDrawerTitleScene::Initialize()
{
	sprites["white"] = Sprite::Create("white1x1.png");
	sprites["white"]->SetCenterPos();
	sprites["white"]->SetCenterAnchor();
	sprites["white"]->size = constant->GetConstant<Vector2>("WhitePicSize");
}