#include "pch.h"
#include "Singleton.h"

Singleton* Singleton::singleton = NULL;

Singleton::Singleton()
{
	//何もしない
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
		//メモリの確保
		singleton = new Singleton();

		//初期化
		singleton->Initialize();
	}
	return nullptr;
}
