#pragma once

#include "SceneBase.h"
#include "StepTimer.h"
#include <VertexTypes.h>
#include <PrimitiveBatch.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include "DebugCamera.h"
#include "FollowCamera.h"
#include "DebugText.h"

#include <SimpleMath.h>
#include <vector>
#include "Obj3d.h"
#include "Player.h"
#include "LandShape.h"

#include <fstream>
#include <sstream>
#include "CGame.h"
#include "Game.h"

using namespace std;

//定数宣言
const int MAX_X_CHIP = 40;						//ステージの横幅のマップチップ
const int MAX_Y_CHIP = 45;						//ステージの縦幅×奥行きのマップチップ
const int MAX_CHIP = MAX_X_CHIP * MAX_Y_CHIP;	//マップチップの合計枚数
const int COIN_NUM = 5;							//コインの枚数
const float OBJ_SPACE = 1.9675f;				//オブジェクトの配置間隔
const float SEGMENT_LENGTH_HEAD = 1.0f;			//上方向（頭側）へのセグメント
const float SEGMENT_LENGTH_LEG = 0.5f;			//下方向（足側）へのセグメント
const float SHADOW_OFFSET = 0.08f;				//影のオフセット
const float SHADOW_DISTANCE = 30.0f;			//足元から影までの最大距離
const float ADSORP_LENGTH = 0.5f;				//足元から何メートル下まで吸着を行うか
const float JUDGMENT_SPACE = 5.0f;				//当たり判定の制限幅
const DirectX::SimpleMath::Vector3 START_POS = DirectX::SimpleMath::Vector3(9.0f, -25.5f, 0.0f);	//プレイヤーの初期位置

class GameScene : public SceneBase
{
private:
	static SceneBase* m_base;

	// プレイヤー
	std::unique_ptr<Player> m_Player;

	//地形データのポインタ配列
	std::vector<LandShape*> m_landShapeArray;

	//std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//std::unique_ptr<DebugText> m_debugText;

	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> m_factory;

	//地面のワールド行列
	DirectX::SimpleMath::Matrix m_worldGraund;

	//モデル(オブジェクト)
	Obj3d m_obj[MAX_CHIP];

	//モデル(地面)
	Obj3d m_objGround;

	// 影
	Obj3d m_ObjShadow;

	//カメラ
	std::unique_ptr<FollowCamera> m_Camera;

	//地形(オブジェクト)
	LandShape m_Landshape_obj[MAX_CHIP];

	int m_map[MAX_Y_CHIP][MAX_X_CHIP];

	//コインの枚数
	int m_coin_num;

	//終了フラグ
	bool m_finish_flag;

	CGame* m_Scene;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;	

//	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//std::unique_ptr<DebugText> m_debugText;

	//エフェクトファクトリ
	//std::unique_ptr<DirectX::EffectFactory> m_factory;

public:
	GameScene();
	~GameScene();
	void Initialize(/*DirectX::Keyboard* keyboard*/);
	void Update(CGame* scene);
	void Render();
	void Dispose();
	static SceneBase* GetInstance();

	//csvファイルの読み込み
	void importData(string filename);
};