#pragma once

#include <d3d11.h>
#include <Keyboard.h>
#include "CollisionNode.h"

class Player
{
public:
	//自機パーツ
	enum PLAYERPARTS
	{
		BODY,
		L_WING,
		R_WING,
		L_ENGINE,
		R_ENGINE,

		PLAYER_PARTS_NUM
	};

	//定数宣言
	const float PLAYER_SPEED = 0.15f;			//プレイヤーの移動速度
	const float GRAVITY_ACC = 0.03f;			//重力加速度<m/frame^2>
	const float JUMP_SPEED_FIRST = 0.5f;		//ジャンプ初速<m/frame>
	const float JUMP_SPEED_MAX = 0.3f;			//落下速度制限<m/frame>

	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//初期化処理
	void Initialize();

	//更新処理
	void Update();

	//行列の計算
	void Calc();

	//描画処理
	void Draw();

	//プレイヤーの移動を取得する
	const DirectX::SimpleMath::Vector3& GetRot();

	//プレイヤーの角度を取得する
	const DirectX::SimpleMath::Vector3& GetTrans();

	//プレイヤーのワールド行列を取得する
	const DirectX::SimpleMath::Matrix& GetWor();

	//プレイヤーの移動をセットする
	void SetRot(const DirectX::SimpleMath::Vector3& rotation);

	//プレイヤーの角度をセットする
	void SetTrans(const DirectX::SimpleMath::Vector3& translation);

	//プレイヤーの当たり判定(排斥処理用)を取得する
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; }

	//プレイヤーの速度を取得する
	const DirectX::SimpleMath::Vector3 GetVelocity() { return m_Velocity; }

	//ジャンプ開始
	void StartJump();

	//ジャンプ終了
	void StopJump();

	//ジャンプ中フラグを取得する
	bool Get_Jump() { return m_isJump; }

	//モード切り替えフラグを取得する
	bool Get_Mode() { return m_mode_flag; }

	//モード切り替えフラグをセットする
	void Set_Mode(bool flag) { m_mode_flag = flag; }

	bool GetFirstPosFlag() { return m_first_pos_flag; }

	void SetFirstPosFlag(bool flag) { m_first_pos_flag = flag; }

private:
	//自機の3Dオブジェクト
	std::vector<Obj3d> m_ObjPlayer;

	//サイン用の引数となる角度
	float m_sinAngle;

	//全身の当たり判定(排斥処理用)
	SphereNode m_CollisionNodeBody;

	//速度
	DirectX::SimpleMath::Vector3 m_Velocity;

	//ジャンプ中フラグ
	bool m_isJump;

	//モード切り替えフラグ
	bool m_mode_flag;

	//初期状態を管理するフラグ
	bool m_first_pos_flag;
};