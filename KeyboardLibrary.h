#pragma once

#include <Keyboard.h>

namespace Library
{
	class KeyboardLibrary
	{
	public:
		static KeyboardLibrary* GetInstance();						//インスタンスの取得

	private:
		static std::unique_ptr<KeyboardLibrary> m_Instance;			//インスタンス

	public:	
		KeyboardLibrary();											//コンストラクタ	
		void Update();												//更新処理
		bool IsKeyPress(DirectX::Keyboard::Keys key);				//キーを押したか
		bool IsKeyTrigger(DirectX::Keyboard::Keys key);				//キーのトリガー処理
		bool IsKeyReleas(DirectX::Keyboard::Keys key);				//キーを離したか

	protected:
		std::unique_ptr<DirectX::Keyboard> m_Keyboard;				//キーボード
		DirectX::Keyboard::State m_State;							//ステート
		DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;	//キーボードトラッカー
	};
}