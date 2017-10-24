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

	// デバイス
	ID3D11Device* m_device;

	// コンテキスト
	ID3D11DeviceContext* m_context;

	//// キーボード関係
	//std::unique_ptr<DirectX::Keyboard> m_keyboard;
	//std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;
};