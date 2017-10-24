//----------------------------------------------------------
// 自機に追従するカメラクラス
//----------------------------------------------------------
#pragma once
#include "Camera.h"
#include "Player.h"

class FollowCamera : public Camera
{
protected:
	float m_camera_timer;							//カメラ移動中に時間を測定する
	bool m_timer_flag;								//タイマーの状態フラグ
	bool m_camera_move_flag;						//カメラが移動中かどうかのフラグ
	DirectX::SimpleMath::Vector3 m_target_pos;		//追従対象の座標
	DirectX::SimpleMath::Vector3 m_target_angle;	//追従対象の回転角
	Player* m_player;								//プレイヤー

public:
	//定数宣言
	static const float MOVE_TIME;											//カメラ移動にかかる時間				
	static const float VIEWPOINT_X;											//視点の座標(X軸)
	static const float VIEWPOINT_Y;											//視点の座標(Y軸)
	static const float VIEWPOINT_Z;											//視点の座標(Z軸)
	FollowCamera(int width, int height);									//コンストラクタ
	void Update() override;													//更新処理
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);		//追従対象の座標をセット
	void SetTargetAngle(const DirectX::SimpleMath::Vector3& targetangle);	//追従対象の角度をセット
	void SetPlayer(Player* player) { m_player = player; }					//プレイヤーをセット
	bool GetCameraMoveFlag() { return m_camera_move_flag; }					//m_camera_move_flagを取得する
};