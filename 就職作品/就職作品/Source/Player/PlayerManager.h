#pragma once
#include "Player.h"

class PlayerManager
{
public:
    PlayerManager();
    ~PlayerManager();

private:
    static PlayerManager* m_Instance;

public:
    static void CreateInstance()
    {
        if (!m_Instance)
        {
            m_Instance = new PlayerManager;
        }
    }

    static PlayerManager* GetInstance()
    {
        return m_Instance;
    }

    static void DeleteInstance()
    {
        if (m_Instance)
        {
            delete m_Instance;
        }

        m_Instance = nullptr;
    }

public:
    void Init();
    void Load();
    void Start();
    void Step();
    void Update();
    void Draw();
    void Fin();

public:
    void CreatePlayer();

    Player* GetPlayer()
    {
        return m_Player;
    }

private:
    Player* m_Player;
};