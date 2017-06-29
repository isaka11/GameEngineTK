#pragma once

#include<d3d11_1.h>
#include<SimpleMath.h>

//��
class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;	//���S���W
	float Radius;							//���a

	//�R���X�g���N�^
	Sphere()
	{
		//���a1m
		Radius = 1.0f;
	}
};

//����
class Segment
{
public:
	DirectX::SimpleMath::Vector3 start;		//�n�_���W
	DirectX::SimpleMath::Vector3 end;		//�I�_���W
};

bool CheakSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
