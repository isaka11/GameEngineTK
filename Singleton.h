#pragma once

class Singleton
{
private:
	static Singleton* singleton;					//Singleton�p�̃C���X�^���X

private:
	Singleton();									//�R���X�g���N�^
	Singleton(const Singleton& src);				//�R�s�[�R���X�g���N�^ src=�R�s�[��
	Singleton& operator=(const Singleton& src);		//������Z�q src=�R�s�[��
	void Initialize();								//����������

public:
	virtual ~Singleton();							//�f�X�g���N�^
	static Singleton* GetInstance();				//�C���X�^���X���擾����
};