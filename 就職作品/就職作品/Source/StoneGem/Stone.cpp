#include "DxLib.h"
#include "Stone.h"
#include "../Input/Input.h"

Stone::Stone()	// コンストラクタ
{
	m_StoneModelHandle = 0;				// 岩のモデルハンドルを初期化
	m_GemModelHandle = 0;				// 宝石のモデルハンドルを初期化
	m_Pos = VGet(0.0f, 0.0f, 0.0f);		// 岩と宝石の位置を初期化
	m_IsBroken = false;					// 岩が破壊されているかどうかのフラグ
	m_IsInteractable = false;			// 岩がインタラクト可能かどうかのフラグ
	m_GemRandomSpawn = false;			// 宝石がランダムにスポーンするかどうかのフラグ
	m_InteractDistance = 3.0f;			// 岩とプレイヤーのインタラクト可能距離を設定
}

Stone::~Stone()	// デストラクタ
{
	Fin();
}

void Stone::Init()
{
	m_IsBroken = false;
	m_IsInteractable = false;
	m_GemRandomSpawn = false;
}

void Stone::Load()
{
	// 岩のモデルを読み込む
	m_StoneModelHandle = MV1LoadModel("Data/Stage/Stage1Rock.x");

	// 宝石のモデルを読み込む
	m_GemModelHandle = MV1LoadModel("Data/Stage/Gem.x");
}

void Stone::Start()
{
	// 岩と宝石を同じ位置に設定
	if (m_StoneModelHandle != -1)
	{
		MV1SetPosition(m_StoneModelHandle, m_Pos);
	}

	if (m_GemModelHandle != -1)
	{
		MV1SetPosition(m_GemModelHandle, m_Pos);
	}
}

void Stone::Step(VECTOR playerPos)
{
	// 岩が破壊されていない場合
	if (!m_IsBroken)
	{
		// プレイヤーと岩の距離を計算
		float distance = VSize(VSub(playerPos, m_Pos));

		// インタラクト可能距離以内か判定
		if (distance <= m_InteractDistance)
		{
			m_IsInteractable = true;

			// Eキーが押された場合、岩を破壊する
			if (Input::IsTriggerKey(Input::KEY_E))
			{
				m_IsBroken = true;
				m_IsInteractable = false;

				// 岩が破壊されたとき、50%の確率で宝石をスポーンさせる(0でスポーン、1でスポーンしない)
				if (GetRand(1) == 0)
				{
					m_GemRandomSpawn = true;
				}
			}
		}
		else
		{
			m_IsInteractable = false;
		}
	}
	else
	{
		// 岩が破壊された後はインタラクト不可
		m_IsInteractable = false;
	}
}

void Stone::Update()
{
	if (m_StoneModelHandle != -1)
	{
		MV1SetPosition(m_StoneModelHandle, m_Pos);
	}

	if (m_GemModelHandle != -1)
	{
		MV1SetPosition(m_GemModelHandle, m_Pos);
	}
}

void Stone::Draw()
{
	// 岩が破壊されていない場合は岩を表示
	if (!m_IsBroken)
	{
		if (m_StoneModelHandle != -1)
		{
			MV1DrawModel(m_StoneModelHandle);
		}
	}
	// 岩が破壊されていて、GetRand(1)の結果が0(出現)の場合は宝石を表示
	else if (m_GemRandomSpawn)
	{
		if (m_GemModelHandle != -1)
		{
			MV1DrawModel(m_GemModelHandle);
		}
	}
}

void Stone::Fin()
{
	if (m_StoneModelHandle != -1)
	{
		MV1DeleteModel(m_StoneModelHandle);
	}

	if (m_GemModelHandle != -1)
	{
		MV1DeleteModel(m_GemModelHandle);
	}
}

void Stone::SetPos(VECTOR pos)
{
	m_Pos = pos;	// 岩と宝石の位置を設定
}

bool Stone::IsInteractable() const
{
	return m_IsInteractable;	// プレイヤーが岩に近づいたかどうかの判定
}

bool Stone::IsBroken() const
{
	return m_IsBroken;	// 岩が破壊されているかどうかの判定
}