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
#include "DebugText.h"

#include <SimpleMath.h>
#include <vector>
#include "Obj3d.h"
#include "Player.h"
#include "LandShape.h"

#include <fstream>
#include <sstream>
#include "CGame.h"

////�萔�錾
//const int MAX_X_CHIP = 40;						//�X�e�[�W�̉����̃}�b�v�`�b�v
//const int MAX_Y_CHIP = 45;						//�X�e�[�W�̏c���~���s���̃}�b�v�`�b�v
//const int MAX_CHIP = MAX_X_CHIP * MAX_Y_CHIP;	//�}�b�v�`�b�v�̍��v����
//const int COIN_NUM = 5;							//�R�C���̖���
//const float OBJ_SPACE = 1.9675f;				//�I�u�W�F�N�g�̔z�u�Ԋu
//const float SEGMENT_LENGTH_HEAD = 1.0f;			//������i�����j�ւ̃Z�O�����g
//const float SEGMENT_LENGTH_LEG = 0.5f;			//�������i�����j�ւ̃Z�O�����g
//const float SHADOW_OFFSET = 0.08f;				//�e�̃I�t�Z�b�g
//const float SHADOW_DISTANCE = 30.0f;			//��������e�܂ł̍ő勗��
//const float ADSORP_LENGTH = 0.5f;				//�������牽���[�g�����܂ŋz�����s����
//const float JUDGMENT_SPACE = 5.0f;				//�����蔻��̐�����
//const DirectX::SimpleMath::Vector3 START_POS = DirectX::SimpleMath::Vector3(9.0f, -25.5f, 0.0f);	//�v���C���[�̏����ʒu

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

	//�R���X�g���N�^
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
	//// �v���C���[
	//std::unique_ptr<Player> m_Player;

	////�L�[�{�[�h
	//std::unique_ptr<DirectX::Keyboard> m_keyboard;

	////�n�`�f�[�^�̃|�C���^�z��
	//std::vector<LandShape*> m_landShapeArray;

	//�X�V����
    void Update(DX::StepTimer const& timer);

	//�`�揈��
    void Render();

	//csv�t�@�C���̓ǂݍ���
	void importData(std::string filename);

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

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

	

	//std::unique_ptr<DirectX::BasicEffect> m_effect;
	//std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//DirectX::SimpleMath::Matrix m_view;
	//DirectX::SimpleMath::Matrix m_proj;	

	//std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//std::unique_ptr<DebugText> m_debugText;

	////�G�t�F�N�g�t�@�N�g��
	//std::unique_ptr<DirectX::EffectFactory> m_factory;

	////���f��(�I�u�W�F�N�g)
	//Obj3d m_obj[MAX_CHIP];

	////���f��(�n��)
	//Obj3d m_objGround;

	//// �e
	//Obj3d m_ObjShadow;

	////�J����
	//std::unique_ptr<FollowCamera> m_Camera;

	////�n�`(�I�u�W�F�N�g)
	//LandShape m_Landshape_obj[MAX_CHIP];

	////�n�`�I�u�W�F�N�g�̔z��
	//int m_map[MAX_Y_CHIP][MAX_X_CHIP];

	////�R�C���̖���
	//int m_coin_num;
	//
	////�I���t���O
	//bool m_finish_flag;

	CGame* m_Scene;
};