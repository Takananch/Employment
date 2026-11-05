#include "Stage.h"
#include "DxLib.h"
#include "../Collision/CollisionManager.h"

Stage::Stage()
{
	m_MinecartHandle = 0;
	m_Stage1Handle = 0;
	m_CollisionHandle = 0;
	m_CollisionResult = {};
}

Stage::~Stage()
{
	Fin();
}

void Stage::Load()
{
	// 描画するモデルをロード
	m_MinecartHandle = MV1LoadModel("Data/Stage/Minecart.x");
	m_Stage1Handle = MV1LoadModel("Data/Stage/Stage1.x");
	// 当たり判定用のモデルをロード
	m_CollisionHandle = MV1LoadModel("Data/Stage/Stage1Collision.x");
}

void Stage::Start()
{
	// 当たり判定用のモデルの衝突情報を構築
	MV1SetupCollInfo(m_CollisionHandle);
}

void Stage::Draw()
{
	MV1DrawModel(m_MinecartHandle);
	MV1DrawModel(m_Stage1Handle);
	// MV1DrawModel(m_CollisionHandle);	// デバッグ用に当たり判定用のモデルを描画する場合はコメントアウトを外す
}

void Stage::Fin()
{
	// 構築した衝突情報を削除
	MV1TerminateCollInfo(m_CollisionHandle);
	// 画像を削除
	MV1DeleteModel(m_MinecartHandle);
	MV1DeleteModel(m_Stage1Handle);
	// 当たり判定用のモデルも削除
	MV1DeleteModel(m_CollisionHandle);
}

MV1_COLL_RESULT_POLY_DIM Stage::CheckCollisionSphere(VECTOR pos, float r)
{
	// ステージと球の当たり判定
	return MV1CollCheck_Sphere(m_CollisionHandle, -1, pos, r);
}