#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "Stage.h"

// UI描画クラス(GamePlayScene用)
class UIDrawerGamePlayScene : public WristerEngine::_2D::AbstractUIDrawer
{
	
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
};

// ゲームプレイシーン
class GamePlayScene : public WristerEngine::BaseScene
{
	// ステージオブジェクト
	Stage stage;
	Stage background;

	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};