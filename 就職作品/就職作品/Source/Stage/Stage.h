#pragma once
#include "DxLib.h"

class Stage
{
public:
	Stage();
	~Stage();

public:
	void Load();
	void Start();
	void Draw();
	void Fin();

	MV1_COLL_RESULT_POLY_DIM GetHitResult() const { return m_CollisionResult; }

	MV1_COLL_RESULT_POLY_DIM CheckCollisionSphere(VECTOR pos, float r);

private:
	int m_MinecartHandle;
	int m_Stage1Handle;
	int m_CollisionHandle;
	MV1_COLL_RESULT_POLY_DIM m_CollisionResult;
};