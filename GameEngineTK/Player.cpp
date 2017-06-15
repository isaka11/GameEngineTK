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
	m_ObjPlayer[BODY].SetTranslation(Vector3(0.0f, 1.0f, 0.0f));

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

	m_weapon_flag = false;
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

//ミサイルを発射する関数
void Player::FireBullet()
{
	if (m_weapon_flag)
	{
		return;
	}

	//発射するパーツのワールド行列を取得
	Matrix worldm_l = m_ObjPlayer[L_WEAPON].GetWorld();

	Matrix worldm_r = m_ObjPlayer[R_WEAPON].GetWorld();

	//ワールド行列から各要素を抽出
	Vector3 scale_l;			//ワールドスケーリング(L)
	Vector3 scale_r;			//ワールドスケーリング(R)

	Quaternion rotation_l;	//ワールド回転(L)
	Quaternion rotation_r;	//ワールド回転(R)

	Vector3 translation_l;	//ワールド座標(L)
	Vector3 translation_r;	//ワールド座標(R)


	//ワールド行列からスケール、回転、座標を取り出す
	worldm_l.Decompose(scale_l, rotation_l, translation_l);

	worldm_r.Decompose(scale_r, rotation_r, translation_r);

	//発射パーツを親から分離して独立
	m_ObjPlayer[L_WEAPON].SetParent(nullptr);
	m_ObjPlayer[L_WEAPON].SetScale(scale_l);
	m_ObjPlayer[L_WEAPON].SetRotationQ(rotation_l);
	m_ObjPlayer[L_WEAPON].SetTranslation(translation_l);

	m_ObjPlayer[R_WEAPON].SetParent(nullptr);
	m_ObjPlayer[R_WEAPON].SetScale(scale_r);
	m_ObjPlayer[R_WEAPON].SetRotationQ(rotation_r);
	m_ObjPlayer[R_WEAPON].SetTranslation(translation_r);


	//ミサイルの速度を設定
	m_BulletVel_l = Vector3(0, 0, -0.2f);
	m_BulletVel_l = Vector3::Transform(m_BulletVel_l, rotation_l);

	m_BulletVel_r = Vector3(0, 0, -0.2f);
	m_BulletVel_r = Vector3::Transform(m_BulletVel_r, rotation_r);

	m_weapon_flag = true;
	m_timer = 0.0f;
}
//ミサイルを再装填する関数
void Player::ResetBullet()
{
	if (!m_weapon_flag)
	{
		return;
	}

	m_ObjPlayer[L_WEAPON].SetParent(&m_ObjPlayer[BODY]);
	m_ObjPlayer[L_WEAPON].SetScale(Vector3(1, 1, 1));
	m_ObjPlayer[L_WEAPON].SetRotation(Vector3(0, 0, 0));
	m_ObjPlayer[L_WEAPON].SetTranslation(Vector3(-0.5f, -0.05f, -0.025f));

	m_ObjPlayer[R_WEAPON].SetParent(&m_ObjPlayer[BODY]);
	m_ObjPlayer[R_WEAPON].SetScale(Vector3(1, 1, 1));
	m_ObjPlayer[R_WEAPON].SetRotation(Vector3(0, 0, 0));
	m_ObjPlayer[R_WEAPON].SetTranslation(Vector3(0.5f, -0.05f, -0.025f));

	m_weapon_flag = false;
	m_timer = 0.0f;
}

//ロボットの挙動
void Player::Action()
{
	//左エンジンの回転
	Vector3 l_angle = m_ObjPlayer[L_ENGINE].GetRotation();
	m_ObjPlayer[L_ENGINE].SetRotation(l_angle + Vector3(0, 0, -0.05f));

	//右エンジンの回転
	Vector3 r_angle = m_ObjPlayer[R_ENGINE].GetRotation();
	m_ObjPlayer[R_ENGINE].SetRotation(r_angle + Vector3(0, 0, 0.05f));

	//キーボードの状態取得
	Keyboard::State g_key = keyboard->GetState();
	//移動ベクトル（Z座標）
	Vector3 moveV(0, 0, -0.1f);

	float angle = m_ObjPlayer[BODY].GetRotation().y;

	//移動量ベクトルを自機の角度分回転させる
	moveV = Vector3::TransformNormal(moveV, m_ObjPlayer[BODY].GetWorld());

	//座標を移動させる
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
		if (m_weapon_flag)
		{
			ResetBullet();
			return;
		}
		else if (!m_weapon_flag)
		{
			FireBullet();
			return;
		}
	}

	if (g_key.Space && m_timer / 60.0f > 0.0f)
	{
		ResetBullet();
	}

	//2秒経過で再装填する
	if (m_timer / 60.0f >= 2.0f)
	{
		ResetBullet();
	}

	//ミサイルを前進させる
	if (m_weapon_flag)
	{
		m_timer++;
 		Vector3 pos_l = m_ObjPlayer[L_WEAPON].GetTranslation();
		Vector3 pos_r = m_ObjPlayer[R_WEAPON].GetTranslation();

		m_ObjPlayer[L_WEAPON].SetTranslation(pos_l + m_BulletVel_l);
		m_ObjPlayer[R_WEAPON].SetTranslation(pos_r + m_BulletVel_r);
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