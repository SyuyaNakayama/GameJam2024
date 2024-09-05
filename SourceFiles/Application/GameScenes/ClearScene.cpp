#include "ClearScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void ClearScene::Initialize()
{
	// UI�`��N���X�̏�����
	uiDrawer = std::make_unique<UIDrawerClearScene>();
	uiDrawer->Initialize();
}

void ClearScene::Update()
{
	// UI�`��
	uiDrawer->Update();
}

void UIDrawerClearScene::Initialize()
{
}
