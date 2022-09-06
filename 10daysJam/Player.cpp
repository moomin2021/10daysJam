#include "Player.h"

// --インスタンスにNULLを代入-- //
Player* Player::myInstance = nullptr;

// --インスタンス読み込み-- //
Player* Player::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new Player();

	// --インスタンスを返す-- //
	return myInstance;
}

// --コンストラクタ-- //
Player::Player() {

}

// --デストラクタ-- //
Player::~Player() {

}

// --初期化処理-- //
void Player::Initialize() {

}

// --更新処理-- //
void Player::Update() {

}

// --描画処理-- //
void Player::Draw() {

}