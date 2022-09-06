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
	if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::Normal) {
		hourHand.state = State::Reverse;
	}

	//ステートが通常なら短針は自動回転
	if (hourHand.state == State::Normal) {
		hourHand.radian += 2.0f;

		hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
	}//ステートが反転しているなら短針を逆走させる
	else if (hourHand.state == State::Reverse) {
		hourHand.radian -= reverseSpd;
		//短針が長針に追いついたら長針のステートを「反転」に、短針は止まる
		if (hourHand.radian < longHand.radian + reverseSpd && hourHand.radian > longHand.radian - reverseSpd){
			longHand.state = State::Reverse;
			hourHand.state = State::Stop;
		}
	}

	//ステートが通常なら長針は自動回転
	if (longHand.state == State::Normal) {
		longHand.radian += 0.5f;
	}//ステートが「反転」なら逆走
	else if (longHand.state == State::Reverse) {
		//速度は短針と等速
		longHand.radian -= reverseSpd * 2;
		
		//長針の角度が0になったら長針と短針のステートを戻し、角度も初期化
		if (longHand.radian < reverseSpd) {
			longHand.state = State::Normal;
			hourHand.state = State::Normal;
			longHand.radian = 0;
			//hourHand.radian = 0;
		}
	}

	//360度超えたら0に戻し、0を下回ったら360加算する
	longHand.radian = fmodf(longHand.radian, 360.0f);
	if (longHand.radian <= 0)longHand.radian += 360.0f;
	//360度超えたら0に戻し、0を下回ったら360加算する
	hourHand.radian = fmodf(hourHand.radian, 360.0f);
	if (hourHand.radian <= 0)hourHand.radian += 360.0f;

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