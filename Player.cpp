#include "Player.h"
#include "ADX2Le.h"
#include "CueSheet_0.h"
#include "KeyboardLibrary.h"

#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Library;

//�R���X�g���N�^
Player::Player()
{
	m_sinAngle = 0.0f;
	m_mode_flag = false;
	m_first_pos_flag = false;
	Initialize();
}

//�f�X�g���N�^
Player::~Player()
{

}

//����������
void Player::Initialize()
{
	//���@�p�[�c�̓ǂݍ���
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[BODY].LoadModel(L"Resources/body.cmo");
	m_ObjPlayer[L_WING].LoadModel(L"Resources/LeftWing.cmo");
	m_ObjPlayer[R_WING].LoadModel(L"Resources/RightWing.cmo");
	m_ObjPlayer[L_ENGINE].LoadModel(L"Resources/Engine.cmo");
	m_ObjPlayer[R_ENGINE].LoadModel(L"Resources/Engine.cmo");

	//�p�[�c��e�q�֌W���Z�b�g
	m_ObjPlayer[L_WING].SetParent(&m_ObjPlayer[BODY]);
	m_ObjPlayer[R_WING].SetParent(&m_ObjPlayer[BODY]);
	m_ObjPlayer[L_ENGINE].SetParent(&m_ObjPlayer[BODY]);
	m_ObjPlayer[R_ENGINE].SetParent(&m_ObjPlayer[BODY]);

	//�e����̃I�t�Z�b�g(���W�̂��炵��)���Z�b�g
	m_ObjPlayer[BODY].SetTranslation(Vector3(0.0f, 1.0f, 0.0f));
	m_ObjPlayer[L_WING].SetTranslation(Vector3(0.0f, 0.0f, 0.0f));
	m_ObjPlayer[R_WING].SetTranslation(Vector3(0.0f, 0.0f, 0.0f));
	m_ObjPlayer[L_ENGINE].SetTranslation(Vector3(-0.1f, 0.0f, 0.5f));
	m_ObjPlayer[L_ENGINE].SetScale(Vector3(0.75f, 0.75f, 0.75f));
	m_ObjPlayer[R_ENGINE].SetTranslation(Vector3(0.1f, 0.0f, 0.5f));
	m_ObjPlayer[R_ENGINE].SetScale(Vector3(0.75f, 0.75f, 0.75f));

	//�����蔻���ݒ肷��(�r�ˏ����p)
	m_CollisionNodeBody.Initialize();
	m_CollisionNodeBody.SetParent(&m_ObjPlayer[BODY]);
	m_CollisionNodeBody.SetTrans(Vector3(0, 0.5f, 0));
	m_CollisionNodeBody.SetLocalRadius(Vector3(0.5f, 0.5f, 0.5f));

	//�W�����v���t���O�̏�����
	m_isJump = false;

	ADX2Le::Initialize("Sounds\\CueSheet_0.acb");
	ADX2Le::LoadAcb("Sounds\\CueSheet_0.acb", "Sounds\\CueSheet_0.awb");
}

//�X�V����
void Player::Update()
{
	KeyboardLibrary* key = KeyboardLibrary::GetInstance();

	//�L�[�{�[�h�̍X�V
	key->Update();

	//C�L�[��2D,3D��؂�ւ���
	if (key->IsKeyTrigger(Keyboard::Keys::C))
	{
		ADX2Le::Play(CRI_CUESHEET_0_CHANGE);

		if (m_first_pos_flag == false)
		{
			m_first_pos_flag = true;
		}

		if (m_mode_flag == false)
		{
			m_mode_flag = true;
		}
		else if (m_mode_flag == true)
		{
			m_mode_flag = false;
		}
	}

	//�X�y�[�X�L�[�ŃW�����v����
	if (key->IsKeyTrigger(Keyboard::Keys::Space))
	{
		if (m_Velocity.y >= 0)
		{
			ADX2Le::Play(CRI_CUESHEET_0_JUMP);

			//�W�����v�J�n
			StartJump();
		}
	}

	//�d��
	m_Velocity.y -= GRAVITY_ACC;

	//���x����
	if (m_Velocity.y <= -JUMP_SPEED_MAX)
	{
		m_Velocity.y = -JUMP_SPEED_MAX;
	}

	//���݂̍��W�E��]�p���擾
	Vector3 trans = m_ObjPlayer[BODY].GetTranslation();

	//�ړ�
	trans += m_Velocity;

	//�ړ��������W�𔽉f
	m_ObjPlayer[BODY].SetTranslation(trans);

	//2D���[�h�̏���
	if (m_mode_flag == false)
	{
		//Z����2D�ɖ߂�
		//this->SetTrans(Vector3(this->GetTrans().x, this->GetTrans().y, 0.0f));

		//���L�[��������
		if (key->IsKeyPress(Keyboard::Keys::Left))
		{
			//�ړ��ʂ̃x�N�g��
			Vector3 moveV(-PLAYER_SPEED, 0.0f, 0.0f);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationX(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//���@�̍��W���ړ�������
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}
		//�E�L�[��������
		if (key->IsKeyPress(Keyboard::Keys::Right))
		{
			//�ړ��ʂ̃x�N�g��
			Vector3 moveV(PLAYER_SPEED, 0.0f, 0.0f);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationX(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//���@�̍��W���ړ�������
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}
	}

	//3D���[�h�̏���
	else
	{
		//��L�[��������
		if (key->IsKeyPress(Keyboard::Keys::Up))
		{
			//�ړ��ʂ̃x�N�g��
			Vector3 moveV(PLAYER_SPEED, 0.0f, 0.0f);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationZ(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//���@�̍��W���ړ�������
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}

		//���L�[��������
		if (key->IsKeyPress(Keyboard::Keys::Down))
		{
			//�ړ��ʂ̃x�N�g��
			Vector3 moveV(-PLAYER_SPEED, 0.0f, 0.0f);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationZ(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//���@�̍��W���ړ�������
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}

		//���L�[��������
		if (key->IsKeyPress(Keyboard::Keys::Left))
		{
			//�ړ��ʂ̃x�N�g��
			Vector3 moveV(0.0f, 0.0f, -PLAYER_SPEED);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationX(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//���@�̍��W���ړ�������
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}
		//�E�L�[��������
		if (key->IsKeyPress(Keyboard::Keys::Right))
		{
			//�ړ��ʂ̃x�N�g��
			Vector3 moveV(0.0f, 0.0f, PLAYER_SPEED);

			float angle = m_ObjPlayer[BODY].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationX(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//���@�̍��W���ړ�������
			Vector3 pos = m_ObjPlayer[BODY].GetTranslation();
			m_ObjPlayer[BODY].SetTranslation(pos + moveV);
		}
	}

	//�s��X�V
	Calc();
}

//�s��X�V
void Player::Calc()
{
	//�v���C���[�̍X�V����
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}

	//�����蔻��̍X�V����
	m_CollisionNodeBody.Update();
}

//�`��
void Player::Draw()
{
	////�e�p�[�c�̕`��
	//for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	//{
	//	it->Draw();
	//}

	m_CollisionNodeBody.Draw();
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

//�v���C���[�̊p�x���Z�b�g����
void Player::SetTrans(const Vector3& translation)
{
	m_ObjPlayer[BODY].SetTranslation(translation);
}

//�v���C���[�̈ړ����Z�b�g����
void Player::SetRot(const Vector3& rotation)
{
	m_ObjPlayer[BODY].SetRotation(rotation);
}

//�v���C���[�̃��[���h�s����擾����
const DirectX::SimpleMath::Matrix& Player::GetWor()
{
	return m_ObjPlayer[BODY].GetWorld();
}

//�W�����v�J�n
void Player::StartJump()
{
	//�W�����v���łȂ���
	if (!m_isJump)
	{
		// ������̏�����ݒ�
		m_Velocity.y = JUMP_SPEED_FIRST;
		m_isJump = true;
	}
}

//�W�����v�I��
void Player::StopJump()
{
	m_isJump = false;
	m_Velocity = Vector3::Zero;
}