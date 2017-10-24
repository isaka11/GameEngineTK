#include "pch.h"
#include "Device.h"

using namespace DirectX;
using namespace Library;
using Microsoft::WRL::ComPtr;

//静的メンバ変数の実体
std::unique_ptr<Device> Device::m_Instance;

//インスタンスの取得
Device* Device::GetInstance()
{
	if (!m_Instance)
	{
		//デバイスの生成
		m_Instance = std::make_unique<Device>();
	}

	return m_Instance.get();
}

//コンストラクタ
Device::Device()
{

}