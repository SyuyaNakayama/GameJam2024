#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

// UI描画クラス(GamePlayScene用)
class UIDrawerGamePlayScene : public WristerEngine::_2D::AbstractUIDrawer
{
	
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
};

// ゲームプレイシーン
class GamePlayScene : public WristerEngine::BaseScene
{
	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
};