#pragma once

class Singleton
{
private:
	static Singleton* singleton;					//Singleton用のインスタンス

private:
	Singleton();									//コンストラクタ
	Singleton(const Singleton& src);				//コピーコンストラクタ src=コピー元
	Singleton& operator=(const Singleton& src);		//代入演算子 src=コピー元
	void Initialize();								//初期化処理

public:
	virtual ~Singleton();							//デストラクタ
	static Singleton* GetInstance();				//インスタンスを取得する
};