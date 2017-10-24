//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "ModelEffect.h"
#include "TitleScene.h"
#include "ADX2Le.h"
#include "CueSheet_0.h"
#include "Device.h"

#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

extern void ExitGame();

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace Library;

Game::Game() :
	m_window(0),
	m_outputWidth(800),
	m_outputHeight(600),
	m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	m_window = window;
	m_outputWidth = std::max(width, 1);
	m_outputHeight = std::max(height, 1);
	
	CreateDevice();

	Device::GetInstance()->SetDevice(m_d3dDevice);
	Device::GetInstance()->SetContext(m_d3dContext);
	Device::GetInstance()->SetWidth(m_outputWidth);
	Device::GetInstance()->SetHeight(m_outputHeight);

	//Obj3d::InitializeDevice(m_d3dDevice, m_d3dContext);

	CreateResources();

	//TODO: Change the timer settings if you want something other than the default variable timestep mode.
	//e.g. for 60 FPS fixed timestep update logic, call:
	
	//m_timer.SetFixedTimeStep(true);
	//m_timer.SetTargetElapsedSeconds(1.0 / 60);
	
	////csvファイルの読み込み
	//importData("stage.csv");

	////カメラの生成
	//m_Camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);

	////3Dオブジェクトの静的メンバを初期化
	//Obj3d::InitializeStatic(m_d3dDevice, m_d3dContext, m_Camera.get());

	////地形クラスの初期化
	//LandShapeCommonDef lscdef;
	//lscdef.pDevice = m_d3dDevice.Get();
	//lscdef.pDeviceContext = m_d3dContext.Get();
	//lscdef.pCamera = m_Camera.get();
	//LandShape::InitializeCommon(lscdef);
	//
	////キーボードの初期化
	//m_keyboard = std::make_unique<Keyboard>();

	////プレイヤーの生成
	//m_Player = std::make_unique<Player>(m_keyboard.get());
	//m_Player->Initialize();
	//m_Player->SetTrans(START_POS);

	////カメラにプレイヤーをセット
	//m_Camera->SetPlayer(m_Player.get());

	//m_batch = std::make_unique<PrimitiveBatch<VertexPositionNormal>>(m_d3dContext.Get());

	//m_effect = std::make_unique<BasicEffect>(m_d3dDevice.Get());

	//m_view = Matrix::CreateLookAt(Vector3(0, 2.0f, 5.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	//m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.0f, float(m_outputWidth) / float(m_outputHeight), 0.1f, 500.f);

	//m_effect->SetView(m_view);

	//m_effect->SetProjection(m_proj);

	//m_effect->SetVertexColorEnabled(true);

	//void const* shaderByteCode;
	//size_t byteCodeLength;

	//m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
	//	VertexPositionColor::InputElementCount,
	//	shaderByteCode, byteCodeLength,
	//	m_inputLayout.GetAddressOf());

	////エフェクトファクトリの生成
	//m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());

	////テクスチャの読み込みパスの指定
	//m_factory->SetDirectory(L"Resources");

	////スプライトバッチを作成
	//m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dContext.Get());

	////デバッグテキストを作成
	//m_debugText = std::make_unique<DebugText>(m_d3dDevice.Get(), m_spriteBatch.get());

	////コインの枚数の初期化
	//m_coin_num = COIN_NUM;

	////ローカル変数の宣言と初期化
	//int a = -1;
	//int j = 0;

	////オブジェクトの生成
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	j++;

	//	if (i % 600 == 0)
	//	{
	//		a++;
	//		j = 0;
	//	}

	//	//0番の場合何も生成しない
	//	if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
	//	{
	//		//地形の初期化と位置の設定
	//		m_Landshape_obj[i].Initialize(L"Object01", L"Object01");
	//		m_Landshape_obj[i].SetTrans(Vector3(i % MAX_X_CHIP * OBJ_SPACE, 
	//											j / MAX_X_CHIP * -OBJ_SPACE - OBJ_SPACE * 5.0f, 
	//											a * -OBJ_SPACE));

	//		//壁・床の生成
	//		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1)
	//		{
	//			m_obj[i].LoadModel(L"Resources/Object01.cmo");
	//		}

	//		//トゲ床の生成
	//		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)
	//		{
	//			m_obj[i].LoadModel(L"Resources/Object02.cmo");
	//		}

	//		//コインの生成
	//		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
	//		{
	//			m_obj[i].LoadModel(L"Resources/Object03.cmo");
	//			m_Landshape_obj[i].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	//		}
	//		m_obj[i].SetTranslation(m_Landshape_obj[i].GetTrans());
	//	}
	//}

	////終了フラグの初期化
	//m_finish_flag = false;

	////地面の初期化と位置の設定
	//m_objGround.LoadModel(L"Resources/Graund.cmo");
	//m_objGround.SetTranslation(Vector3(-1.0f, -27.6f, 1.0f));

	////影の初期化
	//m_ObjShadow.LoadModel(L"Resources/shadow.cmo");
	//m_ObjShadow.SetTranslation(Vector3(0, SHADOW_OFFSET, 0));

	////サウンドの初期化と読み込み
	//ADX2Le::Initialize("Sounds\\CueSheet_0.acb");
	//ADX2Le::LoadAcb("Sounds\\CueSheet_0.acb", "Sounds\\CueSheet_0.awb");

	////BGMの再生
	//ADX2Le::Play(CRI_CUESHEET_0_BGM);	

	m_Scene = new CGame();
	Title* ts = new Title();
	m_Scene->ChangeScene(ts);
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	////サウンドの更新処理
	//ADX2Le::Update();

	//float elapsedTime = float(timer.GetElapsedSeconds());

	////TODO: Add your game logic here.
	//elapsedTime;

	////プレイヤーの更新処理
	//if (m_Camera->GetCameraMoveFlag() == false && m_finish_flag == false)
	//{
	//	m_Player->Update();
	//}

	////キーボードの更新
	//Keyboard::State keystate = m_keyboard->GetState();

	////カメラの更新
	//m_Camera->Update();
	//m_view = m_Camera->GetView();
	//m_proj = m_Camera->GetProj();

	////オブジェクトの更新処理
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	//0番以外の更新処理を行う
	//	if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
	//	{
	//		Vector3 Vec = m_Landshape_obj[i].GetTrans() - m_Player->GetTrans();

	//		float distance_Square;

	//		distance_Square = Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z;

	//		float radius_Square;

	//		//半径の和の二乗
	//		radius_Square = JUDGMENT_SPACE + JUDGMENT_SPACE;
	//		radius_Square = radius_Square * radius_Square;

	//		if (distance_Square < radius_Square)
	//		{
	//			m_obj[i].Update();
	//			m_Landshape_obj[i].Update();
	//		}

	//		//コインの回転
	//		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
	//		{
	//			Vector3 l_angle = m_obj[i].GetRotation();
	//			m_obj[i].SetRotation(l_angle + Vector3(0.0f, 0.1f, 0.0f));

	//			//Vector3 Trans = m_obj[i].GetTranslation();
	//			//m_obj[i].SetTranslation(Trans + Vector3(0.01f, 0.0f, 0.0f));
	//			//m_Landshape_obj[i].SetTrans(Trans + Vector3(0.01f, 0.0f, 0.0f));
	//		}
	//	}
	//}

	////地面の更新処理
	//m_objGround.Update();

	////自機の当たり判定球を取得
	//Sphere sphere = m_Player->GetCollisionNodeBody();

	////自機のワールド座標を取得
	//Vector3 trans = m_Player->GetTrans();

	////球の中心から自機センターのベクトル
	//Vector3 sphere2player = trans - sphere.Center;

	////めり込み排斥ベクトル
	//Vector3 reject;

	////オブジェクトの当たり判定
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1 ||
	//		m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)
	//	{
	//		while (m_Landshape_obj[i].IntersectSphere(sphere, &reject))
	//		{
	//			//めり込みを解消するように移動
	//			sphere.Center += reject;
	//		}
	//	}
	//}

	////影の更新
	//Vector3 pos = m_Player->GetTrans();
	//pos.y = SHADOW_OFFSET;
	//m_ObjShadow.SetTranslation(pos);

	////自機を移動
	//m_Player->SetTrans(sphere.Center + sphere2player);

	////交点座標
	//Vector3 inter;
	//float temp_distance;
	//bool hit = false;

	////地形と線分の当たり判定
	//if (m_Player->GetVelocity().y <= 0.0f)
	//{
	//	//自機の頭から足元への線分
	//	Segment player_segment;

	//	//自機のワールド座標を取得
	//	Vector3 trans = m_Player->GetTrans();

	//	player_segment.start = trans + Vector3(0, SEGMENT_LENGTH_HEAD, 0);
	//	player_segment.end = trans + Vector3(0, -SEGMENT_LENGTH_LEG, 0);

	//	Vector3 temp_inter;

	//	//床面との当たりを判定
	//	for (int i = 0; i < MAX_CHIP; i++)
	//	{
	//		if (m_Landshape_obj[i].IntersectSegment(player_segment, &temp_inter))
	//		{
	//			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1)		//床・壁の処理
	//			{
	//				//Y座標のみ交点の位置に移動
	//				trans.y = temp_inter.y;
	//				// 落下終了
	//				m_Player->StopJump();
	//			}
	//			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)		//トゲ床の処理
	//			{
	//				ADX2Le::Play(CRI_CUESHEET_0_MISS);
	//				m_Player->Set_Mode(false);
	//				m_Player->SetFirstPosFlag(false);
	//				trans = START_POS;
	//			}
	//			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)		//コインの処理
	//			{
	//				bool flag = m_obj[i].Get_Coin();

	//				//コインが1回だけ触れたか確認する
	//				if (flag == false)
	//				{
	//					if (m_coin_num > 1)
	//					{
	//						ADX2Le::Play(CRI_CUESHEET_0_COIN);
	//					}
	//					else
	//					{
	//						ADX2Le::Play(CRI_CUESHEET_0_CLEAR);
	//					}

	//					m_obj[i].Set_Coin(true);
	//					m_obj[i].Set_Delete(true);
	//					m_coin_num--;
	//				}
	//			}
	//		}
	//	}
	//	//自機の移動
	//	m_Player->SetTrans(trans);
	//}

	////自機の頭から足元への線分
	//Segment player_segment_shadow;

	////自機のワールド座標を取得
	//Vector3 trans_shadow = m_Player->GetTrans();

	//player_segment_shadow.start = trans_shadow + Vector3(0, SEGMENT_LENGTH_HEAD, 0);
	//player_segment_shadow.end = trans_shadow + Vector3(0, -SHADOW_DISTANCE, 0);

	//Vector3 temp_inter_shadow;
	//float distance = 1.0e5;

	////影の処理
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	//コインの部分だけ影の計算を行わない
	//	if (!(m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3))
	//	{
	//		//床面との当たりを判定
	//		if (m_Landshape_obj[i].IntersectSegment(player_segment_shadow, &temp_inter_shadow))
	//		{
	//			hit = true;

	//			//プレイヤーのセグメントと地面の差
	//			temp_distance = Vector3::Distance(player_segment_shadow.start, temp_inter_shadow);

	//			if (temp_distance < distance)
	//			{
	//				inter = temp_inter_shadow;
	//				distance = temp_distance;
	//			}
	//		}
	//	}
	//}

	////コイン枚数の表示
	//if (m_finish_flag == false)
	//{
	//	m_debugText->AddText(Vector2(10, 10), L"COIN_NUM = %d", m_coin_num);
	//}

	////影の位置更新
	//if (hit)
	//{
	//	Vector3 shadow_pos = trans;
	//	shadow_pos.y = inter.y + SHADOW_OFFSET;
	//	m_ObjShadow.SetTranslation(shadow_pos);
	//}

	////落下したら初期位置に戻す
	//if (trans.y <= -40.0f)
	//{
	//	ADX2Le::Play(CRI_CUESHEET_0_MISS);
	//	m_Player->Set_Mode(false);
	//	m_Player->SetFirstPosFlag(false);
	//	m_Player->SetTrans(START_POS);
	//}

	////コインを全て入手したらゲーム終了
	//if (m_coin_num == 0)
	//{
	//	m_finish_flag = true;
	//	m_debugText->AddText(Vector2(340, 290), L"GAMECLEAR!");
	//}

	////ゲーム終了処理
	//if (m_finish_flag == true && keystate.Enter)
	//{
	//	ExitProcess(0);
	//	ExitGame();
	//}

	////影の行列計算
	//m_ObjShadow.Calc();

	////エフェクトの更新処理
	//ModelEffectManager::getInstance()->Update();

	m_Scene->Update();
}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    // TODO: Add your rendering code here.

	////描画処理
	//DirectX::CommonStates m_states(m_d3dDevice.Get());

	//m_d3dContext->OMSetBlendState(m_states.Opaque(), nullptr, 0xFFFFFFFF);
	//m_d3dContext->OMSetDepthStencilState(m_states.DepthNone(), 0);
	//m_d3dContext->RSSetState(m_states.CullNone());
	//m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	////地面の描画
	//m_objGround.Draw();

	////オブジェクトの描画
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	//0番以外のオブジェクトを描画
	//	if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
	//	{
	//		Vector3 Vec = m_Landshape_obj[i].GetTrans() - m_Player->GetTrans();

	//		float distance_Square;

	//		distance_Square = Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z;

	//		float radius_Square;

	//		//半径の和の二乗
	//		radius_Square = JUDGMENT_SPACE + JUDGMENT_SPACE;
	//		radius_Square = radius_Square * radius_Square;

	//		if (distance_Square < radius_Square)
	//		{
	//			//3番の描画
	//			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
	//			{
	//				if (m_obj[i].Get_Delete() == false)
	//				{
	//					m_obj[i].Draw();
	//					//m_Landshape_obj[i].Draw();
	//				}
	//			}
	//			//それ以外の描画
	//			else
	//			{
	//				m_obj[i].Draw();
	//			}
	//		}
	//	}
	//}

	////プレイヤーの描画
	//m_Player->Draw();
	//
	////影の描画
	//m_ObjShadow.DrawSubtractive();

	////エフェクトの描画処理
	//ModelEffectManager::getInstance()->Draw();

	//m_spriteBatch->Begin();

	//m_debugText->Draw();

	//m_spriteBatch->End();

	m_Scene->Render();

	Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

	//m_debugText.reset();
	//m_spriteBatch.reset();
    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();

	ADX2Le::Finalize();
}

////csvファイルの読み込み
//void Game::importData(string filename)
//{
//	ifstream ifs(filename);
//
//	string str;
//	int i;
//
//	if (!ifs)
//	{
//		//読めないときは全て0
//		for (i = 0; i < MAX_CHIP; i++)
//		{
//			m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] = 0;
//		}
//		return;
//	}
//
//	i = 0;
//	while (getline(ifs, str))
//	{
//		string token;
//		istringstream stream(str);
//
//		//1行のうち、文字列とコンマを分裂する
//		while (getline(stream, token, ','))
//		{
//			//全て文字列として読み込まれるため
//			//数値は変換が必要
//			m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] = atoi(token.c_str());
//			i++;
//		}
//	}
//}