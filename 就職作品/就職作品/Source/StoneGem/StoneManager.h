#pragma once
#include "DxLib.h"
#include <vector>

class Stone;

class StoneManager
{
public:
	static void CreateInstance();
	static void DeleteInstance();
	static StoneManager* GetInstance();

	StoneManager();
	~StoneManager();

	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	Stone* CreateStone(VECTOR pos);		// 岩を作成
	void ClearStones();              // 岩をすべて削除
	bool IsInteractable() const;		// インタラクト可能な岩があるか取得

private:
	static StoneManager* m_Instance;	// シングルトンインスタンス
	std::vector<Stone*> m_Stones;		// 岩のインスタンス一覧
};