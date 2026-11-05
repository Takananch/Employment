#pragma once

namespace Input
{
	// 入力ボタン定義
	enum InputKey
	{
		KEY_UP = (1 << 0),		// 0x0000 0000 0001
		KEY_DOWN = (1 << 1),	// 0x0000 0000 0010
		KEY_LEFT = (1 << 2),	// 0x0000 0000 0100
		KEY_RIGHT = (1 << 3),	// 0x0000 0000 1000
		KEY_LSHIFT = (1 << 4),	// 0x0000 0001 0000
		KEY_W = (1 << 5),		// 0x0000 0010 0000
		KEY_A = (1 << 6),		// 0x0000 0100 0000
		KEY_S = (1 << 7),		// 0x0000 1000 0000
		KEY_D = (1 << 8),		// 0x0001 0000 0000
		KEY_SPACE = (1 << 9),	// 0x0010 0000 0000
		KEY_P = (1 << 10),		// 0x0100 0000 0000
		KEY_O = (1 << 11),		// 0x1000 0000 0000
		KEY_E = (1 << 12)		// 0x0001 0000 0000 0000
	};

	// 関数
	void Init();
	void Update();
	void Draw();
	void Fin();

	// キー入力判定
	bool IsInputKey(InputKey key);	
	// キー押した瞬間判定
	bool IsTriggerKey(InputKey key);
	// マウスの移動量を取得
	int GetMouseMoveX();
	int GetMouseMoveY();
}
