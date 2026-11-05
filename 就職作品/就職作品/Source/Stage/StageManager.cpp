#include "StageManager.h"
#include "StageBase.h"
#include "Stage1.h"
#include "Stage2.h"
#include "../StoneGem/StoneManager.h"

StageManager* StageManager::m_Instance = nullptr;

StageManager::StageManager()
{
    m_Stage = nullptr;
    m_CurrentStageNumber = 0;
}

StageManager::~StageManager()
{
    Fin();
}

void StageManager::Init()
{
    // 最初のステージとしてStage1を生成
    if (m_Stage == nullptr)
    {
        m_Stage = new Stage1();
        m_CurrentStageNumber = 1;

        if (m_Stage != nullptr)
        {
            m_Stage->Init();
        }
    }
}

void StageManager::Load()
{
    if (m_Stage != nullptr)
    {
        m_Stage->Load();
    }

    // 岩のモデルを読み込む
    if (StoneManager::GetInstance() != nullptr)
    {
        StoneManager::GetInstance()->Load();
    }
}

void StageManager::Start()
{
    if (m_Stage != nullptr)
    {
        m_Stage->Start();
    }

    // 岩の開始処理
    if (StoneManager::GetInstance() != nullptr)
    {
        StoneManager::GetInstance()->Start();
    }
}

void StageManager::Step()
{
    if (m_Stage != nullptr)
    {
        m_Stage->Step();
    }
}

void StageManager::Update()
{
    if (m_Stage != nullptr)
    {
        m_Stage->Update();
    }
}

void StageManager::Draw()
{
    if (m_Stage != nullptr)
    {
        m_Stage->Draw();
    }
}

// ステージ切り替え
bool StageManager::ChangeStage(int stageNumber)
{
    StageBase* newStage = nullptr;

    // ステージ番号に応じてインスタンスを生成
    switch (stageNumber)
    {
    case 1:
        newStage = new Stage1();
        break;

    case 2:
        newStage = new Stage2();
        break;

    default:
		// 無効なステージ番号の場合は何もしない
        return false;
    }

    // 現在のステージを削除
    if (m_Stage != nullptr)
    {
        delete m_Stage;
        m_Stage = nullptr;
    }

    // 新しいステージを設定
    m_Stage = newStage;
    m_CurrentStageNumber = stageNumber;

    // 新しいステージの初期化
    m_Stage->Init();

    // 新しいステージのモデルを読み込む
    m_Stage->Load();

    // 新しいステージの岩を読み込む
    if (StoneManager::GetInstance() != nullptr)
    {
        StoneManager::GetInstance()->Load();
    }

    // 新しいステージの開始処理
    m_Stage->Start();

    // 新しいステージの岩の開始処理
    if (StoneManager::GetInstance() != nullptr)
    {
        StoneManager::GetInstance()->Start();
    }

    return true;
}

// 終了処理
void StageManager::Fin()
{
    if (m_Stage != nullptr)
    {
        delete m_Stage;
        m_Stage = nullptr;
    }

    m_CurrentStageNumber = 0;
}
