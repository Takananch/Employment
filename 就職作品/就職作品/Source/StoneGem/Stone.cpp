#include "DxLib.h"
#include "Stone.h"
#include "Gem.h"
#include "../Input/Input.h"
#include "../Player/Player.h"

Stone::Stone()	// コンストラクタ
{
	m_StoneModelHandle = 0;				// 岩のモデルハンドルを初期化
	m_Pos = VGet(0.0f, 0.0f, 0.0f);		// 岩と宝石の位置を初期化
	m_IsBroken = false;					// 岩が破壊されているかどうかのフラグ
	m_IsInteractable = false;			// 岩がインタラクト可能かどうかのフラグ
	m_InteractDistance = 3.5f;			// 岩とプレイヤーのインタラクト可能距離を設定
	m_GemSpawnTime = 0;					// 宝石のスポーン開始時刻を初期化
	m_IsGemSpawnPending = false;		// 宝石のスポーン待機中かどうかのフラグを初期化
	m_Gem = nullptr;					// 宝石のインスタンスを初期化
}

Stone::~Stone()	// デストラクタ
{
	Fin();
}

void Stone::Init()
{
	m_IsBroken = false;
	m_IsInteractable = false;
	m_GemSpawnTime = 0;
	m_IsGemSpawnPending = false;
}

void Stone::Load()
{
	// 岩のモデルを読み込む
	m_StoneModelHandle = MV1LoadModel("Data/Stage/Stone/Stone.x");
}

void Stone::Start()
{
	// 岩と宝石を同じ位置に設定
	if (m_StoneModelHandle != -1)
	{
		MV1SetPosition(m_StoneModelHandle, m_Pos);
	}
}

void Stone::Step(Player* player)
{
	if (player == nullptr)
	{
		return;
	}

	// 岩が破壊されていない場合
	if (!m_IsBroken)
	{
		// プレイヤーと岩の距離を計算
		float distance = VSize(VSub(player->GetPos(), m_Pos));

		// インタラクト可能距離以内か判定
		if (distance <= m_InteractDistance)
		{
			m_IsInteractable = true;

			// Eキーが押された場合、岩を破壊する
			if (Input::IsTriggerKey(Input::KEY_E))
			{
				m_IsBroken = true;
				m_IsInteractable = false;

				// 岩が破壊されたとき、50%の確率で宝石をスポーンさせる(0で宝石が出現、1で宝石が出現しない)
				if (GetRand(1) == 0)
				{
					m_IsGemSpawnPending = true;
					m_GemSpawnTime = GetNowCount();
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

	// 岩が破壊されてから0.25秒経過したか判定
	if (m_IsGemSpawnPending)
	{
		// 宝石のスポーン待機中で、0.25秒経過した場合、宝石を生成する
		if (GetNowCount() - m_GemSpawnTime >= 250)
		{
			m_Gem = new Gem();
			m_Gem->SetPos(m_Pos);

			// 宝石のモデルを読み込む
			if (!m_Gem->Load())
			{
				delete m_Gem;
				m_Gem = nullptr;
			}

			m_IsGemSpawnPending = false;
		}
	}

	// 宝石が存在する場合、取得判定を行う
	if (m_Gem != nullptr)
	{
		m_Gem->Step(player);

		// 宝石が取得された場合、Stone側の管理から外す
		if (m_Gem->IsPickedUp())
		{
			m_Gem = nullptr;
		}
	}
}

void Stone::Update()
{
	if (m_StoneModelHandle != -1)
	{
		MV1SetPosition(m_StoneModelHandle, m_Pos);
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
	// 岩が破壊されていて、GetRand(1)の結果が0(出現)の場合は宝石を表示、1の場合は宝石を表示しない
	else if (m_Gem != nullptr)
	{
		m_Gem->Draw();
	}
}

void Stone::Fin()
{
	if (m_StoneModelHandle != -1)
	{
		MV1DeleteModel(m_StoneModelHandle);
	}

	// まだ岩側が管理している宝石だけ解放する
	if (m_Gem != nullptr)
	{
		delete m_Gem;
		m_Gem = nullptr;
	}
}

void Stone::SetPos(VECTOR pos)
{
	m_Pos = pos;	// 岩と宝石の位置を設定
}

bool Stone::IsInteractable() const
{
	// 岩がインタラクト可能な場合はtrueを返す
	if (m_IsInteractable)
	{
		return true;
	}

	// 宝石が存在し、かつ宝石がインタラクト可能な場合はtrueを返す
	if (m_Gem != nullptr && m_Gem->IsInteractable())
	{
		return true;
	}

	return false;
}

bool Stone::IsBroken() const
{
	return m_IsBroken;	// 岩が破壊されているかどうかの判定
}