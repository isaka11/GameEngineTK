#include "pch.h"
#include "DxtkResouce.h"

using namespace DirectX;

DxtkResouce::DxtkResouce()
{
	//m_keyboard = std::make_unique<Keyboard>();
	//m_keyTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
	m_outputWidth = 800;
	m_outputHeight = 600;
}

void DxtkResouce::Initialize(ID3D11Device * device, ID3D11DeviceContext * context)
{
	m_device = device;
	m_context = context;
}

void DxtkResouce::Update()
{
	//Keyboard::State key = m_keyboard->GetState();
	//m_keyTracker->Update(key);
}
