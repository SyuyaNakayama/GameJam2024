#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "Easing.h"

// UI描画クラス(TitleScene用)
class UIDrawerTitleScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
};

// タイトルシーン
class TitleScene : public WristerEngine::BaseScene
{
	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
	
	void Draw() override;

	OperateConfig* operate = OperateConfig::GetInstance();

	float chargeMove;
	bool isUDChange;

	//タイトル用スプライト
	std::unique_ptr<WristerEngine::_2D::Sprite> bg;
	std::unique_ptr<WristerEngine::_2D::Sprite> player;
	std::unique_ptr<WristerEngine::_2D::Sprite> logo;
};