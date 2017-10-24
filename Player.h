#pragma once

#include <d3d11.h>
#include <Keyboard.h>
#include "CollisionNode.h"

class Player
{
public:
	//���@�p�[�c
	enum PLAYERPARTS
	{
		BODY,
		L_WING,
		R_WING,
		L_ENGINE,
		R_ENGINE,

		PLAYER_PARTS_NUM
	};

	//�萔�錾
	const float PLAYER_SPEED = 0.15f;			//�v���C���[�̈ړ����x
	const float GRAVITY_ACC = 0.03f;			//�d�͉����x<m/frame^2>
	const float JUMP_SPEED_FIRST = 0.5f;		//�W�����v����<m/frame>
	const float JUMP_SPEED_MAX = 0.3f;			//�������x����<m/frame>

	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	//����������
	void Initialize();

	//�X�V����
	void Update();

	//�s��̌v�Z
	void Calc();

	//�`�揈��
	void Draw();

	//�v���C���[�̈ړ����擾����
	const DirectX::SimpleMath::Vector3& GetRot();

	//�v���C���[�̊p�x���擾����
	const DirectX::SimpleMath::Vector3& GetTrans();

	//�v���C���[�̃��[���h�s����擾����
	const DirectX::SimpleMath::Matrix& GetWor();

	//�v���C���[�̈ړ����Z�b�g����
	void SetRot(const DirectX::SimpleMath::Vector3& rotation);

	//�v���C���[�̊p�x���Z�b�g����
	void SetTrans(const DirectX::SimpleMath::Vector3& translation);

	//�v���C���[�̓����蔻��(�r�ˏ����p)���擾����
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; }

	//�v���C���[�̑��x���擾����
	const DirectX::SimpleMath::Vector3 GetVelocity() { return m_Velocity; }

	//�W�����v�J�n
	void StartJump();

	//�W�����v�I��
	void StopJump();

	//�W�����v���t���O���擾����
	bool Get_Jump() { return m_isJump; }

	//���[�h�؂�ւ��t���O���擾����
	bool Get_Mode() { return m_mode_flag; }

	//���[�h�؂�ւ��t���O���Z�b�g����
	void Set_Mode(bool flag) { m_mode_flag = flag; }

	bool GetFirstPosFlag() { return m_first_pos_flag; }

	void SetFirstPosFlag(bool flag) { m_first_pos_flag = flag; }

private:
	//���@��3D�I�u�W�F�N�g
	std::vector<Obj3d> m_ObjPlayer;

	//�T�C���p�̈����ƂȂ�p�x
	float m_sinAngle;

	//�S�g�̓����蔻��(�r�ˏ����p)
	SphereNode m_CollisionNodeBody;

	//���x
	DirectX::SimpleMath::Vector3 m_Velocity;

	//�W�����v���t���O
	bool m_isJump;

	//���[�h�؂�ւ��t���O
	bool m_mode_flag;

	//������Ԃ��Ǘ�����t���O
	bool m_first_pos_flag;
};