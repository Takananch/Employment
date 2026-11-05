#pragma once
#include "DxLib.h"

class StageBase
{
public:
    StageBase();
    virtual ~StageBase();

public:
    virtual void Init() = 0;
    virtual void Load() = 0;
    virtual void Start() = 0;
    virtual void Step() {}
    virtual void Update() {}
    virtual void Draw() = 0;
    virtual void Fin();

    // ステージとの当たり判定
    MV1_COLL_RESULT_POLY_DIM CheckCollisionSphere(VECTOR pos, float r);

protected:
    // 当たり判定モデルのロード
    void LoadCollisionModel(const char* path);

protected:
    int m_CollisionHandle;          // 当たり判定モデルのハンドル
    bool m_CollisionInfoSetup;      // 衝突情報を構築したかどうか
};