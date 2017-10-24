#include "Player.h"
#include "ADX2Le.h"
#include "CueSheet_0.h"
#include "KeyboardLibrary.h"

#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Library;

//コンストラクタ
Player::Player()
{
	m_sinAngle = 0.0f;
	m_mode_flag = false;
	m_first_pos_flag = false;
	Initialize();
}

//デストラクタ
Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{
	//自機パーツの読み込み
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[BODY].LoadModel(L"Resources/body.cmo");
	m_ObjPlayer[L_WING].LoadModel(L"Resources/LeftWing.cmo");
	m_ObjPlayer[R_WING].LoadModel(L"Resources/RightWing.cmo");
	m_ObjPlayer[L_ENGINE].LoadModel(L"Resources/Engine.cmo");
	m_ObjPlayer[R_ENGINE].LoadModel(L"Resources/Engine.cmo");

	//パーツを親子関係をセット
	m_ObjPlayer[L_WING].SetParent(&m_ObjPlayer[BODY]);
	m_ObjPlayer[R_WING].SetParent(&m_ObjPlayer[BODY]);
	m_ObjPlayer[L_ENGINE].SetParent(&m_ObjPlayer[BODY]);
	m_ObjPlayer[R_ENGINE].SetParent(&m_ObjPlayer[BODY]);

	//親からのオフセット(座標のずらし分)をセット
	m_ObjPlayer[BODY].SetTranslation(Vector3(0.0f, 1.0f, 0.0f));
	m_ObjPlayer[L_WING].SetTranslation(Vector3(0.0f, 0.0f, 0.0f));
	m_ObjPlayer[R_WING].SetTranslation(Vector3(0.0f, 0.0f, 0.0f));
	m_ObjPlayer[L_ENGINE].SetTranslation(Vector3(-0.1f, 0.0f, 0.5f));
	m_ObjPlayer[L_ENGINE].SetScale(Vector3(0.75f, 0.75f, 0.75f));
	m_ObjPlayer[R_ENGINE].SetTranslation(Vector3(0.1f, 0.0f, 0.5f));
	m_ObjPlayer[R_ENGINE].SetScale(Vector3(0.75f, 0.75f, 0.75f));

	//当たり判定を設定する(排斥処理用)
	m_CollisionNodeBody.Initialize();
	m_CollisionNodeBody.SetParent(&m_ObjPlayer[BODY]);
	m_CollisionNodeBody.SetTrans(Vector3(0, 0.5f, 0));
	m_CollisionNodeBody.SetLocalRadius(Vector3(0.5f, 0.5f, 0.5f));

	//ジャンプ中フラグの初期化
	m_isJump = false;

	ADX2Le::Initialize("Sounds\\CueSheet_0.acb");
	ADX2Le::LoadAcb("Sounds\\CueSheet_0.acb", "Sounds\\CueSheet_0.awb");
}

//更新処理
void Player::Update()
{
	KeyboardLibrary* key = KeyboardLibrary::GetInstance();

	//キーボードの更新
	key->Update();

	//Cキーで2D,3Dを切り替える
	if (key->IsKeyTrigger(Keyboard::Keys::C))
	{
		ADX2Le::Play(CRI_CUESHEET_0_CHANGE);

		if (m_first_pos_flag == false)
		{
			m_first_pos_flag = true;
		}

		if (m_mode_flag == false)
		{
			m_mode_flag = true;
		}
		else if (m_mode_flag == true)
		{
			m_mode_flag = false;
		}
	}

	//スペースキーでジャンプする
	if (key->IsKeyTrigger(Keyboard::Keys::Space))
	{
		if (m_Velocity.y >= 0)
		{
			ADX2Le::Play(CRI_CUESHEET_0_JUMP);

			//ジャンプ開始
			StartJump();
		}
	}

	//重力
	m_Velocity.y -= GRAVITY_ACC;

	//速度制限
	if (m_Velocity.y <= -JUMP_SPEED_MAX)
	{
		m_Velocity.y = -JUMP_SPEED_MAX;
	}

	//現在の座標・回転角を取得
	Vector3 trans = m_ObjPlayer[BODY].GetTranslation();

	//移動
	trans += m_Velocity;

	//移動した座標を反映
	m_ObjPlayer[BODY].SetTranslation(trans);

	//2Dモードの処理
	if (m_mode_flag == false)
	{
		//Z軸を2Dに戻す
		//this->SetTrans(Vector3(this->GetTrans().x, this->GetTrans().y, 0.0f));

		//左キーを押すと
		if (key->IsKeyPress(Keyboard::Keys::Left))
		{
			//移動量のベクトル
			Vector3 moveV(-PLAYER_SPEED, 0.0f, 0.0f);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationX(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//自機の座標を移動させる
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}
		//右キーを押すと
		if (key->IsKeyPress(Keyboard::Keys::Right))
		{
			//移動量のベクトル
			Vector3 moveV(PLAYER_SPEED, 0.0f, 0.0f);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationX(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//自機の座標を移動させる
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}
	}

	//3Dモードの処理
	else
	{
		//上キーを押すと
		if (key->IsKeyPress(Keyboard::Keys::Up))
		{
			//移動量のベクトル
			Vector3 moveV(PLAYER_SPEED, 0.0f, 0.0f);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationZ(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//自機の座標を移動させる
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}

		//下キーを押すと
		if (key->IsKeyPress(Keyboard::Keys::Down))
		{
			//移動量のベクトル
			Vector3 moveV(-PLAYER_SPEED, 0.0f, 0.0f);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationZ(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//自機の座標を移動させる
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}

		//左キーを押すと
		if (key->IsKeyPress(Keyboard::Keys::Left))
		{
			//移動量のベクトル
			Vector3 moveV(0.0f, 0.0f, -PLAYER_SPEED);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationX(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//自機の座標を移動させる
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}
		//右キーを押すと
		if (key->IsKeyPress(Keyboard::Keys::Right))
		{
			//移動量のベクトル
			Vector3 moveV(0.0f, 0.0f, PLAYER_SPEED);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationX(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//自機の座標を移動させる
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}
	}

	//行列更新
	Calc();
}

//行列更新
void Player::Calc()
{
	//プレイヤーの更新処理
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}

	//当たり判定の更新処理
	m_CollisionNodeBody.Update();
}

//描画
void Player::Draw()
{
	////各パーツの描画
	//for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	//{
	//	it->Draw();
	//}

	m_CollisionNodeBody.Draw();
}

//プレイヤーの移動を取得する
const DirectX::SimpleMath::Vector3& Player::GetRot()
{
	return m_ObjPlayer[BODY].GetRotation();
}

//プレイヤーの角度を取得する
const DirectX::SimpleMath::Vector3& Player::GetTrans()
{
	return m_ObjPlayer[BODY].GetTranslation();
}

//プレイヤーの角度をセットする
void Player::SetTrans(const Vector3& translation)
{
	m_ObjPlayer[BODY].SetTranslation(translation);
}

//プレイヤーの移動をセットする
void Player::SetRot(const Vector3& rotation)
{
	m_ObjPlayer[BODY].SetRotation(rotation);
}

//プレイヤーのワールド行列を取得する
const DirectX::SimpleMath::Matrix& Player::GetWor()
{
	return m_ObjPlayer[BODY].GetWorld();
}

//ジャンプ開始
void Player::StartJump()
{
	//ジャンプ中でないか
	if (!m_isJump)
	{
		// 上方向の初速を設定
		m_Velocity.y = JUMP_SPEED_FIRST;
		m_isJump = true;
	}
}

//ジャンプ終了
void Player::StopJump()
{
	m_isJump = false;
	m_Velocity = Vector3::Zero;
}