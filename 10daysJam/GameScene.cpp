#include "GameScene.h"
#include "SceneManager.h"
using namespace Util;

// --インスタンスにNULLを代入-- //
GameScene* GameScene::myInstance = nullptr;

// --インスタンス読み込み-- //
GameScene* GameScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new GameScene();

	// --インスタンスを返す-- //
	return myInstance;
}

bool GameScene::CollisionCtoC(Circle cA, Circle cB)
{
	bool flag;
	Vector2 vecAtoB;
	float radius;
	vecAtoB.x = cB.x - cA.x;
	vecAtoB.y = cB.y - cA.y;
	radius = cA.radius + cB.radius;

	if (vecAtoB.length() <= radius) {
		flag = true;
	}
	else {
		flag = false;
	}

	return flag;
}

// --コンストラクタ-- //
GameScene::GameScene() : clock{ 640, 480, 416 },
longHand{ {640, 480}, {640, 0}, clock.radius, 0, 0xFF0000},
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 0, 0xFF }
{
	// --入力クラスインスタンス取得-- //
	input = Input::GetInstance();

	// --プレイヤークラスインスタンス取得-- //
	player = Player::GetInstance();

	// --エネミークラスインスタンス取得-- //
	enemy = Enemy::GetInstance();

	pad = JoyPadInput::GetInstance();
}

// --デストラクタ-- //
GameScene::~GameScene() {
	delete player;
	delete enemy;
}

// --初期化処理-- //
void GameScene::Initialize() {
	// --エネミー初期化-- //
	enemy->Initialize();
}

// --更新処理-- //
void GameScene::Update() {



#pragma region 針の座標計算

	//Lボタンで短針のステートを「反転」に
	if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::normal) {
		hourHand.state = State::reverse;
	}

	//ステートが通常なら短針は自動回転
	if (hourHand.state == State::normal) {
		hourHand.radian += 2.0f;

		hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
	}//ステートが反転しているなら短針を逆走させる
	else if (hourHand.state == State::reverse) {
		hourHand.radian -= reverseSpd;
		//針が0度以下になるならステートを戻す
		//将来的にここにカメラシェイクを付ける
		if (hourHand.radian < reverseSpd) {
			hourHand.radian = 0;
			hourHand.state = State::normal;
		}
	}

	//長針を常時回転
longHand.radian += 0.5f;

	//-360度超えたら0に戻す
	longHand.radian = fmodf(longHand.radian, 360.0f);
	//-360度超えたら0に戻す
	hourHand.radian = fmodf(hourHand.radian, 360.0f);

	//位置調整件描画用のラジアン宣言
	float radL = longHand.radian - 90;
	float radH = hourHand.radian -90;

	//針の角度で終点座標を計算
	longHand.end.x = (longHand.length * cosf(radL / 180 * PI)) + clock.x;
	longHand.end.y = (longHand.length * sinf(radL / 180 * PI)) + clock.y;
	//針の角度で終点座標を計算
	hourHand.end.x = (hourHand.length * cosf(radH  / 180 * PI)) + clock.x;
	hourHand.end.y = (hourHand.length * sinf(radH  / 180 * PI)) + clock.y;


#pragma endregion

	// --プレイヤークラス更新処理-- //
	player->Update(hourHand, clock);

	// --エネミークラス更新処理-- //
	enemy->Update(hourHand, clock);
}

// --描画処理-- //
void GameScene::Draw() {
	// --プレイヤーの描画処理-- //
	player->Draw();
	enemy->Draw();
	DrawCircle(clock, 0xffffff, false);
	DrawLine(longHand, 4);
	DrawLine(hourHand);
	DrawFormatString(0, 20, 0x00ffff, "Rキー:速度リセット");
	DrawFormatString(0, 40, longHand.color, "longHand(長針)の情報 x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 60, hourHand.color, "hourHand(短針)の情報 x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);

	//目印用０時の針
	DrawLine(clock.x, clock.y, clock.x, clock.y - clock.radius + 16, 0x60ffbf, 6);
}