//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include <VertexTypes.h>
#include <PrimitiveBatch.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include "DebugCamera.h"
#include "FollowCamera.h"
#include <Keyboard.h>
#include <SimpleMath.h>
#include <vector>
#include "Obj3d.h"

const int Ball_Number = 20;
const int Teapot_Number = 20;
const int Max_Graund = 200;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:
	
	//自機パーツ
	enum PLAYERPARTS
	{
		TANK,
		BODY,
		BODY2,
		ARM,
		ARM2,
		WEAPON,

		PLAYER_PARTS_NUM
	};

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
	int												m_scalingtime;
    int                                             m_outputWidth;
    int                                             m_outputHeight;
	int                                             m_timeflag;
	int												m_Height_pos[20];
	int												m_Width_pos[20];
	float											m_time;
	float											m_time2;
	
	//自機の回転角
	float m_Spin_Angle;


    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;		

	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> m_factory;

	//モデル(天球)
	Obj3d m_objSkydome;

	//モデル(地面)
	std::unique_ptr<DirectX::Model> m_modelGround;

	//モデル(ボール)
	std::unique_ptr<DirectX::Model> m_modelBall[Ball_Number];

	//モデル(ティーポット)
	std::unique_ptr<DirectX::Model> m_modelTeapot[Teapot_Number];

	////モデル(頭)
	//std::unique_ptr<DirectX::Model> m_modelHead;

	//ボールのワールド行列
	DirectX::SimpleMath::Matrix m_worldBall[Ball_Number];

	//ティーポットのワールド行列
	DirectX::SimpleMath::Matrix m_worldTeapot[Teapot_Number];

	//地面のワールド行列
	DirectX::SimpleMath::Matrix m_worldGraund;

	//キーボード
	std::unique_ptr<DirectX::Keyboard> keyboard;

	//自機の座標
	DirectX::SimpleMath::Vector3 tank_pos;

	//自機のワールド行列1
	DirectX::SimpleMath::Matrix tank_world;

	//自機のワールド行列2
	DirectX::SimpleMath::Matrix tank_world2;

	////自機の3Dオブジェクト
	//Obj3d m_ObjPlayer;

	//自機の3Dオブジェクト
	std::vector<Obj3d> m_ObjPlayer;

	//サイン用の引数となる角度
	float sinAngle;


	//Obj3d m_ObjPlayer1;
	//Obj3d m_ObjPlayer2;

	//カメラ
	std::unique_ptr<FollowCamera> m_Camera;


};