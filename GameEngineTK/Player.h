#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"
#include "CollisionNode.h"

class Player : public Obj3d
{
public:
	Player(DirectX::Keyboard* keyboard);
	~Player();
	//初期化処理
	void Initialize();

	//更新処理
	void Update();

	// 行列の計算
	void Calc();

	//描画処理
	void Draw();

	//ミサイルを発射する関数
	void FireBullet();

	//ミサイルを再装填する関数
	void ResetBullet();

	//プレイヤーの挙動
	void Action();

	//プレイヤーの移動を取得する
	const DirectX::SimpleMath::Vector3& GetRot();

	//プレイヤーの角度を取得する
	const DirectX::SimpleMath::Vector3& GetTrans();

	//プレイヤーの移動をセットする
	void SetRot(const DirectX::SimpleMath::Vector3& rotation);

	//プレイヤーの角度をセットする
	void SetTrans(const DirectX::SimpleMath::Vector3& translation);

	//弾丸用の当たり判定を取得する
	const SphereNode& GetCollisionNodeBullet_l() { return m_CollisionNodeBullet_l; }

	//弾丸用の当たり判定を取得する
	const SphereNode& GetCollisionNodeBullet_r() { return m_CollisionNodeBullet_r; }

private:
	//自機の3Dオブジェクト
	std::vector<Obj3d> m_ObjPlayer;

	// キーボード
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// サイン用の引数となる角度
	float m_sinAngle;

	//ミサイル攻撃を管理するフラグ
	bool m_weapon_flag;
	float m_timer;

	//ミサイルの速度ベクトル
	DirectX::SimpleMath::Vector3 m_BulletVel_l;
	DirectX::SimpleMath::Vector3 m_BulletVel_r;

	//自機パーツ
	enum PLAYERPARTS
	{
		BODY,
		L_WING,
		R_WING,
		L_ENGINE,
		R_ENGINE,
		L_WEAPON,
		R_WEAPON,

		PLAYER_PARTS_NUM
	};

	//弾丸用の当たり判定
	SphereNode m_CollisionNodeBullet_l;
	SphereNode m_CollisionNodeBullet_r;
};