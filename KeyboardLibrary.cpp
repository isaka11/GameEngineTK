#include "pch.h"
#include "KeyboardLibrary.h"

using namespace DirectX;
using namespace Library;

//静的メンバ変数の実体
std::unique_ptr<KeyboardLibrary> KeyboardLibrary::m_Instance;

//インスタンスの取得
KeyboardLibrary* KeyboardLibrary::GetInstance()
{
	if (!m_Instance)
	{
		//キーボードライブラリの生成
		m_Instance = std::make_unique<KeyboardLibrary>();
	}

	return m_Instance.get();
}

//コンストラクタ
KeyboardLibrary::KeyboardLibrary()
{
	//キーボードの生成
	m_Keyboard = std::make_unique<Keyboard>();
}

//更新処理
void KeyboardLibrary::Update()
{
	//キーボードステートを取得
	m_State = m_Keyboard->GetState();

	//トリガー状態の更新
	m_KeyboardTracker.Update(m_State);
}

//キーを押したか
bool KeyboardLibrary::IsKeyPress(DirectX::Keyboard::Keys key)
{
	return m_State.IsKeyDown(key);
}

//キーのトリガー処理
bool KeyboardLibrary::IsKeyTrigger(DirectX::Keyboard::Keys key)
{
	return m_KeyboardTracker.IsKeyPressed(key);
}

//キーを離したか
bool KeyboardLibrary::IsKeyReleas(DirectX::Keyboard::Keys key)
{
	return m_KeyboardTracker.IsKeyReleased(key);
}