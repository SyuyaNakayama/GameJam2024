#pragma once
#include "MyGameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"
#include "Collider.h"
#include "Random.h"
#include "Audio.h"

class Player : public MyGameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> attack;
	std::unique_ptr<WristerEngine::_2D::Sprite> dive;	//潜っている時のスプライト
	std::unique_ptr<WristerEngine::_2D::Sprite> walk;	//歩いてる時
	std::unique_ptr<WristerEngine::_2D::Sprite> isAttack;	//攻撃時
	std::unique_ptr<WristerEngine::_2D::Sprite> drill;	//攻撃時のドリル
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::FrameTimer diveTimer; // 潜っている時間
	WristerEngine::FrameTimer attackTimer; // 攻撃している時間
	bool isGoal = false;

	//UI
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_attack;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_dive;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_coolTime1;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_coolTime2;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_key_space;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_key_down;
	std::unique_ptr<WristerEngine::_2D::Sprite> textBox;

	// なんらかのアクション
	void (Player::* Action)() = nullptr;
	void Dive(); // 潜る
	void Attack(); // 攻撃
	// クールタイム
	WristerEngine::FrameTimer diveCoolTimer;
	WristerEngine::FrameTimer attackCoolTimer;

	bool isCanUseDive = true, isCanUseAttack = true;

	//アニメーション変数
	int animTime;
	//クールタイム
	float coolCutPosA;
	float coolCutPosH;
	int countCoolTimeA;
	int countCoolTimeH;
	bool coolTimeCountStartA;
	bool coolTimeCountStartH;

	//チュートリアルの説明が終わったかどうか
	bool isExplanation;
	float page;

	WristerEngine::Random_Float shakeBody;

	// 音
	WristerEngine::Audio* audio_attack;
	WristerEngine::Audio* audio_dive;

	void Move(); // 移動
	void UITimer();	//UIでのクールタイム視覚化
	void InitializeUI();//長くなりそうなのでUI部分の初期化だけ別個用意
	void Tutorial();	//チュートリアル処理

	// GameObject を介して継承されました
	void Initialize(const ObjectData& objData) override;
	void Update() override;
	void Draw();
	void OnCollision(WristerEngine::_2D::ColliderGroup* group) override;
public:
	bool IsDive() const { return Action == &Player::Dive; }
	const WristerEngine::_2D::Sprite* GetSprite() const { return sprite.get(); }
	bool IsGoal() const { return isGoal; }
};