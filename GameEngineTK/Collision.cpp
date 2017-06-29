#include "Collision.h"
using namespace DirectX::SimpleMath;

//‹…‚Æ‹…‚Æ‚Ì“–‚½‚è”»’è
bool CheakSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//‹…A‚ÆB‚Ì’†SÀ•W‚Ì·‚ğŒvZ‚·‚é
	Vector3 sub = sphereB.Center - sphereA.Center;

	float distance_Square;
	//O•½•û‚Ì’è—‚ÅAƒxƒNƒgƒ‹‚Ì’·‚³‚ğŒvZ‚·‚é
	distance_Square = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//”¼Œa‚Ì˜a‚Ì“ñæ
	float radius_Square;

	radius_Square = sphereA.Radius + sphereB.Radius;
	radius_Square = radius_Square * radius_Square;

	//‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚Î“–‚½‚Á‚Ä‚¢‚È‚¢
	if (distance_Square > radius_Square)
	{
		return false;
	}

	return true;
}