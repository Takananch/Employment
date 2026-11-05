#include "Stage1.h"
#include "DxLib.h"
#include "../StoneGem/StoneManager.h"

Stage1::Stage1()
{
    m_Stage1Handle = -1;
}

Stage1::~Stage1()
{
    Fin();
}

// 初期化処理
void Stage1::Init()
{
    // StoneManagerのインスタンスを取得
    StoneManager* stoneManager = StoneManager::GetInstance();

    if (stoneManager == nullptr)
    {
        return;
    }

    // 以前のステージの岩を削除
    stoneManager->ClearStones();

    // 岩を作成(X座標は+で右に、-で左に生成　Y座標は0.0fで固定　Z座標は奥行き)
    stoneManager->CreateStone(VGet(-2.0f, 0.0f, 11.0f));
    stoneManager->CreateStone(VGet(12.0f, 0.0f, 11.0f));
    stoneManager->CreateStone(VGet(20.0f, 0.0f, 4.0f));
    stoneManager->CreateStone(VGet(20.0f, 0.0f, 15.0f));
    stoneManager->CreateStone(VGet(20.0f, 0.0f, 41.0f));
    stoneManager->CreateStone(VGet(7.0f, 0.0f, 24.0f));
    stoneManager->CreateStone(VGet(7.0f, 0.0f, 41.0f));
    stoneManager->CreateStone(VGet(13.0f, 0.0f, 14.0f));
    stoneManager->CreateStone(VGet(-2.0f, 0.0f, 14.0f));
    stoneManager->CreateStone(VGet(3.0f, 0.0f, 41.0f));
    stoneManager->CreateStone(VGet(3.0f, 0.0f, 33.0f));
    stoneManager->CreateStone(VGet(-5.0f, 0.0f, 20.0f));
    stoneManager->CreateStone(VGet(-17.0f, 0.0f, 5.0f));
    stoneManager->CreateStone(VGet(-17.0f, 0.0f, 41.0f));
    stoneManager->CreateStone(VGet(-5.0f, 0.0f, 4.0f));
    stoneManager->CreateStone(VGet(-5.0f, 0.0f, 11.0f));
    stoneManager->CreateStone(VGet(-5.0f, 0.0f, 17.0f));
    stoneManager->CreateStone(VGet(-12.0f, 0.0f, 12.0f));
}

// モデルの読み込み
void Stage1::Load()
{
    // Stage1モデルをロード
    m_Stage1Handle = MV1LoadModel("Data/Stage/Stage1.x");

    // 当たり判定モデルをロード
    LoadCollisionModel("Data/Stage/Stage1Collision.x");
}

// 開始処理
void Stage1::Start()
{
    // Stage1開始時の処理
}

// 描画処理
void Stage1::Draw()
{
    if (m_Stage1Handle != -1)
    {
        MV1DrawModel(m_Stage1Handle);
    }
}

// 終了処理
void Stage1::Fin()
{
    // Stage1モデルを削除
    if (m_Stage1Handle != -1)
    {
        MV1DeleteModel(m_Stage1Handle);
        m_Stage1Handle = -1;
    }

    // StageBase側の終了処理
    StageBase::Fin();
}