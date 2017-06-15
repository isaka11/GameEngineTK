#include "Player.h"
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^
Player::Player()
{

}

//�f�X�g���N�^
Player::~Player()
{

}

//����������
void Player::Initialize()
{
	//�L�[�{�[�h�̏�����
	keyboard = std::make_unique<Keyboard>();

	//���@�p�[�c�̓ǂݍ���
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[BODY].LoadModel(L"Resources/body.cmo");
	m_ObjPlayer[L_WING].LoadModel(L"Resources/LeftWing.cmo");
	m_ObjPlayer[R_WING].LoadModel(L"Resources/RightWing.cmo");
	m_ObjPlayer[L_ENGINE].LoadModel(L"Resources/Engine.cmo");
	m_ObjPlayer[R_ENGINE].LoadModel(L"Resources/Engine.cmo");
	m_ObjPlayer[L_WEAPON].LoadModel(L"Resources/weapon.cmo");
	m_ObjPlayer[R_WEAPON].LoadModel(L"Resources/weapon.cmo");

	//�p�[�c��e�q�֌W���Z�b�g
	m_ObjPlayer[L_WING].SetParent(&m_ObjPlayer[BODY]);

	m_ObjPlayer[R_WING].SetParent(&m_ObjPlayer[BODY]);

	m_ObjPlayer[L_ENGINE].SetParent(&m_ObjPlayer[BODY]);

	m_ObjPlayer[R_ENGINE].SetParent(&m_ObjPlayer[BODY]);

	m_ObjPlayer[L_WEAPON].SetParent(&m_ObjPlayer[L_WING]);

	m_ObjPlayer[R_WEAPON].SetParent(&m_ObjPlayer[R_WING]);

	//�e����̃I�t�Z�b�g(���W�̂��炵��)���Z�b�g
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

//�X�V����
void Player::Update()
{
	//���{�b�g�̋����̍X�V
	this->Action();

	//�e�p�[�c�̍X�V
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}
}

//�`��
void Player::Draw()
{
	//�e�p�[�c�̕`��
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Draw();
	}
}

//�~�T�C���𔭎˂���֐�
void Player::FireBullet()
{
	if (m_weapon_flag)
	{
		return;
	}

	//���˂���p�[�c�̃��[���h�s����擾
	Matrix worldm_l = m_ObjPlayer[L_WEAPON].GetWorld();

	Matrix worldm_r = m_ObjPlayer[R_WEAPON].GetWorld();

	//���[���h�s�񂩂�e�v�f�𒊏o
	Vector3 scale_l;			//���[���h�X�P�[�����O(L)
	Vector3 scale_r;			//���[���h�X�P�[�����O(R)

	Quaternion rotation_l;	//���[���h��](L)
	Quaternion rotation_r;	//���[���h��](R)

	Vector3 translation_l;	//���[���h���W(L)
	Vector3 translation_r;	//���[���h���W(R)


	//���[���h�s�񂩂�X�P�[���A��]�A���W�����o��
	worldm_l.Decompose(scale_l, rotation_l, translation_l);

	worldm_r.Decompose(scale_r, rotation_r, translation_r);

	//���˃p�[�c��e���番�����ēƗ�
	m_ObjPlayer[L_WEAPON].SetParent(nullptr);
	m_ObjPlayer[L_WEAPON].SetScale(scale_l);
	m_ObjPlayer[L_WEAPON].SetRotationQ(rotation_l);
	m_ObjPlayer[L_WEAPON].SetTranslation(translation_l);

	m_ObjPlayer[R_WEAPON].SetParent(nullptr);
	m_ObjPlayer[R_WEAPON].SetScale(scale_r);
	m_ObjPlayer[R_WEAPON].SetRotationQ(rotation_r);
	m_ObjPlayer[R_WEAPON].SetTranslation(translation_r);


	//�~�T�C���̑��x��ݒ�
	m_BulletVel_l = Vector3(0, 0, -0.2f);
	m_BulletVel_l = Vector3::Transform(m_BulletVel_l, rotation_l);

	m_BulletVel_r = Vector3(0, 0, -0.2f);
	m_BulletVel_r = Vector3::Transform(m_BulletVel_r, rotation_r);

	m_weapon_flag = true;
	m_timer = 0.0f;
}
//�~�T�C�����đ��U����֐�
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

//���{�b�g�̋���
void Player::Action()
{
	//���G���W���̉�]
	Vector3 l_angle = m_ObjPlayer[L_ENGINE].GetRotation();
	m_ObjPlayer[L_ENGINE].SetRotation(l_angle + Vector3(0, 0, -0.05f));

	//�E�G���W���̉�]
	Vector3 r_angle = m_ObjPlayer[R_ENGINE].GetRotation();
	m_ObjPlayer[R_ENGINE].SetRotation(r_angle + Vector3(0, 0, 0.05f));

	//�L�[�{�[�h�̏�Ԏ擾
	Keyboard::State g_key = keyboard->GetState();
	//�ړ��x�N�g���iZ���W�j
	Vector3 moveV(0, 0, -0.1f);

	float angle = m_ObjPlayer[BODY].GetRotation().y;

	//�ړ��ʃx�N�g�������@�̊p�x����]������
	moveV = Vector3::TransformNormal(moveV, m_ObjPlayer[BODY].GetWorld());

	//���W���ړ�������
	Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
	m_ObjPlayer[BODY].SetTranslation(pos + moveV);

	//W�L�[��������
	if (g_key.W)
	{
		Vector3 angle = m_ObjPlayer[BODY].GetRotation();
		angle.x += 0.03f;

		m_ObjPlayer[BODY].SetRotation(angle);
	}

	//S�L�[��������
	if (g_key.S)
	{
		Vector3 angle = m_ObjPlayer[BODY].GetRotation();
		angle.x -= 0.03f;

		m_ObjPlayer[BODY].SetRotation(angle);
	}

	//A�L�[��������
	if (g_key.A)
	{
		Vector3 angle = m_ObjPlayer[BODY].GetRotation();
		angle.y += 0.03f;

		m_ObjPlayer[BODY].SetRotation(angle);
	}

	//D�L�[��������
	if (g_key.D)
	{
		Vector3 angle = m_ObjPlayer[BODY].GetRotation();
		angle.y -= 0.03f;

		m_ObjPlayer[BODY].SetRotation(angle);
	}

	//Space�L�[��������
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

	//2�b�o�߂ōđ��U����
	if (m_timer / 60.0f >= 2.0f)
	{
		ResetBullet();
	}

	//�~�T�C����O�i������
	if (m_weapon_flag)
	{
		m_timer++;
 		Vector3 pos_l = m_ObjPlayer[L_WEAPON].GetTranslation();
		Vector3 pos_r = m_ObjPlayer[R_WEAPON].GetTranslation();

		m_ObjPlayer[L_WEAPON].SetTranslation(pos_l + m_BulletVel_l);
		m_ObjPlayer[R_WEAPON].SetTranslation(pos_r + m_BulletVel_r);
	}
}

//�L�[�����擾����
DirectX::Keyboard* Player::GetKeyboard()
{
	return keyboard.get();
}

//�v���C���[�̈ړ����擾����
const DirectX::SimpleMath::Vector3& Player::GetRot()
{
	return m_ObjPlayer[BODY].GetRotation();
}

//�v���C���[�̊p�x���擾����
const DirectX::SimpleMath::Vector3& Player::GetTrans()
{
	return m_ObjPlayer[BODY].GetTranslation();
}

//�v���C���[�̈ړ����Z�b�g����
void Player::SetRot(const Vector3& rotation)
{
	m_ObjPlayer[BODY].SetRotation(rotation);
}

//�v���C���[�̊p�x���Z�b�g����
void Player::SetTrans(const Vector3& translation)
{
	m_ObjPlayer[BODY].SetTranslation(translation);
}