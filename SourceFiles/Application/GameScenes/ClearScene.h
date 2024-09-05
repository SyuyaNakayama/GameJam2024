#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

// UI描画クラス(ClearScene用)
class UIDrawerClearScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
};

// クリアシーン
class ClearScene : public WristerEngine::BaseScene
{
	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
};