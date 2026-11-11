#pragma once
#include "DxLib.h"

class CollisionAABB;
class Player;

class Minecart
{
public:
    Minecart();
    ~Minecart();

    void Init();
    void Load();
    void Start();
    void Step();
    void Update();
    void Draw();
    void Fin();

    void SetPos(VECTOR pos);
    VECTOR GetPos() const { return m_Pos; }

    // プレイヤーとトロッコが接触しているか
    bool IsPlayerTouching(Player* player) const;

    // プレイヤーが納品エリアに入っているか
    bool IsPlayerInDeliveryArea(Player* player) const;

private:
    int m_ModelHandle;                       // トロッコ本体のモデルハンドル
    int m_CollisionModelHandle;              // 当たり判定モデルのハンドル
    int m_DeliveryCollisionModelHandle;      // 納品エリアのモデルハンドル
    VECTOR m_Pos;                            // トロッコの座標
    CollisionAABB* m_AABB;                   // トロッコのAABB
    CollisionAABB* m_DeliveryCollisionAABB;           // 納品エリアのAABB
};