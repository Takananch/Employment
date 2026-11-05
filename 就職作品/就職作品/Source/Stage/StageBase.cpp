#include "StageBase.h"

StageBase::StageBase()
{
    m_CollisionHandle = -1;
    m_CollisionInfoSetup = false;
}

StageBase::~StageBase()
{
    Fin();
}

// 当たり判定モデルのロード
void StageBase::LoadCollisionModel(const char* path)
{
    // 既存の当たり判定モデルを削除
    if (m_CollisionHandle != -1)
    {
        if (m_CollisionInfoSetup)
        {
            MV1TerminateCollInfo(m_CollisionHandle);
            m_CollisionInfoSetup = false;
        }

        MV1DeleteModel(m_CollisionHandle);
        m_CollisionHandle = -1;
    }

    // 当たり判定モデルをロード
    m_CollisionHandle = MV1LoadModel(path);

    // モデルが正常にロードできた場合、衝突情報を構築
    if (m_CollisionHandle != -1)
    {
        MV1SetupCollInfo(m_CollisionHandle);
        m_CollisionInfoSetup = true;
    }
}

// ステージとの当たり判定
MV1_COLL_RESULT_POLY_DIM StageBase::CheckCollisionSphere(VECTOR pos, float r)
{
    // 当たり判定モデルが存在しない場合
    if (m_CollisionHandle == -1)
    {
        return {};
    }

    // ステージと球の当たり判定
    return MV1CollCheck_Sphere(m_CollisionHandle, -1, pos, r);
}

// 終了処理
void StageBase::Fin()
{
    // 構築した衝突情報を削除
    if (m_CollisionHandle != -1 && m_CollisionInfoSetup)
    {
        MV1TerminateCollInfo(m_CollisionHandle);
        m_CollisionInfoSetup = false;
    }

    // 当たり判定モデルを削除
    if (m_CollisionHandle != -1)
    {
        MV1DeleteModel(m_CollisionHandle);
        m_CollisionHandle = -1;
    }
}