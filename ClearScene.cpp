#include "ClearScene.h"

SceneBase* Clear::m_base = nullptr;

Clear::Clear()
{

}

Clear::~Clear()
{
	Dispose();
}

void Clear::Initialize()
{
	GetInstance();
}

void Clear::Update(CGame* scene)
{
	
}

void Clear::Render()
{

}

SceneBase* Clear::GetInstance()
{
	if (m_base == nullptr)
	{
		m_base = new Clear();
	}
	return m_base;
}

void Clear::Dispose()
{
	if (m_base != nullptr)
	{
		delete m_base;
	}
}