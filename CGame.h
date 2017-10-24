#pragma once
#include "SceneBase.h"

//�N���X�̒�`
class SceneBase;

//�Q�[���Ǘ��N���X
class CGame
{
private:
	SceneBase* m_Scene; // �V�[���I�u�W�F�N�g

public:
	CGame();
	~CGame();

	// �V�[���񋓌^
	void ChangeScene(SceneBase* scene); // �V�[���̑J��
	void Initialize();
	void Update();
	void Render(); // �V�[���̕`��
};