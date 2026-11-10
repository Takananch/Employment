#include "DxLib.h"
#include "Input.h"

// 入力ビットフラグ
int g_InputState;
// 前回の入力ビット
int g_PrevInputState;

// マウスの移動量
int g_MouseMoveX;
int g_MouseMoveY;

namespace Input
{
	void Init()
	{
		g_InputState = 0;
		g_PrevInputState = 0;

		g_MouseMoveX = 0;	// マウスの移動量を初期化
		g_MouseMoveY = 0;	// マウスの移動量を初期化
	}

	void Update()
	{
		// マウスの移動量を取得
		int mouseX;
		int mouseY;
		// マウスの座標を取得
		GetMousePoint(&mouseX, &mouseY);
		// マウスの移動量を計算
		g_MouseMoveX = mouseX - 960;
		g_MouseMoveY = mouseY - 540;
		// マウスの座標を画面中央に戻す
		SetMousePoint(960, 540);
		// 前回の入力状態を保存
		g_PrevInputState = g_InputState;
		g_InputState = 0;

		// 前回の入力を覚えておく
		// g_PrevInputState = g_InputState;

		// 入力状態をクリア
		g_InputState = 0;

		// 入力状態をビットフラグで設定
		if (CheckHitKey(KEY_INPUT_UP))
		{
			g_InputState |= KEY_UP;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			g_InputState |= KEY_DOWN;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			g_InputState |= KEY_LEFT;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			g_InputState |= KEY_RIGHT;
		}
		if (CheckHitKey(KEY_INPUT_LSHIFT))
		{
			g_InputState |= KEY_LSHIFT;
		}
		if (CheckHitKey(KEY_INPUT_W))
		{
			g_InputState |= KEY_W;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			g_InputState |= KEY_A;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			g_InputState |= KEY_S;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			g_InputState |= KEY_D;
		}
		if(CheckHitKey(KEY_INPUT_SPACE))
		{
			g_InputState |= KEY_SPACE;
		}
		if (CheckHitKey(KEY_INPUT_P))
		{
			g_InputState |= KEY_P;
		}
		if (CheckHitKey(KEY_INPUT_O))
		{
			g_InputState |= KEY_O;
		}
		if (CheckHitKey(KEY_INPUT_E))
		{
			g_InputState |= KEY_E;
		}
	}

	void Draw()
	{
	}

	void Fin()
	{
	}

	bool IsInputKey(InputKey key)
	{
		return g_InputState & key;
	}

	bool IsTriggerKey(InputKey key)
	{
		return (g_InputState & key) && !(g_PrevInputState & key);
	}
	// マウスの移動量を取得
	int Input::GetMouseMoveX()
	{
		return g_MouseMoveX;
	}
	// マウスの移動量を取得
	int Input::GetMouseMoveY()
	{
		return g_MouseMoveY;
	}
}
