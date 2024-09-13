#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "AudioManager.h"

// UI描画クラス(GameOverScene用)
class UIDrawerGameOverScene : public WristerEngine::_2D::AbstractUIDrawer
{
	int animTime;
	int maxAnimTime;

	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Update() override;
};

// ゲームオーバーシーン
class GameOverScene : public WristerEngine::BaseScene
{
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::Audio* audio_select;
	WristerEngine::Audio* bgm;

	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
};