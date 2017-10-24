#pragma once
#include "SceneBase.h"

//クラスの定義
class SceneBase;

//ゲーム管理クラス
class CGame
{
private:
	SceneBase* m_Scene; // シーンオブジェクト

public:
	CGame();
	~CGame();

	// シーン列挙型
	void ChangeScene(SceneBase* scene); // シーンの遷移
	void Initialize();
	void Update();
	void Render(); // シーンの描画
};