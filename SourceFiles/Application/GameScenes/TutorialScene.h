#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "Stage.h"

class UIDrawerTutorialScene : public WristerEngine::_2D::AbstractUIDrawer
{

	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
};

class TutorialScene : public WristerEngine::BaseScene
{
	// ステージオブジェクト
	Stage stage;
	std::unique_ptr<WristerEngine::_2D::Sprite> background; // 背景

public:

	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

