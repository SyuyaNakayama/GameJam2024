#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "AudioManager.h"

// UI描画クラス(GameOverScene用)
class UIDrawerGameOverScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
};

// ゲームオーバーシーン
class GameOverScene : public WristerEngine::BaseScene
{
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::Audio* audio_select;

	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
};