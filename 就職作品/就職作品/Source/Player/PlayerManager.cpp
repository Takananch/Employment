#include "PlayerManager.h"

PlayerManager* PlayerManager::m_Instance = nullptr;

PlayerManager::PlayerManager()
{
    m_Player = nullptr;
}

PlayerManager::~PlayerManager()
{
    Fin();
}

void PlayerManager::CreatePlayer()
{
    if (m_Player == nullptr)
    {
        m_Player = new Player;
    }
}

void PlayerManager::Init()
{
    if (m_Player)
    {
        m_Player->Init();
    }
}

void PlayerManager::Load()
{
    if (m_Player)
    {
        m_Player->Load();
    }
}

void PlayerManager::Start()
{
    if (m_Player)
    {
        m_Player->Start();
    }
}

void PlayerManager::Step()
{
    if (m_Player)
    {
        m_Player->Step();
    }
}

void PlayerManager::Update()
{
    if (m_Player)
    {
        m_Player->Update();
    }
}

void PlayerManager::Draw()
{
    if (m_Player)
    {
        m_Player->Draw();
    }
}

void PlayerManager::Fin()
{
    if (m_Player)
    {
        delete m_Player;
        m_Player = nullptr;
    }
}