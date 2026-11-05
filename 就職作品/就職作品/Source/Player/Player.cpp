#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"
#include "../Collision/CollisionAABB.h"
#include "../Stage/StageManager.h"
#include "../Stage/StageBase.h"

#define PLAYER_MOVE_SPEED 0.15f             // プレイヤーの移動速度
#define PLAYER_MOVE_DASH_SPEED 0.25f        // プレイヤーのダッシュ速度
#define PLAYER_MAX_STAMINA 100.0f           // プレイヤーの最大スタミナ
#define PLAYER_STAMINA_DRAIN 0.25f          // プレイヤーのスタミナ消費量
#define PLAYER_STAMINA_RECOVERY 0.1f        // プレイヤーのスタミナ回復量
#define PLAYER_STAMINA_RECOVERY_DELAY 30.0f // プレイヤーのスタミナ回復開始までの時間
#define PLAYER_STAMINA_EMPTY_DELAY 120.0f   // プレイヤーのスタミナ0になった後の待ち時間
#define PLAYER_STAMINA_EMPTY_RECOVERY 0.1f  // プレイヤーのスタミナ0になった後の回復量
#define ANIMATION_SPEED 1.0f                // プレイヤーのアニメーション速度

Player::Player()
{
    m_ModelHandle = 0;
    m_MoveSpeed = PLAYER_MOVE_SPEED;
    m_MoveDashSpeed = PLAYER_MOVE_DASH_SPEED;
    m_MaxStamina = PLAYER_MAX_STAMINA;
    m_Stamina = m_MaxStamina;
    m_StaminaRecoveryDelay = 0.0f;
    m_StaminaEmptyDelay = 0.0f;
	m_AnimationAttachIndex = 0;
	m_AnimationTotalTime = 0.0f;
	m_AnimationNowTime = 0.0f;
	m_IsLoopAnimation = false;
	m_NowAnimation = PLAYER_ANIMATION_WALK;
    m_Pos = VGet(0.0f, 0.0f, 0.0f);
    m_Rot = VGet(0.0f, 0.0f, 0.0f);
    m_Scale = VGet(0.0f, 0.0f, 0.0f);
    m_Move = VGet(0.0, 0.0f, 0.0f);
    m_OldPos = VGet(0.0, 0.0f, 0.0f);
    m_IsDashing = false;
	m_AABB = nullptr;
    m_SphereCollision = nullptr;
}

Player::~Player()
{
    Fin();
}

void Player::Init()
{
}

void Player::Load()
{
    m_ModelHandle = MV1LoadModel("Data/Player/Player.x");
}

void Player::Start()
{
	// プレイヤーの座標、スケール、移動量を初期化
    m_Pos = VGet(0.0f, 0.0f, 0.0f);
    m_Scale = VGet(1.0f, 1.0f, 1.0f);
    m_Move = VGet(0.0, 0.0f, 0.0f);

    // AABBの当たり判定を設定
    m_AABB = CollisionManager::GetInstance()->CreateAABB();
    m_AABB->SetTargetPos(&m_Pos);
    m_AABB->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
    m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));

    // 球の当たり判定を設定
	m_SphereCollision = CollisionManager::GetInstance()->CreateSphere();    // 球の当たり判定を作成
	m_SphereCollision->SetTargetPos(&m_Pos);                                // 球の中心をプレイヤーの座標に設定
	m_SphereCollision->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));                 // 球の中心をプレイヤーの中心に設定
	m_SphereCollision->SetRadius(1.25f);                                    // 球の半径を設定

	// 待機アニメーションを再生
	PlayAnimation(PLAYER_ANIMATION_WAIT, true);
}

void Player::Step()
{
	// プレイヤーの移動処理
    Camera* camera = (Camera*)CameraManager::GetInstance()->GetCamera(CAMERA);
	// カメラが存在しない場合は処理を終了
    if (camera == nullptr)
    {
        return;
    }
	// 移動量を初期化
    VECTOR move = VGet(0, 0, 0);
    
    // 入力に応じて移動量を計算
    if (Input::IsInputKey(Input::KEY_W))
    {
		// カメラの前方向ベクトルを取得して移動量に加算
        move = VAdd(move, camera->GetMoveFront());
		// 歩行アニメーション再生
        PlayAnimation(PLAYER_ANIMATION_WALK, true);
    }
    else
	{
        // 歩いていなければ待機アニメーションに戻す
		PlayAnimation(PLAYER_ANIMATION_WAIT, true);
    }

    if (Input::IsInputKey(Input::KEY_S))
    {
        move = VSub(move, camera->GetMoveFront());
    }

    if (Input::IsInputKey(Input::KEY_D))
    {
        move = VAdd(move, camera->GetMoveRight());
    }

    if (Input::IsInputKey(Input::KEY_A))
    {
        move = VSub(move, camera->GetMoveRight());
    }

	// ダッシュ中かどうかのフラグをリセット
    m_IsDashing = false;

	// 移動量が0でない場合、正規化して移動速度を掛ける
    if (VSize(move) > 0.0f)
    {
		move = VNorm(move);                     // 正規化
		float currentMoveSpeed = m_MoveSpeed;   // 現在の移動速度を通常速度に設定

		// 左シフトキーが押されていて、スタミナが残っている場合、ダッシュ中の速度に変更
        if (Input::IsInputKey(Input::KEY_LSHIFT) && m_Stamina > 0.0f && m_StaminaEmptyDelay <= 0.0f)
        {
			currentMoveSpeed = m_MoveDashSpeed; // ダッシュ中の速度に変更
			m_IsDashing = true;                 // ダッシュ中のフラグを立てる
			m_Stamina -= PLAYER_STAMINA_DRAIN;  // スタミナを消費

			// スタミナが0以下になった場合、スタミナを0にし、スタミナ0になった後の待ち時間を設定
            if (m_Stamina <= 0.0f)
            {
                m_Stamina = 0.0f;
                m_StaminaEmptyDelay = PLAYER_STAMINA_EMPTY_DELAY;
            }
			// スタミナ回復開始までの時間をリセット
            m_StaminaRecoveryDelay = PLAYER_STAMINA_RECOVERY_DELAY;
        }
		// 移動量に現在の移動速度を掛ける
        move = VScale(move, currentMoveSpeed);
		// 移動後の座標を計算
        VECTOR nextPos = VAdd(m_Pos, move);
		// ステージの当たり判定を取得
        StageBase* stage = StageManager::GetInstance()->GetStage();
		// ステージが存在する場合、球の当たり判定で衝突判定を行う
        if (stage != nullptr)
        {
			MV1_COLL_RESULT_POLY_DIM result = stage->CheckCollisionSphere(nextPos, m_SphereCollision->GetRadius());     // ステージと球の当たり判定を行う
			// 衝突していない場合、座標を更新
            if (result.HitNum == 0)
            {
                m_OldPos = m_Pos;
                m_Pos = nextPos;
            }
        }
        else
        {
            m_OldPos = m_Pos;
            m_Pos = nextPos;
        }
    }
	// スタミナ回復処理
    if (!m_IsDashing)
    {
        if (m_StaminaRecoveryDelay > 0.0f)
        {
            m_StaminaRecoveryDelay--;
        }
    }
	// スタミナが0になった後の待ち時間を減らす
    if (m_StaminaEmptyDelay > 0.0f)
    {
        m_StaminaEmptyDelay--;
    }
	// スタミナ回復処理
    if (!m_IsDashing && m_StaminaRecoveryDelay <= 0.0f)
    {
		// スタミナが0になった後の待ち時間がある場合、回復量を減らす
        if (m_StaminaEmptyDelay > 0.0f)
        {
            m_Stamina += PLAYER_STAMINA_EMPTY_RECOVERY;
        }
		// スタミナが0になった後の待ち時間がない場合、通常の回復量で回復
        else
        {
            m_Stamina += PLAYER_STAMINA_RECOVERY;
        }
		// スタミナが最大値を超えないように制限
        if (m_Stamina > m_MaxStamina)
        {
            m_Stamina = m_MaxStamina;
        }
    }
}

void Player::Update()
{
    if (m_ModelHandle != -1)
    {
        // カメラを取得
        Camera* camera = (Camera*)CameraManager::GetInstance()->GetCamera(CAMERA);

        // カメラが存在する場合、プレイヤーの向きをカメラに合わせる
        if (camera != nullptr)
        {
            m_Rot.y = camera->GetYaw();
        }

        // プレイヤーモデルの座標と回転を設定
        MV1SetPosition(m_ModelHandle, m_Pos);
        MV1SetRotationXYZ(m_ModelHandle, m_Rot);
    }

	// アニメーションの更新
	UpdateAnimation();
}

void Player::Draw()
{
    MV1DrawModel(m_ModelHandle);

	// スタミナバーの描画
	int barX = 20;          // スタミナバーのX座標
	int barY = 1000;        // スタミナバーのY座標
	int barWidth = 300;     // スタミナバーの幅
	int barHeight = 30;     // スタミナバーの高さ
	float staminaRate = m_Stamina / m_MaxStamina;                                           // スタミナの割合を計算
	int currentWidth = (int)(barWidth * staminaRate);                                       // 現在のスタミナバーの幅を計算
	DrawBox(barX, barY, barX + barWidth, barY + barHeight, GetColor(255, 255, 255), FALSE); // スタミナバーの枠を描画
	int barColor;           // スタミナバーの色を設定
    if (m_IsDashing)
    {
		barColor = GetColor(255, 0, 0);     // ダッシュ中は赤色
    }
    else
    {
		barColor = GetColor(255, 255, 0);   // 通常時は黄色
	}
	DrawBox(barX, barY, barX + currentWidth, barY + barHeight, barColor, TRUE); // スタミナバーの中身を描画
}

void Player::Fin()
{
    MV1DeleteModel(m_ModelHandle);
}

void Player::HitBlock(CollisionAABB* other)
{
    // 移動前の座標に設定する
    m_Pos = m_OldPos;
    MV1SetPosition(m_ModelHandle, m_Pos);
}

// アニメーションを再生する
void Player::PlayAnimation(PlayerAnimationType anim, bool isLoop)
{
	// すでに再生中のアニメーションと同じ場合は何もしない
    if(anim== m_NowAnimation)
    {
        return;
	}

	// すでにアタッチされているアニメーションをデタッチする
	MV1DetachAnim(m_ModelHandle, m_AnimationAttachIndex);

	// アニメーションをアタッチする
	m_AnimationAttachIndex = MV1AttachAnim(m_ModelHandle, anim);

	// アニメーションの総時間を取得する
	m_AnimationTotalTime = MV1GetAttachAnimTotalTime(m_ModelHandle, m_AnimationAttachIndex);

	// 現在の再生時間を0にする
	m_AnimationNowTime = 0.0f;

    // ループ設定
	m_IsLoopAnimation = isLoop;

	// 再生中のアニメーションを設定
	m_NowAnimation = anim;
}

// アニメーションを更新する
void Player::UpdateAnimation()
{
	//  アニメーションの再生時間を設定する
	MV1SetAttachAnimTime(m_ModelHandle, m_AnimationAttachIndex, m_AnimationNowTime);

	// 再生時間を進める
	m_AnimationNowTime += ANIMATION_SPEED;

	// 末尾まで再生したか
    if (m_AnimationNowTime > m_AnimationTotalTime)
    {
		// ループ設定なら冒頭へ戻す
        if (m_IsLoopAnimation)
        {
			m_AnimationNowTime = 0.0f;
        }
		// ループでなければ末尾で止める
        else
        {
			m_AnimationNowTime = m_AnimationTotalTime;
        }
    }
}