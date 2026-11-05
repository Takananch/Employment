#include "CameraManager.h"
#include "Camera.h"

CameraManager* CameraManager::m_Instance = nullptr;     // Ã“Iƒƒ“ƒo•Ï”‚Ì‰Šú‰»

CameraManager::CameraManager()
{
    for (int i = 0; i < CAMERA_TYPE_MAX; i++)
    {
        m_Camera[i] = nullptr;
    }
}

CameraManager::~CameraManager()
{
    Fin();
}

void CameraManager::CreateInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new CameraManager;
    }
}

CameraManager* CameraManager::GetInstance()
{
    return m_Instance;
}

void CameraManager::DeleteInstance()
{
    if (m_Instance)
    {
        delete m_Instance;
        m_Instance = nullptr;
    }
}

void CameraManager::CreateCamera(CameraType type)
{
    switch (type)
    {
    case CAMERA:

        if (m_Camera[CAMERA] == nullptr)
        {
            m_Camera[CAMERA] = new Camera;
        }

        break;
    }
}

void CameraManager::Init()
{
    for (int i = 0; i < CAMERA_TYPE_MAX; i++)
    {
        if (m_Camera[i])
            m_Camera[i]->Init();
    }
}

void CameraManager::Load()
{
    for (int i = 0; i < CAMERA_TYPE_MAX; i++)
    {
        if (m_Camera[i])
            m_Camera[i]->Load();
    }
}

void CameraManager::Start()
{
    for (int i = 0; i < CAMERA_TYPE_MAX; i++)
    {
        if (m_Camera[i])
            m_Camera[i]->Start();
    }
}

void CameraManager::Step()
{
    for (int i = 0; i < CAMERA_TYPE_MAX; i++)
    {
        if (m_Camera[i])
            m_Camera[i]->Step();
    }
}

void CameraManager::Update()
{
    for (int i = 0; i < CAMERA_TYPE_MAX; i++)
    {
        if (m_Camera[i])
            m_Camera[i]->Update();
    }
}

void CameraManager::Draw()
{
    for (int i = 0; i < CAMERA_TYPE_MAX; i++)
    {
        if (m_Camera[i])
            m_Camera[i]->Draw();
    }
}

void CameraManager::Fin()
{
    for (int i = 0; i < CAMERA_TYPE_MAX; i++)
    {
        if (m_Camera[i])
        {
            delete m_Camera[i];
            m_Camera[i] = nullptr;
        }
    }
}