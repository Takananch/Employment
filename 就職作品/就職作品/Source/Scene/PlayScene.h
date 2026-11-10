#pragma once
#include "SceneBase.h"

//class BackGround;
class Minecart;
class Money;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

private:
	float m_SubLevel1Timer;	// サブレベル1のタイマー
	float m_SubLevel1Alpha;	// サブレベル1のアルファ値

	Minecart* m_Minecart;
	Money* m_Money;     // 納品金額の管理
};