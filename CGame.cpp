#include "CGame.h"

CGame::CGame()
{
	m_Scene = nullptr;
}

CGame::~CGame()
{

}

void CGame::Initialize()
{
	m_Scene->Initialize(/*m_Scene->m_pKeyboard*/);
}

void CGame::ChangeScene(SceneBase* scene)
{
	m_Scene = scene;
	m_Scene->Initialize(/*m_Scene->m_pKeyboard*/);
}

void CGame::Update()
{
	m_Scene->Update(this);
}

void CGame::Render()
{
	m_Scene->Render();
}