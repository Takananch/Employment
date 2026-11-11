#include "DxLib.h"
#include "Minecart.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionParameter.h"
#include "../Player/Player.h"

Minecart::Minecart()
{
	m_ModelHandle = 0;                  // トロッコ本体のモデルハンドルを初期化
	m_CollisionModelHandle = 0;         // 当たり判定モデルのハンドルを初期化
	m_DeliveryCollisionModelHandle = 0; // 納品エリアのモデルハンドルを初期化
	m_Pos = VGet(0.0f, 0.0f, 0.0f);     // トロッコの座標を初期化
	m_AABB = nullptr;                   // トロッコのAABBを初期化
	m_DeliveryCollisionAABB = nullptr;  // 納品エリアのAABBを初期化
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
    MV1SetPosition(m_ModelHandle, m_Pos);
    // 当たり判定モデルの位置を設定
    MV1SetPosition(m_CollisionModelHandle, m_Pos);
    // 納品エリアの位置を設定
    MV1SetPosition(m_DeliveryCollisionModelHandle, m_Pos);

    // トロッコのAABBを生成
    m_AABB = CollisionManager::GetInstance()->CreateAABB();
    m_AABB->SetTargetPos(&m_Pos);
    m_AABB->SetLocalPos(VGet(0.0f, 1.0f, 0.0f));
    m_AABB->SetSize(VGet(3.0f, 2.0f, 4.0f));

    // 納品エリアのAABBを生成
    m_DeliveryCollisionAABB = CollisionManager::GetInstance()->CreateAABB();
    m_DeliveryCollisionAABB->SetTargetPos(&m_Pos);

    // 納品エリアの中心位置
    m_DeliveryCollisionAABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
    // 納品エリアの大きさ
    m_DeliveryCollisionAABB->SetSize(VGet(3.0f, 1.0f, 1.0f));
}

void Minecart::Step()
{
}

// 更新処理
void Minecart::Update()
{
    MV1SetPosition(m_ModelHandle, m_Pos);
    MV1SetPosition(m_CollisionModelHandle, m_Pos);
    MV1SetPosition(m_DeliveryCollisionModelHandle, m_Pos);
}

void Minecart::Draw()
{
    // トロッコ本体を描画
    MV1DrawModel(m_ModelHandle);
}

void Minecart::SetPos(VECTOR pos)
{
    m_Pos = pos;
}

// プレイヤーとトロッコが接触しているかを判定する関数
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

// プレイヤーが納品エリアに入っているかを判定する関数
bool Minecart::IsPlayerInDeliveryArea(Player* player) const
{
	// 納品エリアのAABBが存在しない場合はfalseを返す
    if (player == nullptr || m_DeliveryCollisionAABB == nullptr)
    {
        return false;
    }

    if (player->GetAABB() == nullptr)
    {
        return false;
    }

    // プレイヤーと納品エリアのAABBを比較
    HitResultAABB result = player->GetAABB()->CheckAABB(m_DeliveryCollisionAABB);

    return result.isHit;
}

// 削除処理
void Minecart::Fin()
{
    MV1DeleteModel(m_ModelHandle);
    m_ModelHandle = 0;
    MV1DeleteModel(m_CollisionModelHandle);
    m_CollisionModelHandle = 0;
    MV1DeleteModel(m_DeliveryCollisionModelHandle);
    m_DeliveryCollisionModelHandle = 0;

    // AABBはCollisionManagerが管理・解放する
    m_AABB = nullptr;
    m_DeliveryCollisionAABB = nullptr;
}