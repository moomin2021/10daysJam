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
longHand{ {640, 480}, {640, 0}, clock.radius, 180, 0xFF0000},
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 180, 0xFF }
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

	for (int i = 0; i < 10; i++) {
		enemy[i].radius = 8;
	}
}

// --更新処理-- //
void GameScene::Update() {



#pragma region 針の座標計算

	//長針を常時回転
	longHand.radian -= 0.5f;
	//-360度超えたら0に戻す
	longHand.radian = fmodf(longHand.radian, 360.0f);
	//針の角度で終点座標を計算
	longHand.end.x = (longHand.length * sinf(longHand.radian / 180 * PI)) + clock.x;
	longHand.end.y = (longHand.length * cosf(longHand.radian / 180 * PI)) + clock.y;

	//長針を常時回転
	//hourHand.radian -= 2.0f;
	hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;

	//-360度超えたら0に戻す
	hourHand.radian = fmodf(hourHand.radian, 360.0f);
	//針の角度で終点座標を計算
	hourHand.end.x = (hourHand.length * sinf(hourHand.radian / 180 * PI)) + clock.x;
	hourHand.end.y = (hourHand.length * cosf(hourHand.radian / 180 * PI)) + clock.y;


#pragma endregion

	// --プレイヤークラス更新処理-- //
	player->Update(hourHand, clock);

#pragma region 敵の発生制御

	//スポーンタイマーを減らす
	if (spawnTimer > 0) {
		spawnTimer--;
		//タイマーが0になったらスポーン位置を決める
	}
	else if (spawnTimer == 0) {


		//スポーンタイマーが0になった瞬間のみ位置を決める(短針の位置を参照するため
		if (spawnDelay == delayMax) {
			enemyLength = Random(0.0f, hourHand.length);
			enemyPos.x = (enemyLength * sinf(hourHand.radian / 180 * PI)) + clock.x;
			enemyPos.y = (enemyLength * cosf(hourHand.radian / 180 * PI)) + clock.y;
			//ディレイタイマーを減らす
			spawnDelay--;
		}//ディレイタイマーが0出ないなら
		else if (spawnDelay > 0) {
			//ディレイタイマーを減らす
			spawnDelay--;
		}//ディレイタイマーが0になったら座標を確定
		else if (spawnDelay == 0) {
			for (int i = 0; i < 10; i++) {
				enemy[i].x = enemyPos.x;
				enemy[i].y = enemyPos.y;
				//タイマーをリセット
				spawnTimer = spawnInterval;
				//spawnDelay = delayMax;
				break;
			}
		}
	}
#pragma endregion

#pragma region 自機と敵の当たり判定(今のところ円と円の判定)
	if (CollisionCtoC(player->GetPlayer(), enemy[0])) {
		DrawFormatString(500, 500, 0xff00ff, "衝突");
	}
#pragma endregion
}

// --描画処理-- //
void GameScene::Draw() {
	// --プレイヤーの描画処理-- //
	player->Draw();
	DrawCircle(clock, 0xffffff, false);
	DrawLine(longHand, 4);
	DrawLine(hourHand);
	DrawFormatString(0, 20, 0x00ffff, "Rキー:速度リセット");
	DrawFormatString(0, 40, longHand.color, "longHand(長針)の情報 x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 60, hourHand.color, "hourHand(短針)の情報 x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
	for (int i = 0; i < 10; i++) {
		DrawCircle(enemy[i], 0xffff00, true);
	}
}