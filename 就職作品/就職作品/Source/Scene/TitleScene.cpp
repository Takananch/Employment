#include "DxLib.h"
#include "TitleScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../Sound/Sound.h"
#include <math.h>

// PressSpaceKeyの点滅スピード
#define PRESS_SPACE_KEY_BLINK_SPEED (0.04f)

// 画像ハンドル
int g_TitleLogoHandle = 0;
int g_PressSpaceKeyHandle = 0;

// PressSpaceKey点滅用変数
float g_PressSpaceKeyAlpha = 0.0f;	// アルファ値
float g_PressSpaceKeyRadian = 0.0f;	// cos関数に渡すラジアン値

TitleScene::TitleScene() : SceneBase()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	g_TitleLogoHandle = 0;
	g_PressSpaceKeyHandle = 0;
	g_PressSpaceKeyAlpha = 0.0f;
	g_PressSpaceKeyRadian = 0.0f;
}

void TitleScene::Load()
{
	// 各画像をロード
	g_TitleLogoHandle = LoadGraph("Data/UI/TheDeadlyMiners.png");
	g_PressSpaceKeyHandle = LoadGraph("Data/UI/PressSpaceKey.png");
}

void TitleScene::Start()
{
}

void TitleScene::Step()
{
	// sin波の値からPressSpaceKeyのアルファ値（透明度）を計算する
	// sinfが-1～1の値を返却するので加工して0～1の値にしている
	g_PressSpaceKeyAlpha = (sinf(g_PressSpaceKeyRadian) + 1) / 2;

	// ラジアン値を点滅速度で加算
	g_PressSpaceKeyRadian += PRESS_SPACE_KEY_BLINK_SPEED;

	// ラジアン値は0～2πをループさせる
	if (g_PressSpaceKeyRadian > DX_TWO_PI_F)
	{
		g_PressSpaceKeyRadian -= DX_TWO_PI_F;
	}

	// Spaceキーが押されたらプレイシーンへ
	if (Input::IsTriggerKey(Input::InputKey::KEY_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene(PLAY);
	}
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
	// DrawFormatString(0, 0, GetColor(255, 255, 255), "タイトルシーン", 0);
	// タイトルロゴ描画
	DrawGraph(0, 0, g_TitleLogoHandle, TRUE);
	// 点滅のためにブレンドモードを設定する(DXLibの仕様が0～255で指定するので加工する)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(g_PressSpaceKeyAlpha * 255));
	// PressSpaceKey描画
	DrawGraph(0, 150, g_PressSpaceKeyHandle, TRUE);
	// ブレンドモードを戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::Fin()
{
	DeleteGraph(g_TitleLogoHandle);
	DeleteGraph(g_PressSpaceKeyHandle);
}