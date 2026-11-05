#pragma once
#include "DxLib.h"

class Stone
{
public:
	Stone();
	~Stone();

	void Init();
	void Load();
	void Start();
	void Step(VECTOR playerPos);
	void Update();
	void Draw();
	void Fin();

	void SetPos(VECTOR pos);		// 岩の位置を設定

	bool IsInteractable() const;	// 岩がインタラクト可能かどうかを取得
	bool IsBroken() const;			// 岩が破壊されているかどうかを取得

private:
	int m_StoneModelHandle;		// 岩のモデルハンドル
	int m_GemModelHandle;		// 宝石のモデルハンドル

	VECTOR m_Pos;				// 岩と宝石の位置

	bool m_IsBroken;			// 岩が破壊されているかどうか
	bool m_IsInteractable;		// 岩がインタラクト可能かどうか
	bool m_GemRandomSpawn;		// 宝石がランダムにスポーンするかどうか

	float m_InteractDistance;	// 岩とプレイヤーのインタラクト可能距離
};