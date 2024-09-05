#include "ClearScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void ClearScene::Initialize()
{
	// UI•`‰æƒNƒ‰ƒX‚Ì‰Šú‰»
	uiDrawer = std::make_unique<UIDrawerClearScene>();
	uiDrawer->Initialize();
}

void ClearScene::Update()
{
	// UI•`‰æ
	uiDrawer->Update();
}

void UIDrawerClearScene::Initialize()
{
}
