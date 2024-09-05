#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

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

	OperateConfig* operate = OperateConfig::GetInstance();
};