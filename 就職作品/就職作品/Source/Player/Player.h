#pragma once
#include "DxLib.h"
#include <vector>
#include "../StoneGem/Gem.h"

class CollisionAABB;
class CollisionSphere;

// アニメーション
enum PlayerAnimationType
{
	PLAYER_ANIMATION_DASH,
	PLAYER_ANIMATION_MINE,
	PLAYER_ANIMATION_WAIT,
	PLAYER_ANIMATION_WALK,
};

class Player
{
public:

	Player();
	~Player();

public:

	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:

	VECTOR GetPos() { return m_Pos; }
	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphereCollision() { return m_SphereCollision; }

	void PlayAnimation(PlayerAnimationType anim, bool isLoop);
	void UpdateAnimation();

	void HitBlock(CollisionAABB* other);	// ブロックとの当たり判定

	VECTOR GetPos() const	// 座標を取得
	{
		return m_Pos;
	}

	void SetPos(VECTOR pos)	// 座標を設定
	{
		m_Pos = pos;
	}

	CollisionSphere* GetSphere()	// 球の当たり判定を取得
	{
		return m_SphereCollision;
	}

	// 宝石の所持
	bool AddGem(Gem* gem);				// 宝石を追加
	int GetGemCount() const;			// 宝石の数を取得
	int GetGemTotalValue() const;		// 宝石の合計価値を取得
	std::vector<Gem*> TakeAllGems();	// 持っている宝石を全て手離す

private:

	int m_ModelHandle;					// モデルハンドル
	VECTOR m_Pos;						// 座標
	float m_MoveSpeed;					// 移動速度
	float m_MoveDashSpeed;				// ダッシュ速度
	float m_Stamina;					// スタミナ
	float m_MaxStamina;					// 最大スタミナ
	float m_StaminaRecoveryDelay;		// スタミナ回復開始までの時間
	float m_StaminaEmptyDelay;			// スタミナ0になった後の待ち時間
	bool m_IsDash;						// 現在ダッシュ中か
	int m_AnimationAttachIndex;			// アニメーションのアタッチインデックス
	float m_AnimationTotalTime;			// 再生中のアニメーションの総時間
	float m_AnimationNowTime;			// 再生中のアニメーションの再生時間
	bool m_IsLoopAnimation;				// アニメーションをループさせるか
	PlayerAnimationType m_NowAnimation;	// 再生中のアニメーション
	VECTOR m_Rot;						// 回転
	VECTOR m_Scale;						// スケール
	VECTOR m_Move;						// 移動量
	VECTOR m_OldPos;					// 前回の座標
	CollisionAABB* m_AABB;				// AABBの当たり判定
	CollisionSphere* m_SphereCollision;	// 球の当たり判定

	// 所持している宝石
	std::vector<Gem*> m_Gems;

	// 宝石の最大所持数
	static const int MAX_GEM_COUNT = 5;
};