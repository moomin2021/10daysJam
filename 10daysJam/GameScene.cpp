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
	vecAtoB.x = cB.pos.x - cA.pos.x;
	vecAtoB.y = cB.pos.y - cA.pos.y;
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
GameScene::GameScene() : clock{ {640, 480}, 416 },
longHand{ {640, 480}, {640, 0}, clock.radius, 0, 0xFF0000},
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 0, 0xFF }
{
	// --入力クラスインスタンス取得-- //
	input = Input::GetInstance();

	// --プレイヤークラスインスタンス取得-- //
	player = Player::GetInstance();

	pad = JoyPadInput::GetInstance();
}

// --デストラクタ-- //
GameScene::~GameScene() {
	delete player;
}

// --初期化処理-- //
void GameScene::Initialize() {
	delayMax = 1;
	spawnDelay = delayMax;
	spawnInterval = 20;
	spawnTimer = spawnInterval;
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

		//任意のキーで短針を動かす(デバッグ用)
		hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
	}//ステートが反転しているなら短針を逆走させる
	else if (hourHand.state == State::reverse) {
		hourHand.radian -= reverseSpd;
		//短針が長針に追いついたら長針のステートを「反転」に
		if (hourHand.radian < longHand.radian + reverseSpd && hourHand.radian > longHand.radian - reverseSpd){
			longHand.state = State::reverse;
		}
	}

	//ステートが通常なら長針は自動回転
	if (longHand.state == State::normal) {
		longHand.radian += 0.5f;
	}//ステートが「反転」なら逆走
	else if (longHand.state == State::reverse) {
		//速度は短針と等速
		longHand.radian -= reverseSpd;
		
		//長針の角度が0になったら長針と短針のステートを戻し、角度も初期化
		if (longHand.radian < reverseSpd) {
			longHand.state = State::normal;
			hourHand.state = State::normal;
			longHand.radian = 0;
			hourHand.radian = 0;
			enemys.clear();
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
	longHand.end.x = (longHand.length * cosf(radL / 180 * PI)) + clock.pos.x;
	longHand.end.y = (longHand.length * sinf(radL / 180 * PI)) + clock.pos.y;
	//針の角度で終点座標を計算
	hourHand.end.x = (hourHand.length * cosf(radH  / 180 * PI)) + clock.pos.x;
	hourHand.end.y = (hourHand.length * sinf(radH  / 180 * PI)) + clock.pos.y;


#pragma endregion

	// --プレイヤークラス更新処理-- //
	player->Update(hourHand, clock);

	// --エネミークラス更新処理-- //
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Update();
	}

	// --エネミーのスポーン処理-- //
	EnemySpawn();
}

// --描画処理-- //
void GameScene::Draw() {
	// --プレイヤーの描画処理-- //
	player->Draw();
	
	// --エネミーの描画処理-- //
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Draw();
	}

	DrawCircle(clock, 0xffffff, false);
	DrawLine(longHand, 4);
	DrawLine(hourHand);
	DrawFormatString(0, 20, 0x00ffff, "Rキー:速度リセット");
	DrawFormatString(0, 40, longHand.color, "longHand(長針)の情報 x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 60, hourHand.color, "hourHand(短針)の情報 x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);

	//目印用０時の針
	DrawLine(clock.pos.x, clock.pos.y, clock.pos.x, clock.pos.y - clock.radius + 16, 0x60ffbf, 6);
}

// --敵のスポーン処理-- //
void GameScene::EnemySpawn() {
	//スポーンタイマーを減らす
	if (spawnTimer > 0) {
		spawnTimer--;
		//タイマーが0になったらスポーン位置を決める
	}
	else if (spawnTimer == 0) {


		//スポーンタイマーが0になった瞬間のみ位置を決める(短針の位置を参照するため
		if (spawnDelay == delayMax) {
			enemyLength = Random(0.0f, hourHand.length);
			float rad = hourHand.radian - 90;
			enemyPos.x = (enemyLength * cosf(rad / 180 * PI)) + clock.pos.x;
			enemyPos.y = (enemyLength * sinf(rad / 180 * PI)) + clock.pos.y;
			//ディレイタイマーを減らす
			spawnDelay--;
		}//ディレイタイマーが0出ないなら
		else if (spawnDelay > 0) {
			//ディレイタイマーを減らす
			spawnDelay--;
		}//ディレイタイマーが0になったら座標を確定
		else if (spawnDelay == 0) {
			for (int i = 0; i < 10; i++) {
				enemys.push_back({ enemyPos, 8.0f });
				//タイマーをリセット
				spawnTimer = spawnInterval;
				spawnDelay = delayMax;
				break;
			}
		}
	}
}

// --自機と敵の当たり判定処理-- //
//void GameScene::PlayerAndEnemyCol() {
//	// --自機と敵の当たり判定を行う-- //
//	for (int i = 0; i < enemy->enemys.size();i++) {
//		if (CollisionCtoC(player->player, enemy->enemys[i])) {
//			enemy->enemys.erase(enemy->enemys.begin() + i);
//		}
//	}
//}