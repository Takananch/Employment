#include "DxLib.h"
#include "Gem.h"
#include "Stone.h"
#include "../Player/Player.h"
#include "../Input/Input.h"

Gem::Gem()
{
    m_ModelHandle = -1;
	m_Pos = VGet(0.0f, 0.0f, 0.0f); // 宝石の座標を初期化
	m_Value = 100;                  // 宝石の価値を初期化
	m_Type = GEM_TYPE_NORMAL;       // 宝石の種類を初期化
	m_IsVisible = true;             // 宝石が表示されるかどうかのフラグを初期化
	m_IsInteractable = false;       // 宝石がインタラクト可能かどうかのフラグを初期化
	m_IsPickUp = false;           // 宝石が取得されたかどうかのフラグを初期化
	m_InteractDistance = 2.0f;      // プレイヤーと宝石のインタラクト可能距離を設定
}

Gem::~Gem()
{
    Fin();
}

bool Gem::Load()
{
    // 宝石の種類に応じてモデルを読み込む
    switch (m_Type)
    {
    case GEM_TYPE_NORMAL:
        m_ModelHandle = MV1LoadModel("Data/Stage/Gem/Gem.x");
        break;
    }

    if (m_ModelHandle == -1)
    {
        return false;
    }

    MV1SetPosition(m_ModelHandle, m_Pos);

    return true;
}

void Gem::SetPos(VECTOR pos)
{
    m_Pos = pos;

    if (m_ModelHandle != -1)
    {
        MV1SetPosition(m_ModelHandle, m_Pos);
    }
}

void Gem::Step(Player* player)
{
    m_IsInteractable = false;
	// プレイヤーが存在しない場合、または宝石が非表示の場合は処理を終了
    if (player == nullptr || !m_IsVisible)
    {
        return;
    }

    // プレイヤーと宝石の距離を計算
    float distance = VSize(VSub(player->GetPos(), m_Pos));

    // 取得可能な距離か判定
    if (distance <= m_InteractDistance)
    {
        m_IsInteractable = true;

        // Eキーが押された場合、宝石を取得
        if (Input::IsTriggerKey(Input::KEY_E))
        {
			// Playerに宝石を追加し、取得成功した場合は宝石を非表示にする
            if (player->AddGem(this))
            {
                m_IsPickUp = true;
                m_IsInteractable = false;
            }
        }
    }
}

void Gem::Draw()
{
    if (m_ModelHandle == -1 || !m_IsVisible)
    {
        return;
    }

    MV1DrawModel(m_ModelHandle);
}

void Gem::Fin()
{
    if (m_ModelHandle != -1)
    {
        MV1DeleteModel(m_ModelHandle);
        m_ModelHandle = -1;
    }
}