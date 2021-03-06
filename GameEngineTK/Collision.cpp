#include "Collision.h"
using namespace DirectX::SimpleMath;

//球と球との当たり判定
bool CheakSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//球AとBの中心座標の差を計算する
	Vector3 sub = sphereB.Center - sphereA.Center;

	float distance_Square;
	//三平方の定理で、ベクトルの長さを計算する
	distance_Square = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//半径の和の二乗
	float radius_Square;

	radius_Square = sphereA.Radius + sphereB.Radius;
	radius_Square = radius_Square * radius_Square;

	//距離が半径の和より大きければ当たっていない
	if (distance_Square > radius_Square)
	{
		return false;
	}

	return true;
}