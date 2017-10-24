#include "TitleScene.h"
#include "ClearScene.h"
#include "GameScene.h"
#include "KeyboardLibrary.h"

using namespace DirectX;
using namespace Library;

SceneBase* Title::m_base = nullptr;

Title::Title()
{

}

Title::~Title()
{
	Dispose();
}

void Title::Initialize(/*DirectX::Keyboard* keyboard*/)
{
	m_a = 0;

	GetInstance(); 
}

void Title::Update(CGame* scene)
{
	KeyboardLibrary* key = KeyboardLibrary::GetInstance();
	
	key->Update();

	if (key->IsKeyPress(Keyboard::Keys::Space))
	{
		scene->ChangeScene(GameScene::GetInstance());
	}

	//m_a++;
	
	if (m_a == 60)
	{
		scene->ChangeScene(GameScene::GetInstance());
	}
}

void Title::Render()
{

}

SceneBase* Title::GetInstance()
{
	if (m_base == nullptr)
	{
		m_base = new Title();
	}
	return m_base;
}

void Title::Dispose()
{
	if (m_base != nullptr)
	{
		delete m_base;
	}
}