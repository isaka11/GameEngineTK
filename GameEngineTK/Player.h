#pragma once

#include <d3d11.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"

class Player : public Obj3d
{
public:
	Player();
	~Player();
	//初期化処理
	void Initialize();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	//プレイヤーの挙動
	void Action();

	//キー情報を取得する
	DirectX::Keyboard* GetKeyboard();

	//プレイヤーの移動を取得する
	const DirectX::SimpleMath::Vector3& GetRot();

	//プレイヤーの角度を取得する
	const DirectX::SimpleMath::Vector3& GetTrans();

	//プレイヤーの移動をセットする
	void SetRot(const DirectX::SimpleMath::Vector3& rotation);

	//プレイヤーの角度をセットする
	void SetTrans(const DirectX::SimpleMath::Vector3& translation);

private:
	//自機の3Dオブジェクト
	std::vector<Obj3d> m_ObjPlayer;

	//キーボード
	std::unique_ptr<DirectX::Keyboard> keyboard;

	//ミサイル攻撃を管理するフラグ
	bool m_weapon_flag;
	bool m_a_flag;

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
};