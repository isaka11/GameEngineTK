#include "pch.h"
#include "Singleton.h"

Singleton* Singleton::singleton = NULL;

Singleton::Singleton()
{
	//‰½‚à‚µ‚È‚¢
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
		//ƒƒ‚ƒŠ‚ÌŠm•Û
		singleton = new Singleton();

		//‰Šú‰»
		singleton->Initialize();
	}
	return nullptr;
}
