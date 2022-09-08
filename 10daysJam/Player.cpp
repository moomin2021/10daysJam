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
Player::Player()
{
	/// --インスタンス読み込み-- ///
#pragma region
	// --キーボードクラス-- //
	input = Input::GetInstance();

	// --コントローラークラス-- //
	pad = JoyPadInput::GetInstance();
#pragma endregion
	/// --END-- ///

	/// --プレイヤー関係変数の初期化-- ///
#pragma region
	// --プレイヤー-- //
	player = { {0, 0}, 16 };

	// --プレイヤーの速度-- //
	playerSpeed = 2.0f;

	// --中心からのプレイヤーの距離-- //
	playerLength = player.radius;
#pragma endregion
	/// --END-- ///

	/// --その他の初期化-- ///
#pragma region
	// --スティックの範囲-- //
	stickRange = 90.0f;

	// --操作モード-- //
	controlMode = MODE2;

	// --補助線-- //
	auxiliaryCircle = { {640, 480}, 8 };
#pragma endregion
	/// --END-- ///
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
			if (((hourHandAngle + stickRange) > stickAngle) && ((hourHandAngle - stickRange) < stickAngle)) {
				playerMoveAdd = 1;
			}

			if (hourHandAngle + stickRange > 360.0f) {
				if ((hourHandAngle + stickRange) - 360.0f > stickAngle) playerMoveAdd = 1;
			}

			if (hourHandAngle - stickRange < 0) {
				if (360 - (hourHandAngle - stickRange) < stickAngle) playerMoveAdd = 1;
			}

			hourHandAngle = fmodf(hourHandAngle + 180.0f, 360.0f);

			if (((hourHandAngle + stickRange) > stickAngle) && ((hourHandAngle - stickRange) < stickAngle)) {
				playerMoveAdd = -1;
			}

			if (hourHandAngle + stickRange > 360.0f) {
				if ((hourHandAngle + stickRange) - 360.0f > stickAngle) playerMoveAdd = -1;
			}

			if (hourHandAngle - stickRange < 0) {
				if (360 - (hourHandAngle - stickRange) < stickAngle) playerMoveAdd = -1;
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
	playerLength += playerMoveAdd * playerSpeed;
	
	// --プレイヤーが移動できるのを制限-- //
	playerLength = Clamp(playerLength, hourHand.length, radius + player.radius);

	//短針上での自機の位置を参照して自機座標計算
	//自機は短針上に位置するので、角度は短針のものを使う
	player.pos.x = (playerLength * cosf((hourHand.radian - 90) / 180 * PI)) + clock.pos.x;
	player.pos.y = (playerLength * sinf((hourHand.radian - 90) / 180 * PI)) + clock.pos.y;

	auxiliaryCircle.radius = playerLength;
#pragma endregion

	// --デバック用処理-- //
	playerSpeed += ((input->IsPress(KEY_INPUT_E) - input->IsPress(KEY_INPUT_Q)) * 0.2f);
	if (input->IsPress(KEY_INPUT_R)) playerSpeed = 2.0f;
	playerSpeed = Clamp(playerSpeed, 100.0f, 0.1f);
	if (input->IsTrigger(KEY_INPUT_1)) controlMode = MODE1;
	if (input->IsTrigger(KEY_INPUT_2)) controlMode = MODE2;
	if (input->IsTrigger(KEY_INPUT_3)) controlMode = MODE3;
}

// --描画処理-- //
void Player::Draw(Camera camera_) {
	
	Circle pos = {
		player.pos + camera_.GetPos(),
		player.radius
	};

	Circle pos2 = {
		auxiliaryCircle.pos + camera_.GetPos(),
		auxiliaryCircle.radius
	};

	DrawCircle(pos, color, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawCircle(pos2, 0xFFFFFF, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 125);

	// --デバック用処理
	DrawFormatString(0, 20, 0xFFFFFF, "QEキー:プレイヤーの速度変更");
	DrawFormatString(0, 40, 0xffffff, "Rキー:プレイヤーの速度リセット");
	DrawFormatString(0, 60, 0xffffff, "プレイヤー速度:%f", playerSpeed);
	DrawFormatString(0, 240, 0xFFFFFF, "123キーで操作のモードを変える");
	DrawFormatString(0, 260, 0xFFFFFF, "操作モード:モード%d", controlMode + 1);
}