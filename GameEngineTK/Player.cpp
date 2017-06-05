#include "Player.h"
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Player::Player()
{

}

//デストラクタ
Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{
	//キーボードの初期化
	keyboard = std::make_unique<Keyboard>();

	//自機パーツの読み込み
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[BODY].LoadModel(L"Resources/body.cmo");
	m_ObjPlayer[L_WING].LoadModel(L"Resources/LeftWing.cmo");
	m_ObjPlayer[R_WING].LoadModel(L"Resources/RightWing.cmo");
	m_ObjPlayer[L_ENGINE].LoadModel(L"Resources/Engine.cmo");
	m_ObjPlayer[R_ENGINE].LoadModel(L"Resources/Engine.cmo");
	m_ObjPlayer[L_WEAPON].LoadModel(L"Resources/weapon.cmo");
	m_ObjPlayer[R_WEAPON].LoadModel(L"Resources/weapon.cmo");

	//パーツを親子関係をセット
	m_ObjPlayer[L_WING].SetParent(&m_ObjPlayer[BODY]);

	m_ObjPlayer[R_WING].SetParent(&m_ObjPlayer[BODY]);

	m_ObjPlayer[L_ENGINE].SetParent(&m_ObjPlayer[BODY]);

	m_ObjPlayer[R_ENGINE].SetParent(&m_ObjPlayer[BODY]);

	m_ObjPlayer[L_WEAPON].SetParent(&m_ObjPlayer[L_WING]);

	m_ObjPlayer[R_WEAPON].SetParent(&m_ObjPlayer[R_WING]);

	//親からのオフセット(座標のずらし分)をセット
	m_ObjPlayer[BODY].SetTranslation(Vector3(0.0f, 2.0f, 0.0f));

	m_ObjPlayer[L_WING].SetTranslation(Vector3(0.0f, 0.0f, 0.0f));

	m_ObjPlayer[R_WING].SetTranslation(Vector3(0.0f, 0.0f, 0.0f));

	m_ObjPlayer[L_ENGINE].SetTranslation(Vector3(-0.1f, 0.0f, 0.5f));

	m_ObjPlayer[L_ENGINE].SetScale(Vector3(0.75f, 0.75f, 0.75f));

	m_ObjPlayer[R_ENGINE].SetTranslation(Vector3(0.1f, 0.0f, 0.5f));

	m_ObjPlayer[R_ENGINE].SetScale(Vector3(0.75f, 0.75f, 0.75f));

	m_ObjPlayer[L_WEAPON].SetTranslation(Vector3(-0.5f, -0.05f, -0.025f));

	m_ObjPlayer[L_WEAPON].SetScale(Vector3(0.75f, 0.75f, 0.6f));

	m_ObjPlayer[R_WEAPON].SetTranslation(Vector3(0.5f, -0.05f, -0.025f));

	m_ObjPlayer[R_WEAPON].SetScale(Vector3(0.75f, 0.75f, 0.6f));
}

//更新処理
void Player::Update()
{
	//ロボットの挙動の更新
	this->Action();

	//各パーツの更新
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}
}

//描画
void Player::Draw()
{
	//各パーツの描画
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Draw();
	}
}

//ロボットの挙動
void Player::Action()
{
	//自機パーツのギミック
	{
		//左エンジンの回転
		Vector3 l_angle = m_ObjPlayer[L_ENGINE].GetRotation();
		m_ObjPlayer[L_ENGINE].SetRotation(l_angle + Vector3(0, 0, -0.05f));

		//右エンジンの回転
		Vector3 r_angle = m_ObjPlayer[R_ENGINE].GetRotation();
		m_ObjPlayer[R_ENGINE].SetRotation(r_angle + Vector3(0, 0, 0.05f));

		if (m_weapon_flag == true)
		{
			if (m_ObjPlayer[L_WEAPON].GetParent() != nullptr && m_ObjPlayer[R_WEAPON].GetParent() != nullptr)
			{
				Vector3 a =
					m_ObjPlayer[L_WEAPON].GetParent()->GetParent()->GetTranslation()
					+ m_ObjPlayer[L_WEAPON].GetParent()->GetTranslation()
					+ m_ObjPlayer[L_WEAPON].GetTranslation();

				Vector3 b =
					m_ObjPlayer[R_WEAPON].GetParent()->GetParent()->GetTranslation()
					+ m_ObjPlayer[R_WEAPON].GetParent()->GetTranslation()
					+ m_ObjPlayer[R_WEAPON].GetTranslation();

				Vector3 l_angle =
					m_ObjPlayer[L_WEAPON].GetParent()->GetParent()->GetRotation()
					+ m_ObjPlayer[L_WEAPON].GetParent()->GetRotation()
					+ m_ObjPlayer[L_WEAPON].GetRotation();

				Vector3 r_angle =
					m_ObjPlayer[R_WEAPON].GetParent()->GetParent()->GetRotation()
					+ m_ObjPlayer[R_WEAPON].GetParent()->GetRotation()
					+ m_ObjPlayer[R_WEAPON].GetRotation();

				m_ObjPlayer[L_WEAPON].SetRotation(l_angle);
				m_ObjPlayer[R_WEAPON].SetRotation(r_angle);

				m_a_flag = true;

				m_ObjPlayer[L_WEAPON].SetTranslation(a += Vector3(0, 0, -0.075f));
				m_ObjPlayer[R_WEAPON].SetTranslation(b += Vector3(0, 0, -0.075f));

				m_ObjPlayer[L_WEAPON].SetParent(nullptr);
				m_ObjPlayer[R_WEAPON].SetParent(nullptr);
			}
		}
	}

	//スペースキーを押したら
	if (m_a_flag == true)
	{
		Vector3 a = m_ObjPlayer[L_WEAPON].GetTranslation();
		Vector3 b = m_ObjPlayer[R_WEAPON].GetTranslation();

		Vector3 l_angle = m_ObjPlayer[L_WEAPON].GetRotation();
		Vector3 r_angle = m_ObjPlayer[R_WEAPON].GetRotation();

		m_ObjPlayer[L_WEAPON].SetRotation(l_angle);
		m_ObjPlayer[R_WEAPON].SetRotation(r_angle);

		//移動ベクトル（Z座標）
		Vector3 moveV(0, 0, -0.2f);
		Vector3 moveV2(0, 0, -0.2f);

		//移動量ベクトルを自機の角度分回転させる
		moveV = Vector3::TransformNormal(moveV, m_ObjPlayer[L_WEAPON].GetWorld());

		moveV2 = Vector3::TransformNormal(moveV2, m_ObjPlayer[R_WEAPON].GetWorld());

		m_ObjPlayer[L_WEAPON].SetTranslation(a += moveV);
		m_ObjPlayer[R_WEAPON].SetTranslation(b += moveV2);
	}

	//キーボードの状態取得
	Keyboard::State g_key = keyboard->GetState();

	//移動ベクトル（Z座標）
	Vector3 moveV(0, 0, -0.1f);

	float angle = m_ObjPlayer[BODY].GetRotation().y;

	//移動量ベクトルを自機の角度分回転させる
	moveV = Vector3::TransformNormal(moveV, m_ObjPlayer[BODY].GetWorld());

	////座標を移動させる
	Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
	m_ObjPlayer[BODY].SetTranslation(pos + moveV);

	//Wキーを押すと
	if (g_key.W)
	{
		Vector3 angle = m_ObjPlayer[BODY].GetRotation();
		angle.x += 0.03f;

		m_ObjPlayer[BODY].SetRotation(angle);
	}

	//Sキーを押すと
	if (g_key.S)
	{
		Vector3 angle = m_ObjPlayer[BODY].GetRotation();
		angle.x -= 0.03f;

		m_ObjPlayer[BODY].SetRotation(angle);
	}

	//Aキーを押すと
	if (g_key.A)
	{
		Vector3 angle = m_ObjPlayer[BODY].GetRotation();
		angle.y += 0.03f;

		m_ObjPlayer[BODY].SetRotation(angle);
	}

	//Dキーを押すと
	if (g_key.D)
	{
		Vector3 angle = m_ObjPlayer[BODY].GetRotation();
		angle.y -= 0.03f;

		m_ObjPlayer[BODY].SetRotation(angle);
	}

	//Spaceキーを押すと
	if (g_key.Space)
	{
		m_weapon_flag = true;
	}
}

//キー情報を取得する
DirectX::Keyboard* Player::GetKeyboard()
{
	return keyboard.get();
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

//プレイヤーの移動をセットする
void Player::SetRot(const Vector3& rotation)
{
	m_ObjPlayer[BODY].SetRotation(rotation);
}

//プレイヤーの角度をセットする
void Player::SetTrans(const Vector3& translation)
{
	m_ObjPlayer[BODY].SetTranslation(translation);
}