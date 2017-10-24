

#include "GameScene.h"
#include "ModelEffect.h"
#include "Device.h"

extern void ExitGame();

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Library;

using Microsoft::WRL::ComPtr;

SceneBase* GameScene::m_base = nullptr;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	Dispose();
}

void GameScene::Initialize(/*DirectX::Keyboard* keyboard*/)
{
	Device* device = Device::GetInstance();

	//csvファイルの読み込み
	importData("stage.csv");

	//カメラの生成
	m_Camera = std::make_unique<FollowCamera>(device->GetWidth(), device->GetHeight());

	//3Dオブジェクトの静的メンバを初期化
	Obj3d::InitializeStatic(device->GetDevice(), device->GetContext(), m_Camera.get());

	//地形クラスの初期化
	LandShapeCommonDef lscdef;
	lscdef.pDevice = device->GetDevice().Get();
	lscdef.pDeviceContext = device->GetContext().Get();
	lscdef.pCamera = m_Camera.get();
	LandShape::InitializeCommon(lscdef);

	//プレイヤーの生成
	m_Player = std::make_unique<Player>();
	m_Player->Initialize();
	m_Player->SetTrans(START_POS);

	//カメラにプレイヤーをセット
	m_Camera->SetPlayer(m_Player.get());

	m_batch = std::make_unique<PrimitiveBatch<VertexPositionNormal>>(device->GetContext().Get());

	m_effect = std::make_unique<BasicEffect>(device->GetDevice().Get());

	m_view = Matrix::CreateLookAt(Vector3(0, 2.0f, 5.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.0f, float(device->GetWidth()) / float(device->GetHeight()), 0.1f, 500.f);

	m_effect->SetView(m_view);

	m_effect->SetProjection(m_proj);

	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	device->GetDevice()->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	//エフェクトファクトリの生成
	m_factory = std::make_unique<EffectFactory>(device->GetDevice().Get());

	//テクスチャの読み込みパスの指定
	m_factory->SetDirectory(L"Resources");

	////スプライトバッチを作成
	//m_spriteBatch = std::make_unique<SpriteBatch>(device->GetDeviceContext());

	////デバッグテキストを作成
	//m_debugText = std::make_unique<DebugText>(device->GetDevice().Get(), m_spriteBatch.get());

	//コインの枚数の初期化
	m_coin_num = COIN_NUM;

	//ローカル変数の宣言と初期化
	int a = -1;
	int j = 0;

	//オブジェクトの生成
	for (int i = 0; i < MAX_CHIP; i++)
	{
		j++;

		if (i % 600 == 0)
		{
			a++;
			j = 0;
		}

		//0番の場合何も生成しない
		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
		{
			//地形の初期化と位置の設定
			m_Landshape_obj[i].Initialize(L"Object01", L"Object01");
			m_Landshape_obj[i].SetTrans(Vector3(i % MAX_X_CHIP * OBJ_SPACE, 
												j / MAX_X_CHIP * -OBJ_SPACE - OBJ_SPACE * 5.0f, 
												a * -OBJ_SPACE));

			//壁・床の生成
			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1)
			{
				m_obj[i].LoadModel(L"Resources/Object01.cmo");
			}

			//トゲ床の生成
			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)
			{
				m_obj[i].LoadModel(L"Resources/Object02.cmo");
			}

			//コインの生成
			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
			{
				m_obj[i].LoadModel(L"Resources/Object03.cmo");
				m_Landshape_obj[i].SetScale(Vector3(0.5f, 0.5f, 0.5f));
			}
			m_obj[i].SetTranslation(m_Landshape_obj[i].GetTrans());
		}
	}

	//終了フラグの初期化
	m_finish_flag = false;

	//地面の初期化と位置の設定
	m_objGround.LoadModel(L"Resources/Graund.cmo");
	m_objGround.SetTranslation(Vector3(-1.0f, -27.6f, 1.0f));

	//影の初期化
	m_ObjShadow.LoadModel(L"Resources/shadow.cmo");
	m_ObjShadow.SetTranslation(Vector3(0, SHADOW_OFFSET, 0));

	////サウンドの初期化と読み込み
	//ADX2Le::Initialize("Sounds\\CueSheet_0.acb");
	//ADX2Le::LoadAcb("Sounds\\CueSheet_0.acb", "Sounds\\CueSheet_0.awb");

	////BGMの再生
	//ADX2Le::Play(CRI_CUESHEET_0_BGM);	
}

void GameScene::Update(CGame* scene)
{
	Device* device = Device::GetInstance();


	//プレイヤーの更新処理
	if (m_Camera->GetCameraMoveFlag() == false && m_finish_flag == false)
	{
		m_Player->Update();
	}

	//カメラの更新
	m_Camera->Update();
	m_view = m_Camera->GetView();
	m_proj = m_Camera->GetProj();

	//オブジェクトの更新処理
	for (int i = 0; i < MAX_CHIP; i++)
	{
		//0番以外の更新処理を行う
		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
		{
			Vector3 Vec = m_Landshape_obj[i].GetTrans() - m_Player->GetTrans();

			float distance_Square;

			distance_Square = Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z;

			float radius_Square;

			//半径の和の二乗
			radius_Square = JUDGMENT_SPACE + JUDGMENT_SPACE;
			radius_Square = radius_Square * radius_Square;

			if (distance_Square < radius_Square)
			{
				m_obj[i].Update();
				m_Landshape_obj[i].Update();
			}

			//コインの回転
			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
			{
				Vector3 l_angle = m_obj[i].GetRotation();
				m_obj[i].SetRotation(l_angle + Vector3(0.0f, 0.1f, 0.0f));

				//Vector3 Trans = m_obj[i].GetTranslation();
				//m_obj[i].SetTranslation(Trans + Vector3(0.01f, 0.0f, 0.0f));
				//m_Landshape_obj[i].SetTrans(Trans + Vector3(0.01f, 0.0f, 0.0f));
			}
		}
	}

	//地面の更新処理
	m_objGround.Update();

	//自機の当たり判定球を取得
	Sphere sphere = m_Player->GetCollisionNodeBody();

	//自機のワールド座標を取得
	Vector3 trans = m_Player->GetTrans();

	//球の中心から自機センターのベクトル
	Vector3 sphere2player = trans - sphere.Center;

	//めり込み排斥ベクトル
	Vector3 reject;

	//オブジェクトの当たり判定
	for (int i = 0; i < MAX_CHIP; i++)
	{
		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1 ||
			m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)
		{
			while (m_Landshape_obj[i].IntersectSphere(sphere, &reject))
			{
				//めり込みを解消するように移動
				sphere.Center += reject;
			}
		}
	}

	//影の更新
	Vector3 pos = m_Player->GetTrans();
	pos.y = SHADOW_OFFSET;
	m_ObjShadow.SetTranslation(pos);

	//自機を移動
	m_Player->SetTrans(sphere.Center + sphere2player);

	//交点座標
	Vector3 inter;
	float temp_distance;
	bool hit = false;

	//地形と線分の当たり判定
	if (m_Player->GetVelocity().y <= 0.0f)
	{
		//自機の頭から足元への線分
		Segment player_segment;

		//自機のワールド座標を取得
		Vector3 trans = m_Player->GetTrans();

		player_segment.start = trans + Vector3(0, SEGMENT_LENGTH_HEAD, 0);
		player_segment.end = trans + Vector3(0, -SEGMENT_LENGTH_LEG, 0);

		Vector3 temp_inter;

		//床面との当たりを判定
		for (int i = 0; i < MAX_CHIP; i++)
		{
			if (m_Landshape_obj[i].IntersectSegment(player_segment, &temp_inter))
			{
				if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1)		//床・壁の処理
				{
					//Y座標のみ交点の位置に移動
					trans.y = temp_inter.y;
					// 落下終了
					m_Player->StopJump();
				}
				if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)		//トゲ床の処理
				{
					//ADX2Le::Play(CRI_CUESHEET_0_MISS);
					m_Player->Set_Mode(false);
					m_Player->SetFirstPosFlag(false);
					trans = START_POS;
				}
				if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)		//コインの処理
				{
					bool flag = m_obj[i].Get_Coin();

					//コインが1回だけ触れたか確認する
					if (flag == false)
					{
						if (m_coin_num > 1)
						{
							//ADX2Le::Play(CRI_CUESHEET_0_COIN);
						}
						else
						{
							//ADX2Le::Play(CRI_CUESHEET_0_CLEAR);
						}

						m_obj[i].Set_Coin(true);
						m_obj[i].Set_Delete(true);
						m_coin_num--;
					}
				}
			}
		}
		//自機の移動
		m_Player->SetTrans(trans);
	}

	//自機の頭から足元への線分
	Segment player_segment_shadow;

	//自機のワールド座標を取得
	Vector3 trans_shadow = m_Player->GetTrans();

	player_segment_shadow.start = trans_shadow + Vector3(0, SEGMENT_LENGTH_HEAD, 0);
	player_segment_shadow.end = trans_shadow + Vector3(0, -SHADOW_DISTANCE, 0);

	Vector3 temp_inter_shadow;
	float distance = 1.0e5;

	//影の処理
	for (int i = 0; i < MAX_CHIP; i++)
	{
		//コインの部分だけ影の計算を行わない
		if (!(m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3))
		{
			//床面との当たりを判定
			if (m_Landshape_obj[i].IntersectSegment(player_segment_shadow, &temp_inter_shadow))
			{
				hit = true;

				//プレイヤーのセグメントと地面の差
				temp_distance = Vector3::Distance(player_segment_shadow.start, temp_inter_shadow);

				if (temp_distance < distance)
				{
					inter = temp_inter_shadow;
					distance = temp_distance;
				}
			}
		}
	}

	//コイン枚数の表示
	if (m_finish_flag == false)
	{
		//m_debugText->AddText(Vector2(10, 10), L"COIN_NUM = %d", m_coin_num);
	}

	//影の位置更新
	if (hit)
	{
		Vector3 shadow_pos = trans;
		shadow_pos.y = inter.y + SHADOW_OFFSET;
		m_ObjShadow.SetTranslation(shadow_pos);
	}

	//落下したら初期位置に戻す
	if (trans.y <= -40.0f)
	{
		//ADX2Le::Play(CRI_CUESHEET_0_MISS);
		m_Player->Set_Mode(false);
		m_Player->SetFirstPosFlag(false);
		m_Player->SetTrans(START_POS);
	}

	//コインを全て入手したらゲーム終了
	if (m_coin_num == 0)
	{
		m_finish_flag = true;
		//m_debugText->AddText(Vector2(340, 290), L"GAMECLEAR!");
	}

	////ゲーム終了処理
	//if (m_finish_flag == true && keystate.Enter)
	//{
	//	ExitProcess(0);
	//	ExitGame();
	//}

	//影の行列計算
	m_ObjShadow.Calc();

	//エフェクトの更新処理
	ModelEffectManager::getInstance()->Update();
}

void GameScene::Render()
{
	Device* device = Device::GetInstance();
	
	//描画処理
	DirectX::CommonStates m_states(device->GetDevice().Get());

	device->GetContext()->OMSetBlendState(m_states.Opaque(), nullptr, 0xFFFFFFFF);
	device->GetContext()->OMSetDepthStencilState(m_states.DepthNone(), 0);
	device->GetContext()->RSSetState(m_states.CullNone());
	device->GetContext()->IASetInputLayout(m_inputLayout.Get());

	//地面の描画
	m_objGround.Draw();

	//オブジェクトの描画
	for (int i = 0; i < MAX_CHIP; i++)
	{
		//0番以外のオブジェクトを描画
		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
		{
			Vector3 Vec = m_Landshape_obj[i].GetTrans() - m_Player->GetTrans();

			float distance_Square;

			distance_Square = Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z;

			float radius_Square;

			//半径の和の二乗
			radius_Square = JUDGMENT_SPACE + JUDGMENT_SPACE;
			radius_Square = radius_Square * radius_Square;

			if (distance_Square < radius_Square)
			{
				//3番の描画
				if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
				{
					if (m_obj[i].Get_Delete() == false)
					{
						m_obj[i].Draw();
						//m_Landshape_obj[i].Draw();
					}
				}
				//それ以外の描画
				else
				{
					m_obj[i].Draw();
				}
			}
		}
	}

	//プレイヤーの描画
	m_Player->Draw();
	
	//影の描画
	m_ObjShadow.DrawSubtractive();

	//エフェクトの描画処理
	ModelEffectManager::getInstance()->Draw();

	//m_spriteBatch->Begin();

	//m_debugText->Draw();

	//m_spriteBatch->End();
}

SceneBase* GameScene::GetInstance()
{
	if (m_base == nullptr)
	{
		m_base = new GameScene();
	}
	return m_base;
}

void GameScene::Dispose()
{
	if (m_base != nullptr)
	{
		delete m_base;
	}
}

//csvファイルの読み込み
void GameScene::importData(string filename)
{
	ifstream ifs(filename);

	string str;
	int i;

	if (!ifs)
	{
		//読めないときは全て0
		for (i = 0; i < MAX_CHIP; i++)
		{
			m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] = 0;
		}
		return;
	}

	i = 0;
	while (getline(ifs, str))
	{
		string token;
		istringstream stream(str);

		//1行のうち、文字列とコンマを分裂する
		while (getline(stream, token, ','))
		{
			//全て文字列として読み込まれるため
			//数値は変換が必要
			m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] = atoi(token.c_str());
			i++;
		}
	}
}