#pragma once

#include <Keyboard.h>
#include <d3d11.h>

class DxtkResouce
{
public:
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* context);

	void Update();

private:
	DxtkResouce();

	int m_outputWidth;
	int m_outputHeight;

	// �f�o�C�X
	ID3D11Device* m_device;

	// �R���e�L�X�g
	ID3D11DeviceContext* m_context;

	//// �L�[�{�[�h�֌W
	//std::unique_ptr<DirectX::Keyboard> m_keyboard;
	//std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;
};