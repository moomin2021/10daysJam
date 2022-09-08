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
Player::Player() : player{ { 0, 0 }, 16 }, playerSpd(2.0f), playerLength(player.radius), range(90.0f),
auxiliaryCircle{ {640, 480}, 8 }, controlMode(MODE1)
{
	input = Input::GetInstance();
	pad = JoyPadInput::GetInstance();
}


// --デストラクタ-- //
Player::~Player() {

}

// --初期化処理-- //
void Player::Initialize() {
	
}

// --更新処理-- //
void Player::Update(Line hourHand, Circle clock, float radius) {

#pragma region 自機移動関係

	// --プレイヤーが外側内側どちらに進むか（1 = 外側, -1 = 内側）-- //
	int playerMoveAdd = 0;

	// --操作モード1-- //
	if (controlMode == MODE1) {
		// --左スティックが倒れている角度を求める-- //
		float stickAngle;
		{
			// --スティックのベクトル-- //
			Vector2 lStickVec = { (float)pad->GetLeftStickX(), (float)pad->GetLeftStickY() };

			// --2つのベクトルのなす角を求める-- //
			stickAngle = lStickVec.dot(Vector2(0, -1)) / (lStickVec.length() * Vector2(0, -1).length());
			stickAngle = acos(stickAngle);
			stickAngle = Util::Radian2Degree(stickAngle);

			if (pad->GetLeftStickX() < 0) stickAngle = 180 + (180 - stickAngle);
		}

		// --短針の角度を求める-- //
		float hourHandAngle;
		{
			// --短針のベクトル-- //
			Vector2 hourHandVec = { hourHand.end.x - hourHand.start.x, hourHand.end.y - hourHand.start.y };

			// --2つのベクトルのなす角を求める-- //
			hourHandAngle = hourHandVec.dot(Vector2(0, -1)) / (hourHandVec.length() * Vector2(0, -1).length());
			hourHandAngle = acos(hourHandAngle);
			hourHandAngle = Util::Radian2Degree(hourHandAngle);

			if (hourHandVec.x < 0) hourHandAngle = 180 + (180 - hourHandAngle);
		}

		// --判定-- //
		{
			if (((hourHandAngle + range) > stickAngle) && ((hourHandAngle - range) < stickAngle)) {
				playerMoveAdd = 1;
			}

			if (hourHandAngle + range > 360.0f) {
				if ((hourHandAngle + range) - 360.0f > stickAngle) playerMoveAdd = 1;
			}

			if (hourHandAngle - range < 0) {
				if (360 - (hourHandAngle - range) < stickAngle) playerMoveAdd = 1;
			}

			hourHandAngle = fmodf(hourHandAngle + 180.0f, 360.0f);

			if (((hourHandAngle + range) > stickAngle) && ((hourHandAngle - range) < stickAngle)) {
				playerMoveAdd = -1;
			}

			if (hourHandAngle + range > 360.0f) {
				if ((hourHandAngle + range) - 360.0f > stickAngle) playerMoveAdd = -1;
			}

			if (hourHandAngle - range < 0) {
				if (360 - (hourHandAngle - range) < stickAngle) playerMoveAdd = -1;
			}
		}
	}

	// --操作モード2-- //
	else if (controlMode == MODE2) {
		playerMoveAdd += pad->GetButton(PAD_INPUT_1) - pad->GetButton(PAD_INPUT_2);
	}

	// --操作モード3-- //
	else if (controlMode == MODE3) {
		if (pad->GetLeftStickHorizontal() == 1 && pad->GetRightStickHorizontal() == -1) playerMoveAdd = -1;
		else if (pad->GetLeftStickHorizontal() == -1 && pad->GetRightStickHorizontal() == 1) playerMoveAdd = 1;
	}

	// --中心からのプレイヤーの距離-- //
	playerLength += playerMoveAdd * playerSpd;
	
	// --プレイヤーが移動できるのを制限-- //
	playerLength = Clamp(playerLength, hourHand.length, radius + player.radius);

	//短針上での自機の位置を参照して自機座標計算
	//自機は短針上に位置するので、角度は短針のものを使う
	player.pos.x = (playerLength * cosf((hourHand.radian - 90) / 180 * PI)) + clock.pos.x;
	player.pos.y = (playerLength * sinf((hourHand.radian - 90) / 180 * PI)) + clock.pos.y;

	auxiliaryCircle.radius = playerLength;
#pragma endregion

	// --デバック用処理-- //
	playerSpd += ((input->IsPress(KEY_INPUT_E) - input->IsPress(KEY_INPUT_Q)) * 0.2f);
	if (input->IsPress(KEY_INPUT_R)) playerSpd = 2.0f;
	playerSpd = Clamp(playerSpd, 100.0f, 0.1f);
	if (input->IsTrigger(KEY_INPUT_1)) controlMode = MODE1;
	if (input->IsTrigger(KEY_INPUT_2)) controlMode = MODE2;
	if (input->IsTrigger(KEY_INPUT_3)) controlMode = MODE3;
}

// --描画処理-- //
void Player::Draw() {
	DrawCircle(player, color, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawCircle(auxiliaryCircle, 0xFFFFFF, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 125);

	// --デバック用処理
	DrawFormatString(0, 20, 0xFFFFFF, "QEキー:プレイヤーの速度変更");
	DrawFormatString(0, 40, 0xffffff, "Rキー:プレイヤーの速度リセット");
	DrawFormatString(0, 60, 0xffffff, "プレイヤー速度:%f", playerSpd);
	DrawFormatString(0, 240, 0xFFFFFF, "123キーで操作のモードを変える");
	DrawFormatString(0, 260, 0xFFFFFF, "操作モード:モード%d", controlMode + 1);
}