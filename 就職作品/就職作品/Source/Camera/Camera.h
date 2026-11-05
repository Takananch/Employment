#pragma once
#include "CameraBase.h"

class Player;

class Camera : public CameraBase
{
public:
    Camera();
    virtual ~Camera();

public:
    void Init() override;
    void Load() override;
    void Start() override;
    void Step() override;
    void Update() override;
    void Draw() override;
    void Fin() override;

public:
    // カメラの向いている方向
    VECTOR GetFront() const;
	// カメラの移動方向（前）
    VECTOR GetMoveFront() const;
	// カメラの移動方向（右）
    VECTOR GetMoveRight() const;

	// ヨーの値を取得
    float GetYaw() const;

private:
	Player* m_TargetPlayer;     // 注視点のターゲットプレイヤー

	float m_MouseSensitivity;   // マウス感度
};