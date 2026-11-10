#include "DxLib.h"
#include "Minecart.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionParameter.h"
#include "../Player/Player.h"

Minecart::Minecart()
{
    m_ModelHandle = -1;
    m_CollisionModelHandle = -1;
    m_DeliveryCollisionModelHandle = -1;

    m_Pos = VGet(0.0f, 0.0f, 0.0f);

    m_AABB = nullptr;
    m_DeliveryAABB = nullptr;
}

Minecart::~Minecart()
{
    Fin();
}

void Minecart::Init()
{
}

void Minecart::Load()
{
    // トロッコ本体を読み込む
    m_ModelHandle = MV1LoadModel("Data/Stage/Minecart.x");

    // トロッコ当たり判定用モデルを読み込む
    m_CollisionModelHandle = MV1LoadModel("Data/Stage/MinecartCollision.x");

    // 納品エリアのモデルを読み込む
    m_DeliveryCollisionModelHandle = MV1LoadModel("Data/Stage/DeliveryCollision.x");
}

void Minecart::Start()
{
    // トロッコ本体の位置を設定
    if (m_ModelHandle != -1)
    {
        MV1SetPosition(m_ModelHandle, m_Pos);
    }

    // 当たり判定モデルの位置を設定
    if (m_CollisionModelHandle != -1)
    {
        MV1SetPosition(m_CollisionModelHandle, m_Pos);
    }

    // 納品エリアの位置を設定
    if (m_DeliveryCollisionModelHandle != -1)
    {
        MV1SetPosition(m_DeliveryCollisionModelHandle, m_Pos);
    }

    // トロッコのAABBを生成
    m_AABB = CollisionManager::GetInstance()->CreateAABB();
    m_AABB->SetTargetPos(&m_Pos);
    m_AABB->SetLocalPos(VGet(0.0f, 1.0f, 0.0f));
    m_AABB->SetSize(VGet(3.0f, 2.0f, 4.0f));

    // 納品エリアのAABBを生成
    m_DeliveryAABB = CollisionManager::GetInstance()->CreateAABB();
    m_DeliveryAABB->SetTargetPos(&m_Pos);

    // 納品エリアの中心位置
    m_DeliveryAABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

    // 納品エリアの大きさ
    m_DeliveryAABB->SetSize(VGet(2.0f, 1.0f, 2.0f));
}

void Minecart::Step()
{
}

void Minecart::Update()
{
    if (m_ModelHandle != -1)
    {
        MV1SetPosition(m_ModelHandle, m_Pos);
    }

    if (m_CollisionModelHandle != -1)
    {
        MV1SetPosition(m_CollisionModelHandle, m_Pos);
    }

    if (m_DeliveryCollisionModelHandle != -1)
    {
        MV1SetPosition(m_DeliveryCollisionModelHandle, m_Pos);
    }
}

void Minecart::Draw()
{
    // トロッコ本体を描画
    if (m_ModelHandle != -1)
    {
        MV1DrawModel(m_ModelHandle);
    }
}

void Minecart::SetPos(VECTOR pos)
{
    m_Pos = pos;
}

bool Minecart::IsPlayerTouching(Player* player) const
{
    if (player == nullptr || m_AABB == nullptr)
    {
        return false;
    }

    if (player->GetAABB() == nullptr)
    {
        return false;
    }

    HitResultAABB result = player->GetAABB()->CheckAABB(m_AABB);

    return result.isHit;
}

bool Minecart::IsPlayerInDeliveryArea(Player* player) const
{
    if (player == nullptr || m_DeliveryAABB == nullptr)
    {
        return false;
    }

    if (player->GetAABB() == nullptr)
    {
        return false;
    }

    // プレイヤーと納品エリアのAABBを比較
    HitResultAABB result = player->GetAABB()->CheckAABB(m_DeliveryAABB);

    return result.isHit;
}

void Minecart::Fin()
{
    if (m_ModelHandle != -1)
    {
        MV1DeleteModel(m_ModelHandle);
        m_ModelHandle = -1;
    }

    if (m_CollisionModelHandle != -1)
    {
        MV1DeleteModel(m_CollisionModelHandle);
        m_CollisionModelHandle = -1;
    }

    if (m_DeliveryCollisionModelHandle != -1)
    {
        MV1DeleteModel(m_DeliveryCollisionModelHandle);
        m_DeliveryCollisionModelHandle = -1;
    }

    // AABBはCollisionManagerが管理・解放する
    m_AABB = nullptr;
    m_DeliveryAABB = nullptr;
}