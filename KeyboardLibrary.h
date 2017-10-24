#pragma once

#include <Keyboard.h>

namespace Library
{
	class KeyboardLibrary
	{
	public:
		static KeyboardLibrary* GetInstance();						//�C���X�^���X�̎擾

	private:
		static std::unique_ptr<KeyboardLibrary> m_Instance;			//�C���X�^���X

	public:	
		KeyboardLibrary();											//�R���X�g���N�^	
		void Update();												//�X�V����
		bool IsKeyPress(DirectX::Keyboard::Keys key);				//�L�[����������
		bool IsKeyTrigger(DirectX::Keyboard::Keys key);				//�L�[�̃g���K�[����
		bool IsKeyReleas(DirectX::Keyboard::Keys key);				//�L�[�𗣂�����

	protected:
		std::unique_ptr<DirectX::Keyboard> m_Keyboard;				//�L�[�{�[�h
		DirectX::Keyboard::State m_State;							//�X�e�[�g
		DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;	//�L�[�{�[�h�g���b�J�[
	};
}