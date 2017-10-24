#pragma once
#include "SceneBase.h"

class Title : public SceneBase
{
private:
	static SceneBase* m_base;

	int m_a;

public:
	Title();		//コンストラクタ
	~Title();		//デストラクタ
	void Initialize();				//初期化処理
	void Update(CGame* scene);		//更新処理
	void Render();		//描画処理
	void Dispose();		
	static SceneBase* GetInstance();
};