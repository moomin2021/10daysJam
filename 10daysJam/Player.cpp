#include "Player.h"
#include "DxLib.h"
using namespace Util;
#include "GameScene.h"

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
Player::Player() : player{ 0, 0, 16 }, playerSpd(2.0f), playerPos(0){
	input = Input::GetInstance();
}

// --デストラクタ-- //
Player::~Player() {

}

// --初期化処理-- //
void Player::Initialize() {

}

// --更新処理-- //
void Player::Update(Line hourHand, Circle clock) {
#pragma region 自機移動関係
	//自機移動
	if (input->IsPress(KEY_INPUT_A) || input->IsPress(KEY_INPUT_S) || input->IsPress(KEY_INPUT_W) || input->IsPress(KEY_INPUT_D)) {

		//ADキーで短針上での位置を変更
		playerPos += ((input->IsPress(KEY_INPUT_D) - input->IsPress(KEY_INPUT_A)) * playerSpd);
		//最大値は短針の長さ
		if (playerPos > hourHand.length)playerPos = hourHand.length;

	}

	//短針上での自機の位置を参照して自機座標計算
	//自機は短針上に位置するので、角度は短針のものを使う
	player.x = (playerPos * sinf(hourHand.radian / 180 * PI)) + clock.x;
	player.y = (playerPos * cosf(hourHand.radian / 180 * PI)) + clock.y;


	//アローキーで自機速度変更
	playerSpd += ((input->IsPress(KEY_INPUT_E) - input->IsPress(KEY_INPUT_Q)) * 0.2f);
	if (input->IsPress(KEY_INPUT_R)) playerSpd = 2.0f;

#pragma endregion
}

// --描画処理-- //
void Player::Draw() {
	DrawCircle(player, 0xffffff, true);
}