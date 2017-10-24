#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

//�ÓI�����o�ϐ��̏�����
const float FollowCamera::MOVE_TIME = 60.0f;
const float FollowCamera::VIEWPOINT_X = 7.5f;
const float FollowCamera::VIEWPOINT_Y = 10.0f;
const float FollowCamera::VIEWPOINT_Z = 15.0f;

//�R���X�g���N�^
FollowCamera::FollowCamera(int width, int height) :Camera(width, height)
{
	m_target_pos = Vector3::Zero;
	m_target_angle = Vector3::Zero;
	m_player = nullptr;
	m_camera_timer = 0.0f;
	m_timer_flag = false;
	m_camera_move_flag = false;
}

//�X�V����
void FollowCamera::Update()
{
	//���_�A�Q�Ɠ_���W
	Vector3 eyepos, refpos;

	if (m_player)
	{
		SetTargetPos(m_player->GetTrans());
		SetTargetAngle(m_player->GetRot());
	}

	//2D�J����
	if (m_player->Get_Mode() == false)
	{
		//������
		if (m_timer_flag == true)
		{
			m_camera_timer = 0.0f;
			m_timer_flag = false;
		}

		//1�b�o�߂܂Ń^�C�}�[���v������
		if (m_player->GetFirstPosFlag() == true)
		{
			if (m_camera_timer < MOVE_TIME)
			{
				m_camera_timer++;
				m_camera_move_flag = true;
			}
			else
			{
				m_camera_move_flag = false;
			}
		}

		//�Q�[���J�n���̃J�����̈ʒu
		if (m_player->GetFirstPosFlag() == false)
		{
			//�Q�Ɠ_
			if (m_player->GetTrans().x < 9.0f)
			{
				refpos = Vector3(14.5f, -26.0f, 6.0f);
			}
			else if (m_player->GetTrans().x > 56.5f)
			{
				refpos = Vector3(62.0f, -26.0f, 6.0f);
			}
			else
			{
				refpos = Vector3(m_target_pos.x + 5.5f, -26.0f, 6.0f);
			}

			//�Q�Ɠ_�Ǝ��_�̍����x�N�g��
			Vector3 cameraV(0.0f, 0.0f, VIEWPOINT_Z);

			//���_���W���v�Z
			eyepos = refpos + cameraV;
		}
		else
		{
			//�Q�Ɠ_
			if (m_player->GetTrans().x < 9.0f)
			{
				refpos = Vector3(14.5f, -26.0f, 6.0f);
			}
			else if (m_player->GetTrans().x > 56.5f)
			{
				refpos = Vector3(62.0f, -26.0f, 6.0f);
			}
			else
			{
				refpos = Vector3(m_target_pos.x + 5.5f * (m_camera_timer / MOVE_TIME), 
									-25.5f - 0.5f * (m_camera_timer / MOVE_TIME),
									6.0f * (m_camera_timer / MOVE_TIME));
			}
			//�Q�Ɠ_�Ǝ��_�̍����x�N�g��
			Vector3 cameraV
			(
				-VIEWPOINT_X + VIEWPOINT_X * (m_camera_timer / MOVE_TIME),
				VIEWPOINT_Y - VIEWPOINT_Y * (m_camera_timer / MOVE_TIME),
				VIEWPOINT_Z * (m_camera_timer / MOVE_TIME)
			);

			//���_���W���v�Z
			eyepos = refpos + cameraV;
		}
	}

	//3D�J����
	else if (m_player->Get_Mode() == true)
	{
		//������
		if (m_timer_flag == false)
		{
			m_camera_timer = 0.0f;
			m_timer_flag = true;
		}

		//1�b�o�߂܂Ń^�C�}�[���v������
		if (m_camera_timer < MOVE_TIME)
		{
			m_camera_timer++;
			m_camera_move_flag = true;
		}
		else
		{
			m_camera_move_flag = false;
		}

		//�Q�Ɠ_
		refpos = Vector3(m_target_pos.x + 5.5f - 5.5f * (m_camera_timer / MOVE_TIME),
						 m_target_pos.y - 0.5f + 0.5f * (m_camera_timer / MOVE_TIME),
						 m_target_pos.z + 6.0f - 6.0f * (m_camera_timer / MOVE_TIME));

		//�Q�Ɠ_�Ǝ��_�̍����x�N�g��
		Vector3 cameraV
		(
			-VIEWPOINT_X * (m_camera_timer / MOVE_TIME), 
			VIEWPOINT_Y * (m_camera_timer / MOVE_TIME), 
			VIEWPOINT_Z - VIEWPOINT_Z * (m_camera_timer / MOVE_TIME));

		//���_���W���v�Z
		eyepos = refpos + cameraV;
	}

	SetEyePos(eyepos);
	SetRefPos(refpos);

	//���N���X�̍X�V����
	Camera::Update();
}
//�Ǐ]�Ώۂ̍��W���Z�b�g
void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_target_pos = targetpos;
}

//�Ǐ]�Ώۂ̊p�x���Z�b�g
void FollowCamera::SetTargetAngle(const DirectX::SimpleMath::Vector3& targetangle)
{
	m_target_angle = targetangle;
}