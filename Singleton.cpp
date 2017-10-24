#include "pch.h"
#include "Singleton.h"

Singleton* Singleton::singleton = NULL;

Singleton::Singleton()
{
	//�������Ȃ�
}

Singleton::Singleton(const Singleton& src)
{
	singleton = src.singleton;
}

Singleton& Singleton::operator=(const Singleton & src)
{
	singleton = src.singleton;
	return *this;
}

void Singleton::Initialize()
{
}

Singleton::~Singleton()
{
	delete singleton;
}

Singleton * Singleton::GetInstance()
{
	if (singleton == NULL)
	{
		//�������̊m��
		singleton = new Singleton();

		//������
		singleton->Initialize();
	}
	return nullptr;
}
