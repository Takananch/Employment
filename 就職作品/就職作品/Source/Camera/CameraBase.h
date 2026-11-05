#pragma once
#include "DxLib.h"

class CameraBase
{
public:
    CameraBase();
    virtual ~CameraBase();

public:
    virtual void Init() = 0;
    virtual void Load() = 0;
    virtual void Start() = 0;
    virtual void Step() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Fin() = 0;

public:

	VECTOR GetPos() const { return m_Pos; }         // カメラの位置を取得
	VECTOR GetTarget() const { return m_Target; }   // 注視点を取得

protected:

	VECTOR m_Pos;       // カメラの位置
	VECTOR m_Target;    // 注視点
	VECTOR m_UpVec;     // 上方向ベクトル

	float m_Yaw;    // ヨー
	float m_Pitch;  // ピッチ
};