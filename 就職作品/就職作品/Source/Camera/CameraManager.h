#pragma once

#include "CameraBase.h"

class Camera;

enum CameraType
{
    CAMERA,
    CAMERA_TYPE_MAX,
};

class CameraManager
{
public:
    CameraManager();
    ~CameraManager();

public:
	static void CreateInstance();           // インスタンス生成
	static CameraManager* GetInstance();    // インスタンス取得
	static void DeleteInstance();           // インスタンス削除

public:
    void Init();
    void Load();
    void Start();
    void Step();
    void Update();
    void Draw();
    void Fin();

public:
	void CreateCamera(CameraType type); // カメラの生成
	// カメラの取得
    CameraBase* GetCamera(CameraType type)
    {
        return m_Camera[type];
    }

private:
    static CameraManager* m_Instance;     // 静的メンバ変数の初期化

	CameraBase* m_Camera[CAMERA_TYPE_MAX];  // カメラの配列
};