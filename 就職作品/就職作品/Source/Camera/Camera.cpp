#include "Camera.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Input/Input.h"
#include <cmath>

#define CAMERA_NEAR_CLIP 0.01f      // カメラの近クリップ面の距離
#define CAMERA_FAR_CLIP 1000.0f     // カメラの遠クリップ面の距離
#define SCREEN_CENTER_X 960         // 画面中央のX座標
#define SCREEN_CENTER_Y 540         // 画面中央のY座標

Camera::Camera() : CameraBase()
{
	m_TargetPlayer = nullptr;       // 注視点のターゲットプレイヤー
	m_MouseSensitivity = 0.003f;    // マウス感度
}

Camera::~Camera()
{
    Fin();
}

void Camera::Init()
{
}

void Camera::Load()
{
}

void Camera::Start()
{
	// カメラの近クリップ面と遠クリップ面の距離を設定
    SetCameraNearFar(CAMERA_NEAR_CLIP,CAMERA_FAR_CLIP);
	// マウスカーソルを非表示にする
    SetMouseDispFlag(FALSE);
	// マウスカーソルを画面中央に移動する
    SetMousePoint(SCREEN_CENTER_X,SCREEN_CENTER_Y);
	// 注視点のターゲットプレイヤーを取得
    m_TargetPlayer = PlayerManager::GetInstance()->GetPlayer();
}

void Camera::Step()
{
}

void Camera::Update()
{
	// 注視点のターゲットプレイヤーが存在しない場合は処理を終了
    if (m_TargetPlayer == nullptr)
    {
        return;
    }

	// カメラの位置をプレイヤーの位置に設定
    m_Pos = m_TargetPlayer->GetPos();

	// カメラの高さを調整
    m_Pos.y += 4.5f;

	// マウスの移動量に応じてYawとPitchを更新
    m_Yaw +=Input::GetMouseMoveX() * m_MouseSensitivity;
    m_Pitch -= Input::GetMouseMoveY() * m_MouseSensitivity;

    // カメラの上下の制限
    if (m_Pitch > DX_PI_F / 2.2f)
    {
        m_Pitch = DX_PI_F / 2.2f;
    }

    if (m_Pitch < -DX_PI_F / 2.2f)
    {
        m_Pitch = -DX_PI_F / 2.2f;
    }

	// カメラの前方向ベクトルを取得
    VECTOR front = GetFront();

	// カメラの注視点を計算
    m_Target = VAdd(m_Pos,front);

	// カメラの位置、注視点、上方向ベクトルを設定
    SetCameraPositionAndTargetAndUpVec(m_Pos,m_Target,VGet(0.0f, 1.0f, 0.0f));
}

void Camera::Draw()
{
	// Yawの値を画面に描画
    // DrawFormatString(0,80,GetColor(255, 255, 255),"Yaw : %.2f",m_Yaw);
	// Pitchの値を画面に描画
    // DrawFormatString(0,120,GetColor(255, 255, 255),"Pitch : %.2f",m_Pitch);
}

void Camera::Fin()
{
}

VECTOR Camera::GetFront() const // カメラの向いている方向を取得
{
	VECTOR front;
	// YawとPitchの値から前方向ベクトルを計算
    front.x = cosf(m_Pitch) * sinf(m_Yaw);
    front.y = sinf(m_Pitch);
    front.z = cosf(m_Pitch) * cosf(m_Yaw);
    return front;
}

VECTOR Camera::GetMoveFront() const // カメラの前への移動方向を取得
{
    VECTOR front;

    front.x = sinf(m_Yaw);
    front.y = 0.0f;
    front.z = cosf(m_Yaw);
    return VNorm(front);
}

VECTOR Camera::GetMoveRight() const // カメラの右への移動方向を取得
{
    VECTOR right;

    right.x = cosf(m_Yaw);
    right.y = 0.0f;
    right.z = -sinf(m_Yaw);
    return VNorm(right);
}

float Camera::GetYaw() const
{
    return m_Yaw;
}