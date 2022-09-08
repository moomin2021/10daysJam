#include "GameScene.h"
#include "SceneManager.h"
#include "Score.h"
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

bool GameScene::CollisionCtoL(Circle c, Line l, float lineSpd)
{
	//必要変数宣言
	Vector2 vecLine, vecCircle, vecCircle2, vecN, vecNtoC;
	float len;
	float rad = l.radian - 90;

	for (int i = 0; i < (int)lineSpd; i++) {
		//線の終点座標を変更

		l.end.x = (l.length * cosf((rad) / 180 * PI)) + l.start.x;
		l.end.y = (l.length * sinf((rad) / 180 * PI)) + l.start.y;

		vecLine = l.end - l.start;
		vecLine = vecLine.normalize();
		vecCircle = c.pos - l.start;
		vecCircle2 = c.pos - l.end;
		len = vecLine.dot(vecCircle);
		vecN = vecLine * len;
		vecNtoC = vecCircle - vecN;

		if (vecNtoC.length() < c.radius) {
			if (vecLine.dot(vecCircle) * vecLine.dot(vecCircle2) <= 0.0f) {
				return true;
			}
			else if (vecCircle.length() < c.radius || vecCircle2.length() < c.radius) {

				return true;
			}
		}
		else rad--;
	}
	return false;
}

// --コンストラクタ-- //
GameScene::GameScene() : clock{ {640, 480}, 416 },
longHand{ {640, 480}, {640, 0}, clock.radius, 0, 0xFF0000 },
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 0, 0xFF }, levelCircle{ {640, 480}, 8 },
longHandSpeed(0.5f)
{
	// --入力クラスインスタンス取得-- //
	input = Input::GetInstance();

	// --プレイヤークラスインスタンス取得-- //
	player = Player::GetInstance();

	// --コントローラークラスインスタンス取得-- //
	pad = JoyPadInput::GetInstance();
}

// --デストラクタ-- //
GameScene::~GameScene() {
	delete player;
}

// --初期化処理-- //
void GameScene::Initialize() {
	delayMax = 20; 
	spawnInterval = 20;
	spawnDelay = delayMax;
	spawnTimer = spawnInterval;
	level = 1;
	point = 0;
	hourHandSpeed = 1.0f;
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
		hourHand.radian += hourHandSpeed;

		//任意のキーで短針を動かす(デバッグ用)
		//hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
	}//ステートが反転しているなら短針を逆走させる
	else if (hourHand.state == State::Reverse) {
		hourHand.radian -= reverseSpd;
		//短針が長針に追いついたら長針のステートを「反転」に
		if (hourHand.radian < longHand.radian + reverseSpd && hourHand.radian > longHand.radian - reverseSpd) {
			longHand.state = State::Reverse;
			//短針のステートをとめる
			hourHand.state = State::Stop;
		}
	}

	//ステートが通常なら長針は自動回転
	if (longHand.state == State::Normal) {
		longHand.radian += longHandSpeed;
	}//ステートが「反転」なら逆走
	else if (longHand.state == State::Reverse) {
		//速度は短針と等速
		longHand.radian -= reverseSpd;

		//長針の角度が0になったら長針と短針のステートを戻し、角度も初期化
		if (longHand.radian < reverseSpd) {
			longHand.state = State::Normal;
			hourHand.state = State::Normal;
			longHand.radian = 0;
			//	hourHand.radian = 0;
			enemys.clear();
			LevelReset();
			// --スコア加算-- //
			Score::AddScore(1000);

			//シェイク
			camera.SetShakeCount(10);

			//敵のスポーンタイマーもリセット
			spawnDelay = delayMax;
			spawnTimer = spawnInterval;
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
	float radH = hourHand.radian - 90;

	//針の角度で終点座標を計算
	longHand.end.x = (longHand.length * cosf(radL / 180 * PI)) + clock.pos.x;
	longHand.end.y = (longHand.length * sinf(radL / 180 * PI)) + clock.pos.y;
	//針の角度で終点座標を計算
	hourHand.end.x = (hourHand.length * cosf(radH / 180 * PI)) + clock.pos.x;
	hourHand.end.y = (hourHand.length * sinf(radH / 180 * PI)) + clock.pos.y;


#pragma endregion

	// --プレイヤークラス更新処理-- //
	player->Update(hourHand, clock, levelCircle.radius);

	// --エネミーのスポーン処理-- //
	//短針が通常状態なら行う
	if (hourHand.state == State::Normal) {
		EnemySpawn();
	}


	// --エネミークラス更新処理-- //
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Update(hourHand);

		//短針が反転モードなら判定をとる
		if (hourHand.state == State::Reverse) {
			//短針と敵の当たり判定
			if (CollisionCtoL(enemys[i].GetCircle(), hourHand, reverseSpd)) {
				enemys[i].OnCollison();
			}
		}
	}

	//カメラ更新
	//スペースキーでシェイク
	if (input->IsTrigger(KEY_INPUT_SPACE)) {
		camera.SetShakeCount(5);
	}

	camera.CameraShake();
	
	// --プレイヤーとエネミーの当たり判定-- //
	PlayerAndEnemyCol();

	// --レベルの更新処理-- //
	LevelUpdate();

	// --デバック用処理-- //
	levelCircle.radius += input->IsPress(KEY_INPUT_A) - input->IsPress(KEY_INPUT_D);
	levelCircle.radius = Clamp(levelCircle.radius, 300.0f, 8.0f);
	hourHandSpeed += (input->IsTrigger(KEY_INPUT_Z) - input->IsTrigger(KEY_INPUT_C)) * 0.1f;
	longHandSpeed += (input->IsTrigger(KEY_INPUT_I) - input->IsTrigger(KEY_INPUT_P)) * 0.1f;
}

// --描画処理-- //
void GameScene::Draw() {
	// --プレイヤーの描画処理-- //
	player->Draw(camera);

	// --エネミーの描画処理-- //
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Draw(camera);
	}
	
	//描画用座標宣言
	Circle posC;
	Line posL;
	posC = { clock.pos + camera.GetPos(),clock.radius };
	DrawCircle(posC, 0xffffff, false);
	posL.start = {longHand.start + camera.GetPos()};
	posL.end = {longHand.end + camera.GetPos()};
	posL.color = longHand.color;
	DrawLine(posL, 4);
	posL.start = { hourHand.start + camera.GetPos() };
	posL.end = { hourHand.end + camera.GetPos() };
	posL.color = hourHand.color;
	DrawLine(posL);
	posC = { levelCircle.pos + camera.GetPos() };
	DrawCircle(posC, 0xFFFFFF, false);

	//目印用０時の針
	posL.start = { clock.pos + camera.GetPos() };
	posL.end = { clock.pos.x + camera.GetPos().x,clock.pos.y - clock.radius + 16 + camera.GetPos().y };
	posL.color = 0x60ffbf;
	DrawLine(posL, 6);

	// --デバック用処理-- //
	DrawFormatString(0, 80, 0xFFFFFF, "ADキー:レベルサークルの半径変更");
	DrawFormatString(0, 100, 0xFFFFFF, "レベルサークルの半径:%f", levelCircle.radius);
	DrawFormatString(0, 120, 0xFFFFFF, "ZCキー:短針の速度変更");
	DrawFormatString(0, 140, 0xFFFFFF, "短針の速度:%f", hourHandSpeed);
	DrawFormatString(0, 160, longHand.color, "longHand(長針)の情報 x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 180, hourHand.color, "hourHand(短針)の情報 x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
	DrawFormatString(0, 280, 0xFFFFFF, "IPキーで長針の速度を変更");
	DrawFormatString(0, 300, 0xFFFFFF, "長針の速度:%f", longHandSpeed);
	DrawFormatString(0,320, 0xFFFFFF, "カメラシェイク:スペースキー(振動量の調整は未実装)");
	DrawFormatString(0,340, 0xFFFFFF, "エネミーのスポーンまでの残り時間:%d",spawnTimer);
	DrawFormatString(0,360, 0xFFFFFF, "エネミーのスポーン遅延時間:%d",spawnDelay);
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
			enemyLength = Random(levelCircle.radius, hourHand.length);
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
void GameScene::PlayerAndEnemyCol() {
	// --自機と敵の当たり判定を行う-- //
	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionCtoC(player->player, enemys[i].enemy)) {
			enemys.erase(enemys.begin() + i);
			point++;
			Score::AddScore(100);
		}
	}

	// --レベルサークルとエネミーの当たり判定-- //
	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionCtoC(levelCircle, enemys[i].enemy)) {
			enemys.erase(enemys.begin() + i);
		}
	}
}

// --レベル-- //
void GameScene::LevelUpdate() {
	level = (point / 5) + 1;

	//hourHandSpeed = (0.5f * level) + 1.0f;

	//newCircleRadius = level * 8;

	//if (newCircleRadius > levelCircle.radius) levelCircle.radius++;
	//if (newCircleRadius < levelCircle.radius) levelCircle.radius--;
}

// --レベルリセット-- //
void GameScene::LevelReset() {
	level = 1;
	point = 0;
}
