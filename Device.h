#pragma once

#include <d3d11.h>
#include <memory>
#include <Model.h>

namespace Library
{
	class Device
	{
	public:
		static Device* GetInstance();						//インスタンスの取得

	private:
		static std::unique_ptr<Device> m_Instance;			//インスタンス

	public:
		Device();											//コンストラクタ
		int	GetWidth() { return m_outputWidth; }
		int	GetHeight() { return m_outputHeight; }
		Microsoft::WRL::ComPtr<ID3D11Device> GetDevice(){ return m_d3dDevice; }
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() { return m_d3dContext; }

		void SetWidth(int width) { m_outputWidth = width; }
		void SetHeight(int height) { m_outputHeight = height; }
		void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device) { m_d3dDevice = device; }
		void SetContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context) { m_d3dContext = context; }

	private:
		int                                             m_outputWidth;
		int                                             m_outputHeight;
		Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	};
}