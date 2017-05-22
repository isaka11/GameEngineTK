#pragma once

#include <Windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"

class Obj3d
{
	//�ÓI�����o�ϐ�
public:
	//�ÓI�����o�ϐ��̏�����
	static void InitializeStatic(
		Microsoft::WRL::ComPtr<ID3D11Device>            d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>     d3dContext,
		Camera* camera);

private:
	//�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;

	//�f�o�C�X�R���e�L�X�g
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;

	//�J����
	static Camera* m_Camera;

	//�ėp�`��X�e�[�g
	static std::unique_ptr<DirectX::CommonStates> m_states;

	//�G�t�F�N�g�t�@�N�g��
	static std::unique_ptr<DirectX::EffectFactory> m_factory;

public:
	//�R���X�g���N�^
	Obj3d();

	//���f�������[�h����
	void LoadModel(const wchar_t* fileName);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//setter
	//�X�P�[�����O(X Y Z)

	//��]�p(X Y Z)

	//���s�ړ�(X Y Z)

	//getter
	//�X�P�[�����O(X Y Z)

	//��]�p(X Y Z)

	//���s�ړ�(X Y Z)

	//���[���h�s��


private:
	//�����o�ϐ�
	//3D���f��

	//�X�P�[�����O(X Y Z)

	//��]�p(X Y Z)

	//���s�ړ�(X Y Z)

	//���[���h�s��

};