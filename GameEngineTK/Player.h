#pragma once

#include <d3d11.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"

class Player : public Obj3d
{
public:
	Player();
	~Player();
	//����������
	void Initialize();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�~�T�C���𔭎˂���֐�
	void FireBullet();

	//�~�T�C�����đ��U����֐�
	void ResetBullet();

	//�v���C���[�̋���
	void Action();

	//�L�[�����擾����
	DirectX::Keyboard* GetKeyboard();

	//�v���C���[�̈ړ����擾����
	const DirectX::SimpleMath::Vector3& GetRot();

	//�v���C���[�̊p�x���擾����
	const DirectX::SimpleMath::Vector3& GetTrans();

	//�v���C���[�̈ړ����Z�b�g����
	void SetRot(const DirectX::SimpleMath::Vector3& rotation);

	//�v���C���[�̊p�x���Z�b�g����
	void SetTrans(const DirectX::SimpleMath::Vector3& translation);

private:
	//���@��3D�I�u�W�F�N�g
	std::vector<Obj3d> m_ObjPlayer;

	//�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> keyboard;

	//�~�T�C���U�����Ǘ�����t���O
	bool m_weapon_flag;
	float m_timer;

	//�~�T�C���̑��x�x�N�g��
	DirectX::SimpleMath::Vector3 m_BulletVel_l;
	DirectX::SimpleMath::Vector3 m_BulletVel_r;

	//���@�p�[�c
	enum PLAYERPARTS
	{
		BODY,
		L_WING,
		R_WING,
		L_ENGINE,
		R_ENGINE,
		L_WEAPON,
		R_WEAPON,

		PLAYER_PARTS_NUM
	};
};