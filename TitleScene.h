#pragma once
#include "SceneBase.h"

class Title : public SceneBase
{
private:
	static SceneBase* m_base;

	int m_a;

public:
	Title();		//�R���X�g���N�^
	~Title();		//�f�X�g���N�^
	void Initialize();				//����������
	void Update(CGame* scene);		//�X�V����
	void Render();		//�`�揈��
	void Dispose();		
	static SceneBase* GetInstance();
};