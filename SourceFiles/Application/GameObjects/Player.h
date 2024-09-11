#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"
#include "Collider.h"

class Player : public WristerEngine::_2D::GameObject, public WristerEngine::_2D::ColliderGroup
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	std::unique_ptr<WristerEngine::_2D::Sprite> sprites;
	std::unique_ptr<WristerEngine::_2D::Sprite> attackArea;
	std::unique_ptr<WristerEngine::_2D::Sprite> hide;	//潜っている時のスプライト
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::FrameTimer hideTimer; // 隠れている時間
	WristerEngine::FrameTimer attackTimer; // 攻撃している時間
	bool isGoal = false;

	//UI
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_attack;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_dive;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_coolTime1;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_coolTime2;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_key_space;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_key_down;

	// なんらかのアクション
	void (Player::* Action)() = nullptr;
	void Hide(); // 隠れる
	void Attack(); // 攻撃
	// クールタイム
	WristerEngine::FrameTimer hideCoolTimer;
	WristerEngine::FrameTimer attackCoolTimer;

	bool isCanUseHide = true, isCanUseAttack = true;

	//アニメーション変数
	int animTime;
	//クールタイム
	float coolCutPosA;
	float coolCutPosH;
	int countCoolTimeA;
	int countCoolTimeH;
	bool coolTimeCountStartA;
	bool coolTimeCountStartH;
	//攻撃判定
	float attackCutPos;

	void Move(); // 移動
	void UITimer();	//UIでのクールタイム視覚化
	void Animations();	//プレイヤーのアニメーション周り
	void InitializeUI();//長くなりそうなのでUI部分の初期化だけ別個用意

	// GameObject を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw();
	void OnCollision(WristerEngine::_2D::ColliderGroup* group) override;
public:
	bool IsHide() const { return Action == &Player::Hide; }
	const WristerEngine::_2D::Sprite* GetSprite() const { return sprite.get(); }
	bool IsGoal() const { return isGoal; }
};