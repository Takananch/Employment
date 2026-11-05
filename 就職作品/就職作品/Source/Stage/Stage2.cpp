#include "Stage2.h"
#include "DxLib.h"
#include "../StoneGem/StoneManager.h"

Stage2::Stage2()
{
    m_Stage2Handle = -1;
}

Stage2::~Stage2()
{
    Fin();
}

// 初期化処理
void Stage2::Init()
{
    // StoneManagerのインスタンスを取得
    StoneManager* stoneManager = StoneManager::GetInstance();

    if (stoneManager == nullptr)
    {
        return;
    }

    // 以前のステージの岩を削除
    stoneManager->ClearStones();
    // Stage2固有の初期化処理
    // 岩を作成(X座標は+で右に、-で左に生成する。Y座標は0.0fで固定。Z座標は奥行き)
    stoneManager->CreateStone(VGet(-2.0f, 0.0f, 11.0f));
    stoneManager->CreateStone(VGet(12.0f, 0.0f, 11.0f));
    stoneManager->CreateStone(VGet(20.0f, 0.0f, 4.0f));
    stoneManager->CreateStone(VGet(20.0f, 0.0f, 15.0f));
}

// モデルの読み込み
void Stage2::Load()
{
    // Stage2モデルをロード
    m_Stage2Handle = MV1LoadModel("Data/Stage/Stage2.x");

    // 当たり判定モデルをロード
    LoadCollisionModel("Data/Stage/Stage2Collision.x");
}

// 開始処理
void Stage2::Start()
{
    // Stage2開始時の処理
}

// 描画処理
void Stage2::Draw()
{
    // Stage2モデルを描画
    if (m_Stage2Handle != -1)
    {
        MV1DrawModel(m_Stage2Handle);
    }
}

// 終了処理
void Stage2::Fin()
{
    // Stage2モデルを削除
    if (m_Stage2Handle != -1)
    {
        MV1DeleteModel(m_Stage2Handle);
        m_Stage2Handle = -1;
    }

    // StageBase側の終了処理
    StageBase::Fin();
}