#include "TitleScene.h"

// --インスタンスにNULLを代入-- //
TitleScene* TitleScene::myInstance = nullptr;

// --インスタンス読み込み-- //
TitleScene* TitleScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new TitleScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --コンストラクタ-- //
TitleScene::TitleScene() {

}

// --デストラクタ-- //
TitleScene::~TitleScene() {

}

// --初期化処理-- //
void TitleScene::Initialize() {

}

// --更新処理-- //
void TitleScene::Update() {

}

// --描画処理-- //
void TitleScene::Draw() {

}