#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

FollowCamera::FollowCamera(int width, int height) :Camera(width, height)
{
	m_target_pos = Vector3::Zero;
	m_target_angle = 0.0;
	m_keyboard = nullptr;
	m_isFPS = false;
}

void FollowCamera::Update()
{
	//���_�A�Q�Ɠ_���W
	Vector3 eyepos, refpos;

	//�L�[�{�[�h�̏�Ԏ擾
	Keyboard::State keyboardstate = m_keyboard->GetState();
	m_keyboardTracker.Update(keyboardstate);

	//C�L�[���������Ƃ�FPS/TPS��؂�ւ�
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keys::C))
	{
		//�t���O��؂�ւ�
		if (m_isFPS == false)
		{
			m_isFPS = true;
		}
		else if (m_isFPS == true)
		{
			m_isFPS = false;
		}
	}

	//TPS�J����
	if (m_isFPS == false)
	{
		//���@�̏��2m���Q�Ɠ_�ɂ���
		refpos = m_target_pos + Vector3(0, 2, 0);

		//�Q�Ɠ_�Ǝ��_�̍����x�N�g��
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		//���@�̌��ɉ�荞�ނ��߂̉�]�s��𐶐�
		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);

		//�����x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//���_���W���v�Z
		eyepos = refpos + cameraV;
	}

	////FPS�J����
	else if (m_isFPS == true)
	{
		//���@�̖ڂ̈ʒu�����_�ɂ���
		Vector3 position;

		eyepos = m_target_pos + Vector3(0, 0.3f, 0);

		position = m_target_pos + Vector3(0, 0.3f, 0);

		//�Q�Ɠ_�Ǝ��_�̍����x�N�g��
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);

		//���@�̌��ɉ�荞�ނ��߂̉�]�s��𐶐�
		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);

		//�����x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//�Q�Ɠ_���W���v�Z
		refpos = eyepos + cameraV;
	}
	//���_�����݈ʒu�����Ԃ���
	eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;

	//�Q�Ɠ_�����݈ʒu�����Ԃ���
	refpos = m_refpos + (refpos - m_refpos) * 0.20f;

	SetEyePos(eyepos);
	SetRefPos(refpos);

	//���N���X�̍X�V����
	Camera::Update();
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_target_pos = targetpos;
}

void FollowCamera::SetTargetAngle(float targetangle)
{
	m_target_angle = targetangle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}

