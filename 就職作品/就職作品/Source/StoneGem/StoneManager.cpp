#include "DxLib.h"
#include "StoneManager.h"
#include "Stone.h"
#include "../Player/PlayerManager.h"

StoneManager* StoneManager::m_Instance = nullptr;

void StoneManager::CreateInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new StoneManager();
    }
}

void StoneManager::DeleteInstance()
{
    if (m_Instance != nullptr)
    {
        delete m_Instance;
        m_Instance = nullptr;
    }
}

StoneManager* StoneManager::GetInstance()
{
    return m_Instance;
}

StoneManager::StoneManager()
{
}

StoneManager::~StoneManager()
{
    Fin();
}

// 初期化処理
void StoneManager::Init()
{
    // 岩の配置は各ステージで行う
}

// モデルの読み込み
void StoneManager::Load()
{
    for (Stone* stone : m_Stones)
    {
        if (stone != nullptr)
        {
            stone->Load();
        }
    }
}

// 開始処理
void StoneManager::Start()
{
    for (Stone* stone : m_Stones)
    {
        if (stone != nullptr)
        {
            stone->Start();
        }
    }
}

// 更新前処理
void StoneManager::Step()
{
    if (PlayerManager::GetInstance() == nullptr)
    {
        return;
    }

    Player* player = PlayerManager::GetInstance()->GetPlayer();

    if (player == nullptr)
    {
        return;
    }

    VECTOR playerPos = player->GetPos();

    for (Stone* stone : m_Stones)
    {
        if (stone != nullptr)
        {
            stone->Step(playerPos);
        }
    }
}

// 更新処理
void StoneManager::Update()
{
    for (Stone* stone : m_Stones)
    {
        if (stone != nullptr)
        {
            stone->Update();
        }
    }
}

// 描画処理
void StoneManager::Draw()
{
    for (Stone* stone : m_Stones)
    {
        if (stone != nullptr)
        {
            stone->Draw();
        }
    }
}

// 終了処理
void StoneManager::Fin()
{
    ClearStones();
}

// 岩をすべて削除
void StoneManager::ClearStones()
{
    for (Stone* stone : m_Stones)
    {
        if (stone != nullptr)
        {
            delete stone;
        }
    }

    m_Stones.clear();
}

// 岩を作成
Stone* StoneManager::CreateStone(VECTOR pos)
{
    Stone* stone = new Stone();

    stone->SetPos(pos);         // 岩の位置を設定
    stone->Init();              // 岩の初期化

    m_Stones.push_back(stone);  // 岩のインスタンスをリストに追加

    return stone;
}

// インタラクト可能な岩があるか取得
bool StoneManager::IsInteractable() const
{
    for (Stone* stone : m_Stones)
    {
        if (stone != nullptr && stone->IsInteractable())
        {
            return true;
        }
    }

    return false;
}