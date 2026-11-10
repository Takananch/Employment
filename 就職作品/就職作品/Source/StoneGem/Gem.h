#pragma once
#include "DxLib.h"

class Player;

// 宝石の種類
enum GemType
{
    GEM_TYPE_NORMAL,
};

class Gem
{
public:
    Gem();
    ~Gem();

    bool Load();
    void Step(Player* player);
    void Draw();
    void Fin();

    void SetPos(VECTOR pos);
    VECTOR GetPos() const { return m_Pos; }

	int GetValue() const { return m_Value; }                    // 宝石の価値を取得
	void SetValue(int value) { m_Value = value; }               // 宝石の価値を設定
	void SetVisible(bool visible) { m_IsVisible = visible; }    // 宝石の表示状態を設定
	bool IsVisible() const { return m_IsVisible; }              // 宝石の表示状態を取得
	bool IsInteractable() const { return m_IsInteractable; }	// 宝石がインタラクト可能かどうかを取得
	bool IsPickedUp() const { return m_IsPickUp; }			// 宝石が取得されたかどうかを取得

private:
	int m_ModelHandle;          // 宝石のモデルハンドル
	VECTOR m_Pos;               // 宝石の座標
	int m_Value;                // 宝石の価値
	GemType m_Type;             // 宝石の種類
	bool m_IsVisible;           // 宝石が表示されるかどうか
	bool m_IsInteractable;      // 宝石がインタラクト可能かどうか
	bool m_IsPickUp;          // 宝石が取得されたかどうか
	float m_InteractDistance;   // プレイヤーと宝石のインタラクト可能距離
};