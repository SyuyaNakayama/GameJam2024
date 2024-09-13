#include "GamePlayScene.h"
#include "ShareValue.h"
#include "CollisionManager.h"

using namespace WristerEngine::_2D;

void GamePlayScene::Initialize()
{
	ShareValue::GetInstance()->isGoal = false;
	stage.Initialize();

	background = Sprite::Create("SceneBG/background.png");
	background->size = WristerEngine::WIN_SIZE;
	background->Update();

	// UI•`‰æƒNƒ‰ƒX‚Ì‰Šú‰»
	uiDrawer = std::make_unique<UIDrawerGamePlayScene>();
	uiDrawer->Initialize();
}

void GamePlayScene::Update()
{
	ShareValue* shareVal = ShareValue::GetInstance();
	if (shareVal->isGoal)
	{
		shareVal->isGoal = false;
		shareVal->stageNum++;
		if (shareVal->stageNum <= WEConst(int, "StageNum")) { sceneManager->ChangeScene(Scene::Play); }
		else { sceneManager->ChangeScene(Scene::Clear); }
		return;
	}

	if (shareVal->isGameOver)
	{
		sceneManager->ChangeScene(Scene::GameOver);
		return;
	}

	stage.Update();
	// UI•`‰æ
	uiDrawer->Update();
}

void GamePlayScene::Draw()
{
	background->Draw();
	stage.Draw();
	// UI•`‰æ
	uiDrawer->Draw();
}

void UIDrawerGamePlayScene::Initialize()
{
	// ’n–Ê‚ÌUI‚Ì‰Šú‰»
	sprites["Ground"] = Sprite::Create("brick.png");
	std::unique_ptr<Sprite>& s = sprites["Ground"];
	s->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	s->textureSize.x *= (WristerEngine::WIN_SIZE.x / s->size.x);
	s->textureSize.y *= (Const(float, "GroundHeight") / s->size.y);
	s->size.x = WristerEngine::WIN_SIZE.x;
	s->size.y = Const(float, "GroundHeight");
}
