#pragma once
#include "SceneBase.h"

class Clear : public SceneBase
{
private:
	static SceneBase* m_base;

public:
	Clear();
	~Clear();
	void Initialize();
	void Update(CGame* scene);
	void Render();
	void Dispose();
	static SceneBase* GetInstance();
};