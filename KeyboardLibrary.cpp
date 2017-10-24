#include "pch.h"
#include "KeyboardLibrary.h"

using namespace DirectX;
using namespace Library;

//�ÓI�����o�ϐ��̎���
std::unique_ptr<KeyboardLibrary> KeyboardLibrary::m_Instance;

//�C���X�^���X�̎擾
KeyboardLibrary* KeyboardLibrary::GetInstance()
{
	if (!m_Instance)
	{
		//�L�[�{�[�h���C�u�����̐���
		m_Instance = std::make_unique<KeyboardLibrary>();
	}

	return m_Instance.get();
}

//�R���X�g���N�^
KeyboardLibrary::KeyboardLibrary()
{
	//�L�[�{�[�h�̐���
	m_Keyboard = std::make_unique<Keyboard>();
}

//�X�V����
void KeyboardLibrary::Update()
{
	//�L�[�{�[�h�X�e�[�g���擾
	m_State = m_Keyboard->GetState();

	//�g���K�[��Ԃ̍X�V
	m_KeyboardTracker.Update(m_State);
}

//�L�[����������
bool KeyboardLibrary::IsKeyPress(DirectX::Keyboard::Keys key)
{
	return m_State.IsKeyDown(key);
}

//�L�[�̃g���K�[����
bool KeyboardLibrary::IsKeyTrigger(DirectX::Keyboard::Keys key)
{
	return m_KeyboardTracker.IsKeyPressed(key);
}

//�L�[�𗣂�����
bool KeyboardLibrary::IsKeyReleas(DirectX::Keyboard::Keys key)
{
	return m_KeyboardTracker.IsKeyReleased(key);
}