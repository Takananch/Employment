#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"


// 静的変数の初期化
CollisionManager* CollisionManager::m_Instance = nullptr;

// コンストラクタ
CollisionManager::CollisionManager()
{
	m_AABB = {};
	m_Sphere = {};
}

// デストラクタ
CollisionManager::~CollisionManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void CollisionManager::Draw()
{
	// m_AABBを先頭から末尾までまわす範囲for文
	for (CollisionAABB* aabb : m_AABB)
	{
		if (aabb)
		{
			aabb->Draw();
		}
	}

	// m_Sphereを先頭から末尾までまわす範囲for文
	for (CollisionSphere* sphere : m_Sphere)
	{
		if (sphere)
		{
			sphere->Draw();
		}
	}
}

void CollisionManager::Fin()
{
	for (CollisionAABB* aabb : m_AABB)
	{
		if (aabb)
		{
			delete aabb;
		}
	}
	m_AABB.clear();

	for (CollisionSphere* sphere : m_Sphere)
	{
		if (sphere)
		{
			delete sphere;
		}
	}
	m_Sphere.clear();
}

CollisionAABB* CollisionManager::CreateAABB()
{
	CollisionAABB* aabb = new CollisionAABB;
	m_AABB.push_back(aabb);

	return aabb;
}


// Sphereを生成する
CollisionSphere* CollisionManager::CreateSphere()
{
	CollisionSphere* sphere = new CollisionSphere;
	m_Sphere.push_back(sphere);

	return sphere;
}
