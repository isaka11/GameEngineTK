//----------------------------------------------------------
// ���@�ɒǏ]����J�����N���X
//----------------------------------------------------------
#pragma once
#include "Camera.h"

class FollowCamera : public Camera
{
protected:
	
	DirectX::SimpleMath::Vector3 m_target_pos;		//�Ǐ]�Ώۂ̍��W
	float m_target_angle;							//�Ǐ]�Ώۂ̉�]�p

public:
	static const float CAMERA_DISTANCE;				//���@�ƃJ�����̋���
	FollowCamera(int width, int height);			//�R���X�g���N�^
	void Update() override;							//�X�V����
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);	//�Ǐ]�Ώۂ̍��W���Z�b�g
	void SetTargetAngle(float targetangle);	//�Ǐ]�Ώۂ̊p�x���Z�b�g
};