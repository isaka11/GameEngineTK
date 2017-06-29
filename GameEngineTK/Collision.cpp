#include "Collision.h"
using namespace DirectX::SimpleMath;

//���Ƌ��Ƃ̓����蔻��
bool CheakSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//��A��B�̒��S���W�̍����v�Z����
	Vector3 sub = sphereB.Center - sphereA.Center;

	float distance_Square;
	//�O�����̒藝�ŁA�x�N�g���̒������v�Z����
	distance_Square = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//���a�̘a�̓��
	float radius_Square;

	radius_Square = sphereA.Radius + sphereB.Radius;
	radius_Square = radius_Square * radius_Square;

	//���������a�̘a���傫����Γ������Ă��Ȃ�
	if (distance_Square > radius_Square)
	{
		return false;
	}

	return true;
}