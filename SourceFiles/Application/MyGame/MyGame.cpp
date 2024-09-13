#include "AudioManager.h"
#include "CollisionManager.h"
#include "ModelManager.h"
#include "MyGame.h"
#include "ParticleManager.h"
#include "Scene.h"
#include "ShareValue.h"
using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void MyGame::Initialize()
{
	windowName = L"4026_“ä‚ª‰ð‚¯‚È‚¢‚Ì‚Å—Í‹Æ‚Å“Ë”j‚µ‚Ü‚·";
	Framework::Initialize();
#ifdef _DEBUG
	sceneManager->ChangeScene(Scene::Title, false, false, false);
#endif // _DEBUG
#ifdef NDEBUG
	sceneManager->ChangeScene(Scene::Title, false, false, false);
#endif // NDEBUG

	ModelManager::Initialize();
	WristerEngine::ParticleManager::Initialize();
	WristerEngine::AudioManager::Initialize();
	PostEffect::StaticInitialize();
	postEffect.Initialize(PostEffect::Type::None);
}

void MyGame::Update()
{
	Framework::Update();
	ModelManager::Update();
	WristerEngine::CollisionManager::CheckAllCollisions();
	WristerEngine::Physics::ResetCollideList();
	WristerEngine::ParticleManager::Update();
	WristerEngine::AudioManager::Update();
}

void MyGame::Draw()
{
	postEffect.PreDrawScene();
	ModelManager::DrawObjects();
	WristerEngine::ParticleManager::Draw();
	postEffect.PostDrawScene();

	dxCommon->PreDraw();
	postEffect.Draw();
	Sprite::PreDraw();
	sceneManager->Draw();
	dxCommon->PostDraw();
}

void MyGame::Finalize()
{
	WristerEngine::AudioManager::Finalize();
	Framework::Finalize();
}