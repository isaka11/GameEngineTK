//----------------------------------------------------------
// ���@�ɒǏ]����J�����N���X
//----------------------------------------------------------
#pragma once
#include "Camera.h"
#include "Player.h"

class FollowCamera : public Camera
{
protected:
	float m_camera_timer;							//�J�����ړ����Ɏ��Ԃ𑪒肷��
	bool m_timer_flag;								//�^�C�}�[�̏�ԃt���O
	bool m_camera_move_flag;						//�J�������ړ������ǂ����̃t���O
	DirectX::SimpleMath::Vector3 m_target_pos;		//�Ǐ]�Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_target_angle;	//�Ǐ]�Ώۂ̉�]�p
	Player* m_player;								//�v���C���[

public:
	//�萔�錾
	static const float MOVE_TIME;											//�J�����ړ��ɂ����鎞��				
	static const float VIEWPOINT_X;											//���_�̍��W(X��)
	static const float VIEWPOINT_Y;											//���_�̍��W(Y��)
	static const float VIEWPOINT_Z;											//���_�̍��W(Z��)
	FollowCamera(int width, int height);									//�R���X�g���N�^
	void Update() override;													//�X�V����
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);		//�Ǐ]�Ώۂ̍��W���Z�b�g
	void SetTargetAngle(const DirectX::SimpleMath::Vector3& targetangle);	//�Ǐ]�Ώۂ̊p�x���Z�b�g
	void SetPlayer(Player* player) { m_player = player; }					//�v���C���[���Z�b�g
	bool GetCameraMoveFlag() { return m_camera_move_flag; }					//m_camera_move_flag���擾����
};