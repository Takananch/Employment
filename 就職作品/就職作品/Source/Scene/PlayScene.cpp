#include "DxLib.h"
#include "PlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Camera/CameraManager.h"
#include "../Collision/CollisionManager.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"
#include "../Sound/Sound.h"
#include "../Stage/StageManager.h"
#include "../StoneGem/StoneManager.h"

int g_CenterPixelHandle = 0;		// 画面中心の点画像のハンドル
int g_UI_TargetAmountHandle = 0;	// 目標額を表示するUI画像のハンドル
int g_UI_OperationHandle = 0;		// 操作方法を表示するUI画像のハンドル
int g_SubLevel1Handle = 0;			// SubLevel1画像のハンドル
int g_UI_EKeyHandle = 0;			// Eキーを表示するUI画像のハンドル

PlayScene::PlayScene() : SceneBase()
{
	m_SubLevel1Timer = 0.0f;	// サブレベル1画像のタイマー
	m_SubLevel1Alpha = 255.0f;	// サブレベル1画像のアルファ値
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	g_CenterPixelHandle = 0;
	g_UI_TargetAmountHandle = 0;
	g_UI_OperationHandle = 0;
	g_SubLevel1Handle = 0;
	g_UI_EKeyHandle = 0;
	m_SubLevel1Timer = 0.0f;		// サブレベル1画像のタイマーを初期化
	m_SubLevel1Alpha = 255.0f;		// サブレベル1画像のアルファ値を初期化

	CollisionManager::CreateInstance();

	StoneManager::CreateInstance();
	StoneManager::GetInstance()->Init();

	StageManager::CreateInstance();
	StageManager::GetInstance()->Init();

	PlayerManager::CreateInstance();
	PlayerManager* playerManager = PlayerManager::GetInstance();
	playerManager->CreatePlayer();
	playerManager->Init();

	CameraManager::CreateInstance();
	CameraManager::GetInstance()->CreateCamera(CAMERA);
	CameraManager::GetInstance()->Init();
}

void PlayScene::Load()
{
	g_CenterPixelHandle = LoadGraph("Data/UI/CenterPixel.png");				// 画面中心の点画像をロード
	g_UI_TargetAmountHandle = LoadGraph("Data/UI/UI_TargetAmount.png");		// 目標額を表示するUI画像をロード
	g_UI_OperationHandle = LoadGraph("Data/UI/UI_Operation.png");			// 操作方法を表示するUI画像をロード
	g_SubLevel1Handle = LoadGraph("Data/UI/SubLevel1.png");					// SubLevel1画像をロード
	g_UI_EKeyHandle = LoadGraph("Data/UI/UI_EKey.png");						// Eキーを表示するUI画像をロード

	PlayerManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	StageManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	StageManager::GetInstance()->Start();
	PlayerManager::GetInstance()->Start();
	CameraManager::GetInstance()->Start();
}

void PlayScene::Step()
{
	StageManager::GetInstance()->Step();


	PlayerManager::GetInstance()->Step();
	StoneManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();

	// SubLevel1画像の表示時間を計測
	if (m_SubLevel1Timer < 180.0f)
	{
		m_SubLevel1Timer++;
	}
	// 2秒経過後、画像を徐々に透明にする
	if (m_SubLevel1Timer > 120.0f)
	{
		m_SubLevel1Alpha -= 4.25f;

		if (m_SubLevel1Alpha < 0.0f)
		{
			m_SubLevel1Alpha = 0.0f;
		}
	}
}

void PlayScene::Update()
{
	StageManager::GetInstance()->Update();
	PlayerManager::GetInstance()->Update();
	StoneManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	StageManager::GetInstance()->Draw();
	StoneManager::GetInstance()->Draw();
	PlayerManager::GetInstance()->Draw();
	CameraManager::GetInstance()->Draw();

	// UIの描画
	DrawGraph(0, 0, g_CenterPixelHandle, TRUE);
	DrawGraph(0, 0, g_UI_TargetAmountHandle, TRUE);
	DrawGraph(0, 0, g_UI_OperationHandle, TRUE);

	// 目標額の描画
	DrawString(350, 55, "%d/283", GetColor(0, 0, 0));

	// Eキー画像の描画
	if (StoneManager::GetInstance()->IsInteractable())
	{
		DrawGraph(0, 0, g_UI_EKeyHandle, TRUE);
	}

	// SubLevel1画像の描画
	if (m_SubLevel1Alpha > 0.0f)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_SubLevel1Alpha);	// アルファブレンドモードを設定
		DrawGraph(0, 0, g_SubLevel1Handle, TRUE);						// SubLevel1画像を描画
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);					// ブレンドモードを元に戻す
	}
}

void PlayScene::Fin()
{
	StageManager::DeleteInstance();
	PlayerManager::DeleteInstance();
	StoneManager::DeleteInstance();
	CameraManager::DeleteInstance();
	CollisionManager::DeleteInstance();

	DeleteGraph(g_CenterPixelHandle);
	DeleteGraph(g_UI_TargetAmountHandle);
	DeleteGraph(g_UI_OperationHandle);
	DeleteGraph(g_SubLevel1Handle);
	DeleteGraph(g_UI_EKeyHandle);
}