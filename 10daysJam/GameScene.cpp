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

	// --次に敵が発生するまでの間隔-- //
	spawnInterval = 20;

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
	whiteCircleGraph = LoadGraph("Resources/whiteCircle.png");
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
	star.start = clock.pos;
	star.radian = 0;
	star.length = hourHand.length + 96;
	star.end = { star.start.x + star.length,star.start.y + star.length };

	//位置用のラジアン
	float radStar = star.radian - 90;
	//座標計算
	star.end.x = (star.length * cosf(radStar / 180 * PI)) + star.start.x;
	star.end.y = (star.length * sinf(radStar / 180 * PI)) + star.start.y;

	//パーティクルの数とか
	maxStarparticle = 32;
	for (int i = 0; i< maxStarparticle; i++) {
		Particle newParticle;
		newParticle.SetParent(star.end);
		newParticle.Initialize();
		starParticles.push_back(newParticle);
	}
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

			//はさんだオブジェクトの数で戻す力を増やす
			reverseTime += level;
			reverseTime += itemSandwichCount / 2 * level;
			reverseTime += enemySandwichCount * 2 * level;
			//スコアを加算、はさんだ数をリセット
			Score::AddScore(300 * itemSandwichCount);
			Score::AddScore(500 * enemySandwichCount);
			itemSandwichCount = 0;
			enemySandwichCount = 0;

			//はさんだ瞬間にはさまれている敵を消滅させる
			for (int i = enemys.size()-1; i >=0; i--) {
				if (enemys[i].GetState() == State::Reverse) {
					enemys.erase(enemys.begin() + i);
				}
			}
		}
	}

	//ステートが通常なら長針は自動回転
	if (longHand.state == State::Normal) {
		longHand.radian += longHandSpeed;
	}//ステートが「反転」かつ、反転する力がまだ残っているなら逆走
	else if (longHand.state == State::Reverse) {
		if (reverseTime > 0) {
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
				spawnTimer = spawnInterval;
				//衝撃エフェクトを作成
				CreateBreakEffect(clock.pos, 128);
				//戻す力をリセット
				reverseTime = 0;
			}
			//反転速度の減算
			reverseTime--;
		}//戻す力がなくなったらステートをノーマルに戻す
		else if (reverseTime <= 0) {
			longHand.state = State::Normal;
			hourHand.state = State::Normal;
			//敵のスポーンタイマーをリセット
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


	if (star.state == State::Normal) {
		star.radian += 0.4f;
	}

	//角度が上限、下限を超えたら戻す
	star.radian = fmodf(star.radian, 360.f);
	if (star.radian <= 0)star.radian += 360.0f;
	//位置用のラジアン
	float radStar = star.radian - 90;
	//座標計算
	star.end.x = (star.length * cosf(radStar / 180 * PI)) + star.start.x;
	star.end.y = (star.length * sinf(radStar / 180 * PI)) + star.start.y;

	//パーティクルの更新
	for (int i = 0; i < starParticles.size(); i++) {
		starParticles[i].SetParent(star.end);
		starParticles[i].Update();
	}


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
	for (int i = enemys.size() - 1; i >= 0; i--) {
		enemys[i].Update(hourHand);

		//短針が反転モードなら判定をとる
		if (hourHand.state == State::Reverse) {
			//短針と敵の当たり判定
			if (CollisionCtoL(enemys[i].GetCircle(), hourHand, reverseSpeed)) {
				//オブジェクトのステートがまだ「反転」でないなら当たり判定のコールバック関数を呼び出し、挟んだ数をカウントする
				if (enemys[i].GetState() != State::Reverse) {
					if (enemys[i].GetState() == State::Item) {
						itemSandwichCount++;
					}
					else if (enemys[i].GetState() == State::Enemy) {
						enemySandwichCount++;
					}

					enemys[i].OnCollison();
				}
			}
		}

		//長針がノーマルモードなら判定をとる
	//	if (longHand.state == State::Normal) {
			//長針と敵の当たり判定
		if (CollisionCtoL(enemys[i].GetCircle(), longHand, longHandSpeed)) {
			//一度もステート変更が行われていないなら
			if (!enemys[i].GetIsChange()) {
				//敵の状態がアイテムなら敵に
				if (enemys[i].GetState() == State::Item) {
					enemys[i].SetState(State::Enemy);
				}//敵ならアイテムに
				else if (enemys[i].GetState() == State::Enemy) {
					enemys[i].SetState(State::Item);
				}
				enemys[i].StateChange();
			}

		}

		//}

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

	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Draw(camera);
	}
#pragma endregion

#pragma region 時計の外枠の描画
	// --時計の外枠の座標とカメラシェイクの座標足したCircle変数-- //
	Circle clockCircle = { clock.pos + camera.GetPos(), clock.radius };

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(255, 255, 255);

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

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(119, 28, 28);

	// --長針の描画-- //
	for (int i = levelCircle.radius; i < longHand.length; i++) {
		DrawRotaGraph(
			longHandLine.start.x + cosf(Degree2Radian(longHand.radian - 90)) * (i),
			longHandLine.start.y + sinf(Degree2Radian(longHand.radian - 90)) * (i),
			0.5f, 0.0f, whiteCircleGraph, true);
	}

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

#pragma region 短針の描画
	// --短針の座標とカメラシェイクの座標足したLine変数-- //
	Line hourHandLine;
	hourHandLine.start = { hourHand.start + camera.GetPos() };
	hourHandLine.end = { hourHand.end + camera.GetPos() };
	hourHandLine.color = hourHand.color;

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(39, 32, 225);

	// --短針の描画-- //
	for (int i = levelCircle.radius; i < longHand.length; i++) {
		DrawRotaGraph(
			hourHandLine.start.x + cosf(Degree2Radian(hourHand.radian - 90)) * (i),
			hourHandLine.start.y + sinf(Degree2Radian(hourHand.radian - 90)) * (i),
			0.5f, 0.0f, whiteCircleGraph, true);
	}

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

	SetDrawBlendMode(DX_BLENDMODE_ADD, 256);
	for (int i = 0; i < starParticles.size(); i++) {
		starParticles[i].Draw(camera);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//パーティクルスターの描画
	Circle starC;
	starC = { star.end + camera.GetPos(),10 };
	DrawCircle(starC, 0xffffff, true);
	

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

#pragma region 敵の爆発円描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawCircle(burstCircle, 0xff0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);
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
	DrawFormatString(0, 420, 0xFFFFFF, "敵を挟んだ数:%d", enemySandwichCount);
	DrawFormatString(0, 400, 0xFFFFFF, "アイテムを挟んだ数:%d", itemSandwichCount);
	DrawFormatString(0, 400, 0xFFFFFF, "アイテム:%d", itemSandwichCount);
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
		enemyLength = Random(levelCircle.radius, hourHand.length);
		float rad = hourHand.radian - 90;
		enemyPos.x = (enemyLength * cosf(rad / 180 * PI)) + clock.pos.x;
		enemyPos.x -= (10.0f * cosf((rad + 90) / 180 * PI));
		enemyPos.y = (enemyLength * sinf(rad / 180 * PI)) + clock.pos.y;
		enemyPos.y -= (10.0f * sinf((rad + 90) / 180 * PI));
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
	}

		
	
}

// --自機と敵の当たり判定処理-- //
void GameScene::Collision() {
	// --自機と敵の当たり判定を行う-- //
	for (int i = enemys.size() - 1; i >= 0; i--) {
		if (CollisionCtoC(player->player, enemys[i].enemy)) {
			//敵のステートがItemなら消滅
			if (enemys[i].GetState() == State::Item) {
				enemys.erase(enemys.begin() + i);
				point++;
				Score::AddScore(100);
				AddReversePower(1);
			}//敵のステートがenemyならレベルを減らして消滅させる
			else if (enemys[i].GetState() == State::Enemy) {
				//レベルを下げて、爆発サークルを出現
				if (level > 1) {
					level--;
				}
				burstCircle.pos = enemys[i].GetCircle().pos + camera.GetPos();
				burstCircle.radius = 96.0f;
				//敵を消滅
				enemys.erase(enemys.begin() + i);
				//逆走する力をリセット
				reverseTime = 0;
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

	//レベルで敵の出現率を調整
	switch (level)
	{
	case 1:
		enemySpawnRate = 15.0f;
		spawnInterval = 100;
		break;
	case 2:
		enemySpawnRate = 19.0f;
		break;
	case 3:
		enemySpawnRate = 23.0f;
		break;
	case 4:
		enemySpawnRate = 26.0f;
		break;
	case 5:
		enemySpawnRate = 28.0f;
		break;
	case 6:
		enemySpawnRate = 29.0f;
		break;
	case 7:
		enemySpawnRate = 30.0f;
		break;
	case 8:
		enemySpawnRate = 31.0f;
		break;
	case 9:
		enemySpawnRate = 32.0f;
		break;
	case 10:
		enemySpawnRate = 33.5f;
		break;
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

void GameScene::AddReversePower(int power) {
	//加算
	reverseTime += power;
}