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

//�萔�錾
const int MAX_X_CHIP = 40;						//�X�e�[�W�̉����̃}�b�v�`�b�v
const int MAX_Y_CHIP = 45;						//�X�e�[�W�̏c���~���s���̃}�b�v�`�b�v
const int MAX_CHIP = MAX_X_CHIP * MAX_Y_CHIP;	//�}�b�v�`�b�v�̍��v����
const int COIN_NUM = 5;							//�R�C���̖���
const float OBJ_SPACE = 1.9675f;				//�I�u�W�F�N�g�̔z�u�Ԋu
const float SEGMENT_LENGTH_HEAD = 1.0f;			//������i�����j�ւ̃Z�O�����g
const float SEGMENT_LENGTH_LEG = 0.5f;			//�������i�����j�ւ̃Z�O�����g
const float SHADOW_OFFSET = 0.08f;				//�e�̃I�t�Z�b�g
const float SHADOW_DISTANCE = 30.0f;			//��������e�܂ł̍ő勗��
const float ADSORP_LENGTH = 0.5f;				//�������牽���[�g�����܂ŋz�����s����
const float JUDGMENT_SPACE = 5.0f;				//�����蔻��̐�����
const DirectX::SimpleMath::Vector3 START_POS = DirectX::SimpleMath::Vector3(9.0f, -25.5f, 0.0f);	//�v���C���[�̏����ʒu

class GameScene : public SceneBase
{
private:
	static SceneBase* m_base;

	// �v���C���[
	std::unique_ptr<Player> m_Player;

	//�n�`�f�[�^�̃|�C���^�z��
	std::vector<LandShape*> m_landShapeArray;

	//std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//std::unique_ptr<DebugText> m_debugText;

	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> m_factory;

	//�n�ʂ̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldGraund;

	//���f��(�I�u�W�F�N�g)
	Obj3d m_obj[MAX_CHIP];

	//���f��(�n��)
	Obj3d m_objGround;

	// �e
	Obj3d m_ObjShadow;

	//�J����
	std::unique_ptr<FollowCamera> m_Camera;

	//�n�`(�I�u�W�F�N�g)
	LandShape m_Landshape_obj[MAX_CHIP];

	int m_map[MAX_Y_CHIP][MAX_X_CHIP];

	//�R�C���̖���
	int m_coin_num;

	//�I���t���O
	bool m_finish_flag;

	CGame* m_Scene;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;	

//	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//std::unique_ptr<DebugText> m_debugText;

	//�G�t�F�N�g�t�@�N�g��
	//std::unique_ptr<DirectX::EffectFactory> m_factory;

public:
	GameScene();
	~GameScene();
	void Initialize(/*DirectX::Keyboard* keyboard*/);
	void Update(CGame* scene);
	void Render();
	void Dispose();
	static SceneBase* GetInstance();

	//csv�t�@�C���̓ǂݍ���
	void importData(string filename);
};