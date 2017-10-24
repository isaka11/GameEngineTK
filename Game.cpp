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
	
	////csv�t�@�C���̓ǂݍ���
	//importData("stage.csv");

	////�J�����̐���
	//m_Camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);

	////3D�I�u�W�F�N�g�̐ÓI�����o��������
	//Obj3d::InitializeStatic(m_d3dDevice, m_d3dContext, m_Camera.get());

	////�n�`�N���X�̏�����
	//LandShapeCommonDef lscdef;
	//lscdef.pDevice = m_d3dDevice.Get();
	//lscdef.pDeviceContext = m_d3dContext.Get();
	//lscdef.pCamera = m_Camera.get();
	//LandShape::InitializeCommon(lscdef);
	//
	////�L�[�{�[�h�̏�����
	//m_keyboard = std::make_unique<Keyboard>();

	////�v���C���[�̐���
	//m_Player = std::make_unique<Player>(m_keyboard.get());
	//m_Player->Initialize();
	//m_Player->SetTrans(START_POS);

	////�J�����Ƀv���C���[���Z�b�g
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

	////�G�t�F�N�g�t�@�N�g���̐���
	//m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());

	////�e�N�X�`���̓ǂݍ��݃p�X�̎w��
	//m_factory->SetDirectory(L"Resources");

	////�X�v���C�g�o�b�`���쐬
	//m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dContext.Get());

	////�f�o�b�O�e�L�X�g���쐬
	//m_debugText = std::make_unique<DebugText>(m_d3dDevice.Get(), m_spriteBatch.get());

	////�R�C���̖����̏�����
	//m_coin_num = COIN_NUM;

	////���[�J���ϐ��̐錾�Ə�����
	//int a = -1;
	//int j = 0;

	////�I�u�W�F�N�g�̐���
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	j++;

	//	if (i % 600 == 0)
	//	{
	//		a++;
	//		j = 0;
	//	}

	//	//0�Ԃ̏ꍇ�����������Ȃ�
	//	if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
	//	{
	//		//�n�`�̏������ƈʒu�̐ݒ�
	//		m_Landshape_obj[i].Initialize(L"Object01", L"Object01");
	//		m_Landshape_obj[i].SetTrans(Vector3(i % MAX_X_CHIP * OBJ_SPACE, 
	//											j / MAX_X_CHIP * -OBJ_SPACE - OBJ_SPACE * 5.0f, 
	//											a * -OBJ_SPACE));

	//		//�ǁE���̐���
	//		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1)
	//		{
	//			m_obj[i].LoadModel(L"Resources/Object01.cmo");
	//		}

	//		//�g�Q���̐���
	//		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)
	//		{
	//			m_obj[i].LoadModel(L"Resources/Object02.cmo");
	//		}

	//		//�R�C���̐���
	//		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
	//		{
	//			m_obj[i].LoadModel(L"Resources/Object03.cmo");
	//			m_Landshape_obj[i].SetScale(Vector3(0.5f, 0.5f, 0.5f));
	//		}
	//		m_obj[i].SetTranslation(m_Landshape_obj[i].GetTrans());
	//	}
	//}

	////�I���t���O�̏�����
	//m_finish_flag = false;

	////�n�ʂ̏������ƈʒu�̐ݒ�
	//m_objGround.LoadModel(L"Resources/Graund.cmo");
	//m_objGround.SetTranslation(Vector3(-1.0f, -27.6f, 1.0f));

	////�e�̏�����
	//m_ObjShadow.LoadModel(L"Resources/shadow.cmo");
	//m_ObjShadow.SetTranslation(Vector3(0, SHADOW_OFFSET, 0));

	////�T�E���h�̏������Ɠǂݍ���
	//ADX2Le::Initialize("Sounds\\CueSheet_0.acb");
	//ADX2Le::LoadAcb("Sounds\\CueSheet_0.acb", "Sounds\\CueSheet_0.awb");

	////BGM�̍Đ�
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
	////�T�E���h�̍X�V����
	//ADX2Le::Update();

	//float elapsedTime = float(timer.GetElapsedSeconds());

	////TODO: Add your game logic here.
	//elapsedTime;

	////�v���C���[�̍X�V����
	//if (m_Camera->GetCameraMoveFlag() == false && m_finish_flag == false)
	//{
	//	m_Player->Update();
	//}

	////�L�[�{�[�h�̍X�V
	//Keyboard::State keystate = m_keyboard->GetState();

	////�J�����̍X�V
	//m_Camera->Update();
	//m_view = m_Camera->GetView();
	//m_proj = m_Camera->GetProj();

	////�I�u�W�F�N�g�̍X�V����
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	//0�ԈȊO�̍X�V�������s��
	//	if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
	//	{
	//		Vector3 Vec = m_Landshape_obj[i].GetTrans() - m_Player->GetTrans();

	//		float distance_Square;

	//		distance_Square = Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z;

	//		float radius_Square;

	//		//���a�̘a�̓��
	//		radius_Square = JUDGMENT_SPACE + JUDGMENT_SPACE;
	//		radius_Square = radius_Square * radius_Square;

	//		if (distance_Square < radius_Square)
	//		{
	//			m_obj[i].Update();
	//			m_Landshape_obj[i].Update();
	//		}

	//		//�R�C���̉�]
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

	////�n�ʂ̍X�V����
	//m_objGround.Update();

	////���@�̓����蔻�苅���擾
	//Sphere sphere = m_Player->GetCollisionNodeBody();

	////���@�̃��[���h���W���擾
	//Vector3 trans = m_Player->GetTrans();

	////���̒��S���玩�@�Z���^�[�̃x�N�g��
	//Vector3 sphere2player = trans - sphere.Center;

	////�߂荞�ݔr�˃x�N�g��
	//Vector3 reject;

	////�I�u�W�F�N�g�̓����蔻��
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1 ||
	//		m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)
	//	{
	//		while (m_Landshape_obj[i].IntersectSphere(sphere, &reject))
	//		{
	//			//�߂荞�݂���������悤�Ɉړ�
	//			sphere.Center += reject;
	//		}
	//	}
	//}

	////�e�̍X�V
	//Vector3 pos = m_Player->GetTrans();
	//pos.y = SHADOW_OFFSET;
	//m_ObjShadow.SetTranslation(pos);

	////���@���ړ�
	//m_Player->SetTrans(sphere.Center + sphere2player);

	////��_���W
	//Vector3 inter;
	//float temp_distance;
	//bool hit = false;

	////�n�`�Ɛ����̓����蔻��
	//if (m_Player->GetVelocity().y <= 0.0f)
	//{
	//	//���@�̓����瑫���ւ̐���
	//	Segment player_segment;

	//	//���@�̃��[���h���W���擾
	//	Vector3 trans = m_Player->GetTrans();

	//	player_segment.start = trans + Vector3(0, SEGMENT_LENGTH_HEAD, 0);
	//	player_segment.end = trans + Vector3(0, -SEGMENT_LENGTH_LEG, 0);

	//	Vector3 temp_inter;

	//	//���ʂƂ̓�����𔻒�
	//	for (int i = 0; i < MAX_CHIP; i++)
	//	{
	//		if (m_Landshape_obj[i].IntersectSegment(player_segment, &temp_inter))
	//		{
	//			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1)		//���E�ǂ̏���
	//			{
	//				//Y���W�̂݌�_�̈ʒu�Ɉړ�
	//				trans.y = temp_inter.y;
	//				// �����I��
	//				m_Player->StopJump();
	//			}
	//			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)		//�g�Q���̏���
	//			{
	//				ADX2Le::Play(CRI_CUESHEET_0_MISS);
	//				m_Player->Set_Mode(false);
	//				m_Player->SetFirstPosFlag(false);
	//				trans = START_POS;
	//			}
	//			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)		//�R�C���̏���
	//			{
	//				bool flag = m_obj[i].Get_Coin();

	//				//�R�C����1�񂾂��G�ꂽ���m�F����
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
	//	//���@�̈ړ�
	//	m_Player->SetTrans(trans);
	//}

	////���@�̓����瑫���ւ̐���
	//Segment player_segment_shadow;

	////���@�̃��[���h���W���擾
	//Vector3 trans_shadow = m_Player->GetTrans();

	//player_segment_shadow.start = trans_shadow + Vector3(0, SEGMENT_LENGTH_HEAD, 0);
	//player_segment_shadow.end = trans_shadow + Vector3(0, -SHADOW_DISTANCE, 0);

	//Vector3 temp_inter_shadow;
	//float distance = 1.0e5;

	////�e�̏���
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	//�R�C���̕��������e�̌v�Z���s��Ȃ�
	//	if (!(m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3))
	//	{
	//		//���ʂƂ̓�����𔻒�
	//		if (m_Landshape_obj[i].IntersectSegment(player_segment_shadow, &temp_inter_shadow))
	//		{
	//			hit = true;

	//			//�v���C���[�̃Z�O�����g�ƒn�ʂ̍�
	//			temp_distance = Vector3::Distance(player_segment_shadow.start, temp_inter_shadow);

	//			if (temp_distance < distance)
	//			{
	//				inter = temp_inter_shadow;
	//				distance = temp_distance;
	//			}
	//		}
	//	}
	//}

	////�R�C�������̕\��
	//if (m_finish_flag == false)
	//{
	//	m_debugText->AddText(Vector2(10, 10), L"COIN_NUM = %d", m_coin_num);
	//}

	////�e�̈ʒu�X�V
	//if (hit)
	//{
	//	Vector3 shadow_pos = trans;
	//	shadow_pos.y = inter.y + SHADOW_OFFSET;
	//	m_ObjShadow.SetTranslation(shadow_pos);
	//}

	////���������珉���ʒu�ɖ߂�
	//if (trans.y <= -40.0f)
	//{
	//	ADX2Le::Play(CRI_CUESHEET_0_MISS);
	//	m_Player->Set_Mode(false);
	//	m_Player->SetFirstPosFlag(false);
	//	m_Player->SetTrans(START_POS);
	//}

	////�R�C����S�ē��肵����Q�[���I��
	//if (m_coin_num == 0)
	//{
	//	m_finish_flag = true;
	//	m_debugText->AddText(Vector2(340, 290), L"GAMECLEAR!");
	//}

	////�Q�[���I������
	//if (m_finish_flag == true && keystate.Enter)
	//{
	//	ExitProcess(0);
	//	ExitGame();
	//}

	////�e�̍s��v�Z
	//m_ObjShadow.Calc();

	////�G�t�F�N�g�̍X�V����
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

	////�`�揈��
	//DirectX::CommonStates m_states(m_d3dDevice.Get());

	//m_d3dContext->OMSetBlendState(m_states.Opaque(), nullptr, 0xFFFFFFFF);
	//m_d3dContext->OMSetDepthStencilState(m_states.DepthNone(), 0);
	//m_d3dContext->RSSetState(m_states.CullNone());
	//m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	////�n�ʂ̕`��
	//m_objGround.Draw();

	////�I�u�W�F�N�g�̕`��
	//for (int i = 0; i < MAX_CHIP; i++)
	//{
	//	//0�ԈȊO�̃I�u�W�F�N�g��`��
	//	if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
	//	{
	//		Vector3 Vec = m_Landshape_obj[i].GetTrans() - m_Player->GetTrans();

	//		float distance_Square;

	//		distance_Square = Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z;

	//		float radius_Square;

	//		//���a�̘a�̓��
	//		radius_Square = JUDGMENT_SPACE + JUDGMENT_SPACE;
	//		radius_Square = radius_Square * radius_Square;

	//		if (distance_Square < radius_Square)
	//		{
	//			//3�Ԃ̕`��
	//			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
	//			{
	//				if (m_obj[i].Get_Delete() == false)
	//				{
	//					m_obj[i].Draw();
	//					//m_Landshape_obj[i].Draw();
	//				}
	//			}
	//			//����ȊO�̕`��
	//			else
	//			{
	//				m_obj[i].Draw();
	//			}
	//		}
	//	}
	//}

	////�v���C���[�̕`��
	//m_Player->Draw();
	//
	////�e�̕`��
	//m_ObjShadow.DrawSubtractive();

	////�G�t�F�N�g�̕`�揈��
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

////csv�t�@�C���̓ǂݍ���
//void Game::importData(string filename)
//{
//	ifstream ifs(filename);
//
//	string str;
//	int i;
//
//	if (!ifs)
//	{
//		//�ǂ߂Ȃ��Ƃ��͑S��0
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
//		//1�s�̂����A������ƃR���}�𕪗􂷂�
//		while (getline(stream, token, ','))
//		{
//			//�S�ĕ�����Ƃ��ēǂݍ��܂�邽��
//			//���l�͕ϊ����K�v
//			m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] = atoi(token.c_str());
//			i++;
//		}
//	}
//}