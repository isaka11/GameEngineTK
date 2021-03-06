#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <vector>
#include "Obj3d.h"
#include "CollisionNode.h"

class Enemy : public Obj3d
{
public:
	Enemy();

	~Enemy();
	//初期化処理
	void Initialize();

	//更新処理
	void Update();

	//行列の計算
	void Calc();

	//描画処理
	void Draw();

	//エネミーの挙動
	void Action();

	//エネミーの移動を取得する
	const DirectX::SimpleMath::Vector3& GetRot();

	//エネミーの角度を取得する
	const DirectX::SimpleMath::Vector3& GetTrans();

	//エネミーの移動をセットする
	void SetRot(const DirectX::SimpleMath::Vector3& rotation);

	//エネミーの角度をセットする
	void SetTrans(const DirectX::SimpleMath::Vector3& translation);

	//エネミーの当たり判定を取得する
	const SphereNode& GetCollisionNodeEnemy() { return m_CollisionNodeEnemy; }

private:
	//自機の3Dオブジェクト
	std::vector<Obj3d> m_ObjEnemy;

	// サイン用の引数となる角度
	float m_sinAngle;

	//タイマー
	int m_Timer;

	//目標角度
	float m_DistAngle;

	//ミサイル攻撃を管理するフラグ
	bool m_weapon_flag;
	bool m_a_flag;

	//自機パーツ
	enum ENEMYPARTS
	{
		BODY,
		L_WING,
		R_WING,
		L_ENGINE,
		R_ENGINE,
		L_WEAPON,
		R_WEAPON,

		ENEMY_PARTS_NUM
	};

	//エネミーの当たり判定
	SphereNode m_CollisionNodeEnemy;
};