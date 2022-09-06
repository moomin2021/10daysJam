#include "Input.h"
#include"DxLib.h"

// --インスタンスにNULLを代入-- //
Input* Input::myInstance = nullptr;

// --インスタンス読み込み-- //
Input* Input::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new Input();

	// --インスタンスを返す-- //
	return myInstance;
}

// --コンストラクタ-- //
Input::Input() {

}

// --更新処理-- //
void Input::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}

	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

// --キーが押された瞬間か-- //
bool Input::IsTrigger(char key) { return (keys[key] && !oldkeys[key]); }

// --キーが押されているか-- //
bool Input::IsPress(char key) { return keys[key]; }

// --キーが離された瞬間か-- //
bool Input::IsRelease(char key) { return (!keys[key] && oldkeys[key]); }
