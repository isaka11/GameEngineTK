#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�ÓI�����o�ϐ��̎���
//�f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device>            Obj3d::m_d3dDevice;

//�f�o�C�X�R���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext>     Obj3d::m_d3dContext;

//�J����
Camera* Obj3d::m_Camera;

//�ėp�`��X�e�[�g
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;

//�G�t�F�N�g�t�@�N�g��
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	//�ėp�`��X�e�[�g����
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	//�G�t�F�N�g�t�@�N�g���̐���
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());

	//�e�N�X�`���̓ǂݍ��݃p�X�̎w��
	m_factory->SetDirectory(L"Resources");
}

Obj3d::Obj3d()
{
	//�X�P�[����1�{���f�t�H���g
	m_scale = Vector3(1.0f, 1.0f, 1.0f);

	m_parent = nullptr;
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	//���f���̓ǂݍ��݁A����
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obj3d::Update()
{
	//�s��̌v�Z

	//�X�P�[�����O�s��
	Matrix scalemat = Matrix::CreateScale(m_scale);

	//��]�s��
	Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
	Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
	Matrix rotmatX = Matrix::CreateRotationY(m_rotation.x);

	Matrix rotmat = rotmatZ * rotmatX * rotmatY;

	//���s�ړ��s��
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//���[���h�s�������
	m_world = scalemat * rotmat * transmat;

	//�e�̍s���������
	if (m_parent)
	{
		m_world *= m_parent->m_world;
	}
}

void Obj3d::Draw()
{
	assert(m_Camera);

	//3D���f���̕`��
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetView(), m_Camera->GetProj());
	}
}