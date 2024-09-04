#include "TitleScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void TitleScene::Initialize()
{
	uiDrawer = std::make_unique<UIDrawerTitleScene>();
	uiDrawer->Initialize();
}

void TitleScene::Update()
{
	uiDrawer->Update();
}

void UIDrawerTitleScene::Initialize()
{
	sprites["white"] = Sprite::Create("white1x1.png");
	sprites["white"]->SetCenterPos();
	sprites["white"]->SetCenterAnchor();
	sprites["white"]->size = constant->GetConstant<Vector2>("WhitePicSize");
}
