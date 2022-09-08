#include "GameScene.h"
#include "SceneManager.h"
#include "Score.h"
using namespace Util;
using namespace std;

// --インスタンスにNULLを代入-- //
GameScene* GameScene::myInstance = nullptr;

// --インスタンス読み込み-- //
GameScene* GameScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new GameScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --インスタンス解放-- //
void GameScene::Relese() {
	// --インスタンスが無かったら何もせずに終了する-- //
	if (myInstance == nullptr) return;

	// --インスタンス解放-- //
	delete myInstance;
	myInstance = nullptr;
}

// --コンストラクタ-- //
GameScene::GameScene() {
#pragma region インスタンス読み込み
	// --キーボードクラス-- //
	input = Input::GetInstance();

	// -コントローラークラス-- //
	pad = JoyPadInput::GetInstance();

	// --プレイヤークラス-- //
	player = Player::GetInstance();
#pragma endregion

#pragma region エネミーのスポーン関係変数の初期化
	// --敵のスポーン位置を確定してからスポーンさせるまでの時間-- //
	delayMax = 20;

	// --次に敵が発生するまでの間隔-- //
	spawnInterval = 20;

	// --敵のスポーン遅延の残り時間-- //
	spawnDelay = delayMax;

	// --敵の発生タイマー-- //
	spawnTimer = spawnInterval;

	// --敵が短針上のどこでスポーンするかの変数-- //
	enemyLength = 0.0f;

	// --確定した敵のスポーン位置を保存する用変数-- //
	enemyPos = { 0.0f, 0.0f };
#pragma endregion

#pragma region 時計関係変数の初期化
	// --時計-- //
	clock = { {640.0f, 480.0f}, 416.0f };

	// --長針-- //
	longHand = { {640.0f, 480.0f}, {640.0f, 0.0f}, clock.radius, 0.0f, 0xFF0000 };

	// --長針の速度-- //
	longHandSpeed = 0.1f;

	// --短針-- //
	hourHand = { {640.0f, 480.0f}, {640.0f, 32.0f}, clock.radius - 32.0f, 0, 0xFF };

	// --短針の速度-- //
	hourHandSpeed = 0.8f;

	// --レベルによる短針の速度の上がり幅-- //
	hourHandlevelSpeed = 0.5f;

	// --短針が逆回りするときの速度-- //
	reverseSpeed = 4.0f;
#pragma endregion

#pragma region レベル関係変数の初期化
	// --真ん中のレベルを表記する円-- //
	levelCircle = { {640.0f, 480.0f}, 78.0f };

	// --レベルサークルの新しい半径-- //
	newCircleRadius = 0.0f;

	// --レベル-- //
	level = 1;

	// --経験値-- //
	point = 0;

	// --レベルによって必要な経験値-- //
	int needPointCopy[10] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
	for (int i = 0; i < 10; i++) { needPoint[i] = needPointCopy[i]; }
#pragma endregion

#pragma region エフェクト関係変数の初期化
	// --敵の爆発したときの円の大きさ用-- //
	burstCircle = { {0.0f, 0.0f}, 0.0f };
#pragma endregion

#pragma region 画像読み込み
	// --時計や針の描画用画像-- //
	whiteCircleGraph = LoadGraph("Resouces/whiteCircle.png");
#pragma endregion
}

// --デストラクタ-- //
GameScene::~GameScene() {
#pragma region クラスのインスタンス解放
	player->Relese();
#pragma endregion
}

// --初期化処理-- //
void GameScene::Initialize() {

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
		hourHand.radian += hourHandSpeed + hourHandlevelSpeed * (level - 1);

		//任意のキーで短針を動かす(デバッグ用)
		//hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
	}//ステートが反転しているなら短針を逆走させる
	else if (hourHand.state == State::Reverse) {
		hourHand.radian -= reverseSpeed;
		//短針が長針に追いついたら長針のステートを「反転」に
		if (hourHand.radian < longHand.radian + reverseSpeed && hourHand.radian > longHand.radian - reverseSpeed) {
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
		longHand.radian -= reverseSpeed;

		//長針の角度が0になったら長針と短針のステートを戻し、角度も初期化
		if (longHand.radian < reverseSpeed) {
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

			//衝撃エフェクトを作成
			CreateBreakEffect(clock.pos, 128);
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

#pragma region プレイヤー更新処理
	player->Update(hourHand, clock, levelCircle.radius);
#pragma endregion

#pragma region エネミー関係の処理
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
			if (CollisionCtoL(enemys[i].GetCircle(), hourHand, reverseSpeed)) {
				enemys[i].OnCollison();
			}
		}

		//爆発円との当たり判定
		if (CollisionCtoC(enemys[i].GetCircle(), burstCircle)) {
			//当たったアイテムを消す
			enemys.erase(enemys.begin() + i);
		}
	}
#pragma endregion

#pragma region エフェクト処理
	//　--爆発円の座標リセット-- //
	burstCircle = { {0.0f,0.0f}, 0.0f };

	//エフェクト更新処理
	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Update();
		//生存フラグがfalseなら該当要素を消す
		if (!breakEffects[i].GetAllive()) {
			breakEffects.erase(breakEffects.begin() + i);
		}
	}
#pragma endregion

#pragma region カメラシェイク処理
	camera.CameraShake();
#pragma endregion

#pragma region ゲームシーンの当たり判定処理
	Collision();
#pragma endregion

#pragma region レベルの更新処理
	LevelUpdate();
#pragma endregion

#pragma region デバッグ用処理
	// --レベルサークルの半径変更-- //
	levelCircle.radius += input->IsPress(KEY_INPUT_A) - input->IsPress(KEY_INPUT_D);

	// --レベルサークルの半径制限-- //
	levelCircle.radius = Clamp(levelCircle.radius, 300.0f, 8.0f);

	// --短針の速度変更-- //
	hourHandSpeed += (input->IsTrigger(KEY_INPUT_Z) - input->IsTrigger(KEY_INPUT_C)) * 0.1f;

	// --長針の速度変更-- //
	longHandSpeed += (input->IsTrigger(KEY_INPUT_I) - input->IsTrigger(KEY_INPUT_P)) * 0.1f;

	// --SPACEキーを押すと画面がシェイクする-- //
	if (input->IsTrigger(KEY_INPUT_SPACE)) { camera.SetShakeCount(5); }
#pragma endregion
}

// --描画処理-- //
void GameScene::Draw() {
#pragma region プレイヤー描画
	player->Draw(camera);
#pragma endregion

#pragma region エネミー描画
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Draw(camera);
	}
	
	//描画用座標宣言
	Circle posC;
	Line posL;
	posC = { clock.pos + camera.GetPos(),clock.radius };
	//DrawCircle(posC, 0xffffff, false);
	posL.start = {longHand.start + camera.GetPos()};
	posL.end = {longHand.end + camera.GetPos()};
	posL.color = longHand.color;
	DrawLine(posL, 4);
	posL.start = { hourHand.start + camera.GetPos() };
	posL.end = { hourHand.end + camera.GetPos() };
	posL.color = hourHand.color;
	DrawLine(posL);
	posC = { levelCircle.pos + camera.GetPos(), levelCircle.radius };
	DrawCircle(posC, 0xFFFFFF, false);

	posC = { burstCircle.pos + camera.GetPos(),burstCircle.radius };
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawCircle(posC, 0xff0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Draw(camera);
	}
#pragma endregion

#pragma region 時計の外枠の描画
	// --時計の外枠の座標とカメラシェイクの座標足したCircle変数-- //
	Circle clockCircle = { clock.pos + camera.GetPos(), clock.radius };

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(119, 28, 28);

	// --時計の外枠の描画-- //
	for (int i = 0; i < 1440; i++) {
		DrawGraphF(
			clockCircle.pos.x + cosf(Degree2Radian(i * 0.25f)) * clockCircle.radius - 16,
			clockCircle.pos.y + sinf(Degree2Radian(i * 0.25f)) * clockCircle.radius - 16,
			whiteCircleGraph, true);
	}

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

#pragma region 長針の描画
	// --長針の座標とカメラシェイクの座標足したLine変数-- //
	Line longHandLine;
	longHandLine.start = { longHand.start + camera.GetPos() };
	longHandLine.end = { longHand.end + camera.GetPos() };
	longHandLine.color = longHand.color;

	// --長針の描画-- //
	DrawLine(longHandLine, 4);
#pragma endregion

#pragma region 短針の描画
	// --短針の座標とカメラシェイクの座標足したLine変数-- //
	Line hourHandLine;
	hourHandLine.start = { hourHand.start + camera.GetPos() };
	hourHandLine.end = { hourHand.end + camera.GetPos() };
	hourHandLine.color = hourHand.color;

	// --短針の描画-- //
	DrawLine(hourHandLine);
#pragma endregion

#pragma region レベルサークルの描画
	// --レベルサークルの座標とカメラシェイクの座標足したCircle変数-- //
	Circle circle;
	circle = { levelCircle.pos + camera.GetPos(), levelCircle.radius };

	// --レベルサークルの描画-- //
	DrawCircle(circle, 0xFFFFFF, false);
#pragma endregion

#pragma region 目印用0時の針の描画
	// --0時の針の座標とカメラシェイクの座標足したCircle変数-- //
	Line line;
	line.start = { clock.pos + camera.GetPos() };
	line.end = { clock.pos.x + camera.GetPos().x, clock.pos.y - clock.radius + 16 + camera.GetPos().y };
	line.color = 0x60FFBF;

	// --0時の針描画-- //
	DrawLine(line, 6);
#pragma endregion

#pragma region エフェクト描画
	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Draw(camera);
	}
#pragma endregion

#pragma region デバッグ描画
	DrawFormatString(0, 80, 0xFFFFFF, "ADキー:レベルサークルの半径変更");
	DrawFormatString(0, 100, 0xFFFFFF, "レベルサークルの半径:%f", levelCircle.radius);
	DrawFormatString(0, 120, 0xFFFFFF, "ZCキー:短針の速度変更");
	DrawFormatString(0, 140, 0xFFFFFF, "短針の速度:%f", hourHandSpeed);
	DrawFormatString(0, 160, longHand.color, "longHand(長針)の情報 x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 180, hourHand.color, "hourHand(短針)の情報 x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
	DrawFormatString(0, 280, 0xFFFFFF, "IPキーで長針の速度を変更");
	DrawFormatString(0, 300, 0xFFFFFF, "長針の速度:%f", longHandSpeed);
	DrawFormatString(0, 320, 0xFFFFFF, "カメラシェイク:スペースキー(振動量の調整は未実装)");
	DrawFormatString(0, 340, 0xFFFFFF, "エネミーのスポーンまでの残り時間:%d", spawnTimer);
	DrawFormatString(0, 360, 0xFFFFFF, "エネミーのスポーン遅延時間:%d", spawnDelay);
	/*SetFontSize(80);*/
	DrawFormatString(1280 / 2 - 20, 960 / 2 - 40, 0xFFFFFF, "%d", level);
	/*SetFontSize(16);*/
#pragma endregion
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
				enemys.push_back({ enemyPos, 8.0f });
				if (Random(0, 100) <= enemySpawnRate) {
					//5%の確率で敵としてスポーン
					enemys.back().SetState(State::Enemy);
				}
				else {//それ以外の95%でアイテムとしてスポーン
					enemys.back().SetState(State::Item);
				}
				//タイマーをリセット
				spawnTimer = spawnInterval;
				spawnDelay = delayMax;
				
			
		}
	}
}

// --自機と敵の当たり判定処理-- //
void GameScene::Collision() {
	// --自機と敵の当たり判定を行う-- //
	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionCtoC(player->player, enemys[i].enemy)) {
			//敵のステートがItemなら消滅
			if (enemys[i].GetState() == State::Item) {
			enemys.erase(enemys.begin() + i);
			point++;
			Score::AddScore(100);
			}//敵のステートがenemyならレベルを減らして消滅させる
			else if (enemys[i].GetState() == State::Enemy) {
				//レベルを下げて、爆発サークルを出現
				if (level > 1) {
					level--;
				}
				burstCircle.pos = enemys[i].GetCircle().pos;
				burstCircle.radius = 96.0f;

				enemys.erase(enemys.begin() + i);
			}
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
#pragma region 経験値によってレベルを変える処理
	// --現在のレベルの必要経験値が手に入ったらレベルを上げる-- //
	if (needPoint[level - 1] == point) {
		level++;
		point = 0;
	}
#pragma endregion
}

// --レベルリセット-- //
void GameScene::LevelReset() {
	level = 1;
	point = 0;
}

void GameScene::CreateBreakEffect(Vector2 pos, int effectParam) {

	//作成するエフェクトの数だけ動的配列に入れる
	for (int i = 0; i < effectParam; i++) {
		BreakEffect newEffect{};
		newEffect.Initialize(pos);
		breakEffects.push_back(newEffect);
	}
}