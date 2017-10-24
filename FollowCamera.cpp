#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

//静的メンバ変数の初期化
const float FollowCamera::MOVE_TIME = 60.0f;
const float FollowCamera::VIEWPOINT_X = 7.5f;
const float FollowCamera::VIEWPOINT_Y = 10.0f;
const float FollowCamera::VIEWPOINT_Z = 15.0f;

//コンストラクタ
FollowCamera::FollowCamera(int width, int height) :Camera(width, height)
{
	m_target_pos = Vector3::Zero;
	m_target_angle = Vector3::Zero;
	m_player = nullptr;
	m_camera_timer = 0.0f;
	m_timer_flag = false;
	m_camera_move_flag = false;
}

//更新処理
void FollowCamera::Update()
{
	//視点、参照点座標
	Vector3 eyepos, refpos;

	if (m_player)
	{
		SetTargetPos(m_player->GetTrans());
		SetTargetAngle(m_player->GetRot());
	}

	//2Dカメラ
	if (m_player->Get_Mode() == false)
	{
		//初期化
		if (m_timer_flag == true)
		{
			m_camera_timer = 0.0f;
			m_timer_flag = false;
		}

		//1秒経過までタイマーを計測する
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

		//ゲーム開始時のカメラの位置
		if (m_player->GetFirstPosFlag() == false)
		{
			//参照点
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

			//参照点と視点の差分ベクトル
			Vector3 cameraV(0.0f, 0.0f, VIEWPOINT_Z);

			//視点座標を計算
			eyepos = refpos + cameraV;
		}
		else
		{
			//参照点
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
			//参照点と視点の差分ベクトル
			Vector3 cameraV
			(
				-VIEWPOINT_X + VIEWPOINT_X * (m_camera_timer / MOVE_TIME),
				VIEWPOINT_Y - VIEWPOINT_Y * (m_camera_timer / MOVE_TIME),
				VIEWPOINT_Z * (m_camera_timer / MOVE_TIME)
			);

			//視点座標を計算
			eyepos = refpos + cameraV;
		}
	}

	//3Dカメラ
	else if (m_player->Get_Mode() == true)
	{
		//初期化
		if (m_timer_flag == false)
		{
			m_camera_timer = 0.0f;
			m_timer_flag = true;
		}

		//1秒経過までタイマーを計測する
		if (m_camera_timer < MOVE_TIME)
		{
			m_camera_timer++;
			m_camera_move_flag = true;
		}
		else
		{
			m_camera_move_flag = false;
		}

		//参照点
		refpos = Vector3(m_target_pos.x + 5.5f - 5.5f * (m_camera_timer / MOVE_TIME),
						 m_target_pos.y - 0.5f + 0.5f * (m_camera_timer / MOVE_TIME),
						 m_target_pos.z + 6.0f - 6.0f * (m_camera_timer / MOVE_TIME));

		//参照点と視点の差分ベクトル
		Vector3 cameraV
		(
			-VIEWPOINT_X * (m_camera_timer / MOVE_TIME), 
			VIEWPOINT_Y * (m_camera_timer / MOVE_TIME), 
			VIEWPOINT_Z - VIEWPOINT_Z * (m_camera_timer / MOVE_TIME));

		//視点座標を計算
		eyepos = refpos + cameraV;
	}

	SetEyePos(eyepos);
	SetRefPos(refpos);

	//基底クラスの更新処理
	Camera::Update();
}
//追従対象の座標をセット
void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_target_pos = targetpos;
}

//追従対象の角度をセット
void FollowCamera::SetTargetAngle(const DirectX::SimpleMath::Vector3& targetangle)
{
	m_target_angle = targetangle;
}