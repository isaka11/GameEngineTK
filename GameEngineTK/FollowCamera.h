//----------------------------------------------------------
// 自機に追従するカメラクラス
//----------------------------------------------------------
#pragma once
#include "Camera.h"

class FollowCamera : public Camera
{
protected:
	
	DirectX::SimpleMath::Vector3 m_target_pos;		//追従対象の座標
	float m_target_angle;							//追従対象の回転角

public:
	static const float CAMERA_DISTANCE;				//自機とカメラの距離
	FollowCamera(int width, int height);			//コンストラクタ
	void Update() override;							//更新処理
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);	//追従対象の座標をセット
	void SetTargetAngle(float targetangle);	//追従対象の角度をセット
};