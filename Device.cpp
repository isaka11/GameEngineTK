#include "pch.h"
#include "Device.h"

using namespace DirectX;
using namespace Library;
using Microsoft::WRL::ComPtr;

//�ÓI�����o�ϐ��̎���
std::unique_ptr<Device> Device::m_Instance;

//�C���X�^���X�̎擾
Device* Device::GetInstance()
{
	if (!m_Instance)
	{
		//�f�o�C�X�̐���
		m_Instance = std::make_unique<Device>();
	}

	return m_Instance.get();
}

//�R���X�g���N�^
Device::Device()
{

}