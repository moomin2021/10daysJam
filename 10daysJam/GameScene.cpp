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

// --インスタンス解放-- 
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

	// --サウンド-- //
	sound = Sound::GetInstance();

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
	hourHandReverseSpeed = 4.0f;
#pragma endregion

#pragma region レベル関係変数の初期化
	// --真ん中のレベルを表記する円-- //
	levelCircle = { {640.0f, 480.0f}, 78.0f };

	// --レベルサークルの新しい半径-- //
	newCircleRadius = 0.0f;

	// --レベル-- //
	level = 0;

	// --経験値-- //
	point = 0;

	// --レベルによって必要な経験値-- //
	int needPointCopy[10] = { 2, 2, 3, 4, 5, 10, 10, 10, 10, 10 };
	for (int i = 0; i < 10; i++) { needPoint[i] = needPointCopy[i]; }
#pragma endregion

#pragma region エフェクト関係変数の初期化
	// --敵の爆発したときの円の大きさ用-- //
	burstCircle = { {0.0f, 0.0f}, 0.0f };
#pragma endregion

#pragma region 画像読み込み
	// --時計や針の描画用画像-- //
	whiteCircleGraph = LoadGraph("Resources/whiteCircle.png");

	// --カウント-- //
	LoadDivGraph("Resources/countNum.png", 3, 3, 1, 102, 135, countNumGraph);

	particleGraph = LoadGraph("Resources/particle.png");
	particleGraph = whiteCircleGraph;

	// --アイテム-- //
	LoadDivGraph("Resources/Item.png", 2, 2, 1, 48, 48, itemGraph);

	// --敵-- //
	LoadDivGraph("Resources/Enemy.png", 2, 2, 1, 48, 48, enemyGraph);

	// --背景-- //
	backGroundGraph = LoadGraph("Resources/backillust.png");

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
	//パーティクルの数とか
	//Circle starC;
	//starLen = hourHand.length + 72;
	//starC.pos = clock.pos;
	//starC.radius = 6;

	//for (int i = 0; i < 5; i++) {
	//	star[i].Initialize(starC, 72 * i, starLen, 32);
	//	star2[i].Initialize(starC, 72 * i + 36, starLen + 108, 32);
	//}

	lineParticleMax = 64;
	for (int i = 0; i < lineParticleMax; i++) {
		Particle newParticle;
		/*Vector2 pos;
		pos.x = Random(hourHand.start.x + levelCircle.radius, hourHand.end.x);
		pos.y = Random(hourHand.start.y + levelCircle.radius, hourHand.end.y);*/
		//newParticle.SetParent(hourHand.start);
		newParticle.SetState(ParticleState::Endress);
		newParticle.Initialize();
		hourHandParticle.push_back(newParticle);
		longHandParticle.push_back(newParticle);
	}

	//オープニングを始める
	isOpening = true;
	nowTime = 0;
	//オープニング用変数の初期化

	//敵のスポーン時間のブレ

	for (int i = 0; i < opEnemyMax; i++) {
		//敵のスポーンフレームをランダムに
		int spawnFrame;
		spawnFrame = 30 + i * 50;
		opSpawnFrame.push_back(spawnFrame);
	}


}

// --更新処理-- //
void GameScene::Update() {
#pragma region 針の座標計算

	//オープニング処理
	if (isOpening) {
		OpeningUpdate();
	}
	else {
		//Lボタンで短針のステートを「反転」に
		if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::Normal && level > 0) {
			hourHand.state = State::Reverse;
		}

		//逆走の速度は短針の速度 * 速度倍率に
		hourHandReverseSpeed = (hourHandSpeed + hourHandlevelSpeed * (level - 1)) *reverseVelocityScale;

		//ステートが通常なら短針は自動回転
		if (hourHand.state == State::Normal) {
			hourHand.radian += hourHandSpeed + hourHandlevelSpeed * (level - 1);

			//任意のキーで短針を動かす(デバッグ用)
			//hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
		}//ステートが反転しているなら短針を逆走させる
		else if (hourHand.state == State::Reverse) {
			hourHand.radian -= hourHandReverseSpeed;
			//短針が長針に追いついたら長針のステートを「反転」に
			if (hourHand.radian < longHand.radian + hourHandReverseSpeed && hourHand.radian > longHand.radian - hourHandReverseSpeed) {
				longHand.state = State::Reverse;
				//短針のステートをとめる
				hourHand.state = State::Stop;

				//はさんだオブジェクトの数で戻す力を増やす
				reverseTime += level * 1.5;
				reverseTime += itemSandwichCount / 2 * level;
				reverseTime += enemySandwichCount * 2 * level;

				//スコアを加算、はさんだ数をリセット
				Score::AddScore(300 * itemSandwichCount);
				Score::AddScore(500 * enemySandwichCount);
				itemSandwichCount = 0;
				enemySandwichCount = 0;

				LevelReset();


				longHandReverseSpeed = hourHandReverseSpeed * reverseVelocityScaleLong;
				//はさんだ瞬間にはさまれている敵を消滅させる
				for (int i = enemys.size() - 1; i >= 0; i--) {
					if (enemys[i].GetState() == State::Reverse) {
						enemys[i].Death();
						//enemys.erase(enemys.begin() + i);
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
				longHand.radian -= longHandReverseSpeed;
				//長針の角度が0になったら長針と短針のステートを戻し、角度も初期化
				if (longHand.radian < hourHandReverseSpeed) {
					longHand.state = State::Normal;
					hourHand.state = State::Normal;
					longHand.radian = 0;
					//	hourHand.radian = 0;
					//ステートがデスでない敵は削除、デスはそのまま
					for (int i = enemys.size() - 1; i >= 0; i--) {
						if (enemys[i].GetState() != State::Death) {
							enemys.erase(enemys.begin() + i);
						}
					}
					LevelReset();
					// --スコア加算-- //
					Score::AddScore(1000);
					//シェイク
					camera.SetShakeCount(10);
					//敵のスポーンタイマーもリセット
					spawnTimer = spawnInterval;
					//衝撃エフェクトを作成
					CreateBreakEffect(clock.pos, 128);
					//レベル変動エフェクトを作成
					LevelUpEfffect(64 * 3);
					
					//戻す力をリセット
					reverseTime = 0;


					//サウンド再生
					sound->PlaySE(SANDSE);

					//敵を5体スポーンさせる
					for (int i = 0; i < 5; i++) {
						EnemySpawn(Random(0.0f, 72.0f) + 72.0f * i);
					}

				}
				//反転速度の減算
				reverseTime--;
			}//戻す力がなくなったらステートをノーマルに戻す
			else if (reverseTime <= 0) {
				longHand.state = State::Normal;
				hourHand.state = State::Normal;
				//敵のスポーンタイマーをリセット
				spawnTimer = spawnInterval;

				//敵を5体スポーンさせる
				for (int i = 0; i < 5; i++) {
					EnemySpawn(Random(0.0f, 72.0f) + 72.0f * i);
				}
			}
		}

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

		// --長針が一周したらリザルト
		if (longHand.radian >= 360.0f) {
			// --シーンを変える-- //
			SceneManager::SetScene(RESULTSCENE);
		}

#pragma endregion

		

#pragma region プレイヤー更新処理
		player->Update(hourHand, clock, levelCircle.radius);
#pragma endregion

#pragma region エネミー関係の処理
		// --エネミーのスポーン処理-- //
		//短針が通常状態なら行う
		if (hourHand.state == State::Normal) {
			//スポーンタイマーを減らす
			if (spawnTimer > 0) {
				spawnTimer--;
				//タイマーが0になったらスポーン位置を決める
			}
			else if (spawnTimer == 0) {

				EnemySpawn(hourHand.radian - 5);
				//タイマーをリセット
				spawnTimer = spawnInterval;
			}
		}

		

		// --エネミークラス更新処理-- //
		for (int i = enemys.size() - 1; i >= 0; i--) {
			Vector2 scorePos = { 1200,60 };
			//DrawCircle({ scorePos,32 }, 0xffffff, true);
			enemys[i].Update(hourHand,scorePos);
			//短針が反転モードなら判定をとる
			if (hourHand.state == State::Reverse) {
				//短針と敵の当たり判定
				if (CollisionCtoL(enemys[i].GetCircle(), hourHand, hourHandReverseSpeed)) {
					//オブジェクトのステートがまだ「反転」でなく、死んでもいないなら当たり判定のコールバック関数を呼び出し、挟んだ数をカウントする
					if (enemys[i].GetState() != State::Reverse && enemys[i].GetState() != State::Death) {
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
			if (longHand.state == State::Normal) {
				//長針と敵の当たり判定
				if (CollisionCtoL(enemys[i].GetCircle(), longHand, longHandSpeed)) {
					//一度もステート変更が行われていないなら
					if (!enemys[i].GetIsChange()) {
						//敵の状態がアイテムなら敵に
						if (enemys[i].GetState() == State::Item) {
							enemys[i].SetState(State::Enemy);
							enemys[i].SetHandle(enemyGraph);
						}//敵ならアイテムに
						else if (enemys[i].GetState() == State::Enemy) {
							enemys[i].SetState(State::Item);
							enemys[i].SetHandle(itemGraph);
						}
						enemys[i].StateChange();
					}

				}

			}

			//爆発円との当たり判定
			if (CollisionCtoC(enemys[i].GetCircle(), burstCircle)) {
				//当たったアイテムを消す
				enemys[i].SetState(State::Delete);
				
			}

			for (int i = burstCircleEffects.size() - 1; i >= 0; i--) {
				//バーストサークルの色を落とす
				burstEffectColorParam[i] -= Random(-5, 15);
				if (burstEffectColorParam[i] <= 0) {
					burstEffectColorParam.erase(burstEffectColorParam.begin() + i);
					burstEffectColor.erase(burstEffectColor.begin() + i);
					burstCircleEffects.erase(burstCircleEffects.begin() + i);
				}
			}

			if (enemys[i].GetState() == State::Delete) {
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

		for (int i = 0; i < 5; i++) {
			star[i].Update(hourHand);
			//star2[i].SetSpd(0.8f);
			star2[i].Update(hourHand);
			//if(star[i].)
		}

		for (int i = 0; i < lineParticleMax; i++) {
			Vector2 pos;
			float len, rad;
			len = Random(levelCircle.radius, hourHand.length);
			rad = hourHand.radian - 90.0f;
			pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
			pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
			hourHandParticle[i].SetParent(pos);
			hourHandParticle[i].SetSpeed(Random(0.0f, 0.2f));
			hourHandParticle[i].SetRadius(Random(3.0f, 6.0f));
			hourHandParticle[i].Update();

			len = Random(levelCircle.radius, longHand.length);
			rad = longHand.radian - 90.0f;
			pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
			pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
			longHandParticle[i].SetParent(pos);
			longHandParticle[i].SetSpeed(Random(0.5f, 2.0f));
			hourHandParticle[i].SetRadius(Random(1.0f, 3.0f));
			longHandParticle[i].SetRadian(Random(rad - 135, rad - 45));
			longHandParticle[i].Update();

		}

		for (int i = levelChangeParticle.size()- 1; i >= 0; i--) {
			Vector2 pos;
			float len, rad;
			len = longHand.length;
			rad = Random(0.0f, 360.0f);
			pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
			pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
			levelChangeParticle[i].SetParent(pos);
			levelChangeParticle[i].SetSpeed(Random(3.0f, 8.0f));
			levelChangeParticle[i].SetRadius(Random(6.0f, 10.0f));
			//levelChangeParticle[i].SetRadian(Random(rad - 60, rad + 60));
			//levelChangeParticle[i].SetRadian(rad);
			levelChangeParticle[i].Update();
			//アクティブじゃなくなったら消す
			if (!levelChangeParticle[i].GetActive()) {
				levelChangeParticle.erase(levelChangeParticle.begin() + i);
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
		if (SceneManager::GetDebugMode() == true) {
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
		}
#pragma endregion
	}
}

// --描画処理-- //
void GameScene::Draw() {
	// --背景描画-- //
	DrawGraph(0, 0, backGroundGraph, true);

	//現在時間を参照してライトアップ
	int brightLongHand = 0;
	brightLongHand = (256.0f / 25.0f) * (nowTime - 175) + 16.0f;
	int brightClock = 0;
	brightClock = (256.0f / 25.0f) * (nowTime - 125) + 16.0f;
	int brightHourHand = 0;
	brightHourHand = (256.0f / 25.0f) * (nowTime - 75) + 16.0f;

#pragma region プレイヤー描画
	player->Draw(camera, brightHourHand);
#pragma endregion

#pragma region エネミー描画
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Draw(camera, particleGraph);
	}

#pragma endregion

#pragma region 時計の外枠の描画
	// --時計の外枠の座標とカメラシェイクの座標足したCircle変数-- //
	Circle clockCircle = { clock.pos + camera.GetPos(), clock.radius };



	SetDrawBlendMode(DX_BLENDMODE_ADD, brightClock);
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

	//針のパーティクルの描画
	SetDrawBlendMode(DX_BLENDMODE_ADD, 256);
	for (int i = 0; i < lineParticleMax; i++) {
		hourHandParticle[i].Draw(camera, PURPLE, particleGraph);
		longHandParticle[i].Draw(camera, EFFECT_GREEN, particleGraph);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);

#pragma region 長針の描画
	// --長針の座標とカメラシェイクの座標足したLine変数-- //
	Line longHandLine;
	longHandLine.start = { longHand.start + camera.GetPos() };
	longHandLine.end = { longHand.end + camera.GetPos() };
	longHandLine.color = longHand.color;



	SetDrawBlendMode(DX_BLENDMODE_ADD, brightLongHand);
	//etDrawBright(119, 28, 28);
	Color c;
	c = HexadecimalColor(GREEN);
	SetDrawBright(c.red, c.green, c.blue);
	// --長針の描画-- //
	for (int i = 0; i < longHand.length * 1.3f; i++) {
		DrawRotaGraph(
			longHandLine.start.x + cosf(Degree2Radian(longHand.radian - 90)) * (levelCircle.radius + i * 0.8f / 1.3f),
			longHandLine.start.y + sinf(Degree2Radian(longHand.radian - 90)) * (levelCircle.radius + i * 0.8f / 1.3f),
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

	SetDrawBlendMode(DX_BLENDMODE_ADD, brightHourHand);
	SetDrawBright(39, 32, 225);

	// --短針の描画-- //
	for (int i = 0; i < longHand.length; i++) {
		DrawRotaGraph(
			hourHandLine.start.x + cosf(Degree2Radian(hourHand.radian - 90)) * (levelCircle.radius + i * 0.8f),
			hourHandLine.start.y + sinf(Degree2Radian(hourHand.radian - 90)) * (levelCircle.radius + i * 0.8f),
			0.5f, 0.0f, whiteCircleGraph, true);
	}



	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
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
	//DrawLine(line, 6);
#pragma endregion

#pragma region 敵の爆発円描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	//DrawCircle(burstCircle, 0xff0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);

	for (int i = 0; i < burstCircleEffects.size(); i++) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, burstEffectColorParam[i]);
		int X1 = burstCircleEffects[i].pos.x;
		int Y1 = burstCircleEffects[i].pos.y;
		int X2 = burstCircleEffects[i].pos.x + burstCircleEffects[i].radiusX;
		int Y2 = burstCircleEffects[i].pos.y + burstCircleEffects[i].radiusY;
		DrawBox(X1, Y1, X2, Y2, burstEffectColor[i], true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, burstEffectColorParam[i]);
	}
#pragma endregion

#pragma region エフェクト描画
	for (int i = 0; i < breakEffects.size(); i++) {
		int graph;
		if (Random(0, 100) > 50)graph = itemGraph[0];
		else graph = enemyGraph[0];
		breakEffects[i].Draw(camera,graph);
	}

	//パーティクルスターの描画
	/*for (int i = 0; i < 5; i++) {
		if (!isOpening) {
			star[i].Draw(camera, PURPLE, particleGraph);
			star2[i].Draw(camera, ORANGE, particleGraph);
		}
	}*/

	//レベル変動エフェクト
	for (int i = 0; i < levelChangeParticle.size(); i++) {
		int graph;
		if (Random(0, 100) > 50)graph = itemGraph[0];
		else graph = enemyGraph[0];
		levelChangeParticle[i].Draw(camera, Random(0, 0xffffff), graph);
	}
#pragma endregion

	//カウントダウンの描画
	//数字
	int countDownBright;
	int graphNum = (nowTime - animationTime) / 50 * (nowTime >= animationTime);	//画像配列の順番が321ならこっち
	if (graphNum > 2)graphNum = 2;					//1,2,3ならこっち
	int graphNumR = 2 - graphNum;

	countDownBright = (256 - ((256.0f / 50.0f) * (nowTime - (animationTime + (graphNum * 50))))) * (nowTime >= animationTime);
	SetDrawBlendMode(DX_BLENDMODE_ADD, countDownBright);
	// --画像描画をここに-- //
	DrawGraphF(589.0f, 412.5f, countNumGraph[graphNum], true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, countDownBright);

	DrawFormatString(1280 / 2 - 20, 960 / 2 - 40, 0xFFFFFF, "%d", level);

#pragma region デバッグ描画
	if (SceneManager::GetDebugMode() == true) {
		DrawFormatString(0, 100, 0xFFFFFF, "ADキー:レベルサークルの半径変更");
		DrawFormatString(0, 120, 0xFFFFFF, "レベルサークルの半径:%f", levelCircle.radius);
		DrawFormatString(0, 140, 0xFFFFFF, "ZCキー:短針の速度変更");
		DrawFormatString(0, 160, 0xFFFFFF, "IPキーで長針の速度を変更");
		DrawFormatString(0, 180, 0xFFFFFF, "カメラシェイク:スペースキー(振動量の調整は未実装)");
		DrawFormatString(0, 200, longHand.color, "longHand(長針)の情報 x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
		DrawFormatString(0, 220, hourHand.color, "hourHand(短針)の情報 x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
		DrawFormatString(0, 240, 0xFFFFFF, "短針の速度:%f", hourHandSpeed + hourHandlevelSpeed * (level - 1));
		DrawFormatString(0, 260, 0xFFFFFF, "長針の速度:%f", longHandSpeed);
		DrawFormatString(0, 280, 0xFFFFFF, "逆走の速度(短針):%f", hourHandReverseSpeed);
		DrawFormatString(0, 300, 0xFFFFFF, "エネミーのスポーンまでの残り時間:%d", spawnTimer);
		DrawFormatString(0, 340, 0xFFFFFF, "敵の総数:%d", enemys.size());
		DrawFormatString(0, 320, 0xFFFFFF, "FPS");
		DrawFormatString(0, 360, 0xFFFFFF, "アイテムを挟んだ数:%d", itemSandwichCount);
	
		DrawFormatString(0, 400, 0xFFFFFF, "敵を挟んだ数:%d", enemySandwichCount);
		DrawFormatString(0, 420, 0xFFFFFF, "point:%d", point);

		/*SetFontSize(80);*/
		/*SetFontSize(16);*/
	}
#pragma endregion

	//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	//for (int i = 0; i < 3; i++) {
	//	DrawGraph(0, 800, enemyGraph[0], true);
	//}
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// --敵のスポーン処理-- //
void GameScene::EnemySpawn(float radian) {

	enemyLength = Random(levelCircle.radius + 8.0f, hourHand.length);
	float rad = radian - 90;
	enemyPos.x = (enemyLength * cosf(rad / 180 * PI)) + clock.pos.x;
	enemyPos.x -= (10.0f * cosf((rad + 90) / 180 * PI));
	enemyPos.y = (enemyLength * sinf(rad / 180 * PI)) + clock.pos.y;
	enemyPos.y -= (10.0f * sinf((rad + 90) / 180 * PI));
	Enemy newEnemy;
	//Circle newPos = {enemyPos,8.0f}
	newEnemy.SetObj({ {enemyPos} , 8.0f });
	newEnemy.Initialize();
	enemys.push_back(newEnemy);
	if (Random(0, 100) <= enemySpawnRate) {
		//5%の確率で敵としてスポーン
		enemys.back().SetState(State::Enemy);
		enemys.back().SetHandle(enemyGraph);
	}
	else {//それ以外の95%でアイテムとしてスポーン
		enemys.back().SetState(State::Item);
		enemys.back().SetHandle(itemGraph);
	}
}

// --自機と敵の当たり判定処理-- //
void GameScene::Collision() {
	// --自機と敵の当たり判定を行う-- //
	for (int i = enemys.size() - 1; i >= 0; i--) {
		if (CollisionCtoC(player->player, enemys[i].obj)) {
			//敵のステートがItemなら消滅
			if (enemys[i].GetState() == State::Item) {
				enemys[i].Death();
				//enemys.erase(enemys.begin() + i);
				point++;
				Score::AddScore(100);
				AddReversePower(1);

				//サウンド再生
				sound->PlaySE(GETITEMSE);

			}//敵のステートがenemyならレベルを減らして消滅させる
			else if (enemys[i].GetState() == State::Enemy) {
				//レベルを下げて、爆発サークルを出現
				if (level > 0) {
					level--;
					point = 0;
				}
				burstCircle.pos = enemys[i].GetCircle().pos + camera.GetPos();
				burstCircle.radius = 96.0f;
				CreateBurstEffect(burstCircle, 128);
				//敵を消滅
				enemys.erase(enemys.begin() + i);
				//逆走する力をリセット
				reverseTime = 0;

				//サウンド再生
				sound->PlaySE(HITENEMYSE);
			}
		}
	}

	// --レベルサークルとエネミーの当たり判定-- //
	//for (int i = 0; i < enemys.size(); i++) {
	//	if (CollisionCtoC(levelCircle, enemys[i].obj)) {
	//		//敵のステートが死亡でないなら(死亡演出中でないなら)
	//		if (enemys[i].GetState() != State::Death) {
	//			enemys.erase(enemys.begin() + i);
	//		}
	//	}
	//}
}

// --レベル-- //
void GameScene::LevelUpdate() {
#pragma region 経験値によってレベルを変える処理
	// --現在のレベルの必要経験値が手に入ったらレベルを上げる-- //
	if (needPoint[level] == point && level < 5) {
		level++;
		point = 0;
		LevelUpEfffect(96);

		//サウンド再生
		sound->PlaySE(LEVELUPSE);
	}

	//逆走速度の速度倍率
	reverseVelocityScale = 2.0f;		//短針	
	reverseVelocityScaleLong = 2.0f;	//長針


	//レベルで敵の出現率を調整
	switch (level)
	{
	case 0:
		enemySpawnRate = 0.0f;
		spawnInterval = 120;
		break;
	case 1:
		enemySpawnRate = 15.0f;
		spawnInterval = 50;
		reverseVelocityScale = 3.5f;
		break;
	case 2:
		enemySpawnRate = 19.0f;
		spawnInterval = 40;
		reverseVelocityScale = 3.5f;
		break;
	case 3:
		enemySpawnRate = 23.0f;
		spawnInterval = 30;
		reverseVelocityScale = 3.0f;
		break;
	case 4:
		enemySpawnRate = 26.0f;
		spawnInterval = 30;
		reverseVelocityScale = 2.5f;
		break;
	case 5:
		enemySpawnRate = 28.0f;
		spawnInterval = 25;
		reverseVelocityScale = 2.5f;
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
	level = 0;
	point = 0;
}

void GameScene::CreateBreakEffect(Vector2 pos, int effectParam) {

	//作成するエフェクトの数だけ動的配列に入れる
	for (int i = 0; i < effectParam; i++) {
		BreakEffect newEffect;
		newEffect.Initialize(pos);
		breakEffects.push_back(newEffect);
	}
}

void GameScene::AddReversePower(int power) {
	//加算
	reverseTime += power;
}

void GameScene::OpeningUpdate() {
	if (!isOpening) {
		return;
	}
	//時間を加算
	nowTime++;

	if (nowTime <= animationTime) {

		//1秒で一回転するように回転速度を変更
		hourHandReverseSpeed = 360.0f / 250.0f;

		hourHand.radian -= hourHandReverseSpeed;
		float radH = hourHand.radian - 90;
		//針の角度で終点座標を計算
		hourHand.end.x = (hourHand.length * cosf(radH / 180 * PI)) + clock.pos.x;
		hourHand.end.y = (hourHand.length * sinf(radH / 180 * PI)) + clock.pos.y;

	}
	//経過時間が指定のフレームに来たらスポーン
	for (int i = 0; i < opSpawnFrame.size(); i++) {
		if (nowTime == opSpawnFrame[i]) {
			EnemySpawn(hourHand.radian - 5.0f);
		}
	}

	player->Update(hourHand, clock, levelCircle.radius);

	for (int i = enemys.size() - 1; i >= 0; i--) {
		enemys[i].Update(hourHand,{0,0});
	}
	if (nowTime == openingTime) {
		isOpening = false;
	}
}

void GameScene::LevelUpEfffect(int effectNum)
{
	for (int i = 0; i < effectNum; i++) {
		Particle newpaticle;
		Vector2 pos;
		float len, rad;
		len = longHand.length;
		rad = Random(0.0f, 360.0f);
		pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
		pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
		newpaticle.SetParent(pos);
		newpaticle.SetSpeed(Random(3.0f, 8.0f));
		newpaticle.SetRadius(Random(8.0f, 12.0f));
		newpaticle.SetRadian(Random(rad - 60, rad + 60));
		newpaticle.SetRadian(rad);
		newpaticle.Initialize(true);
		levelChangeParticle.push_back(newpaticle);
	}
}

void GameScene::CreateBurstEffect(Circle burstRange, int effectNum) {
	for (int i = 0; i < effectNum; i++) {
		Box newbox;
		float rad = Random(0.0f, 360.0f);
		float len = Random(0.0f, burstCircle.radius);
		float lenX ;
		float lenY ;

		while (true) {
			lenX = Random(0.0f, burstRange.radius / 3);
			lenY = Random(0.0f, burstRange.radius / 3);
			newbox.pos.x = len * cosf(rad / 180 * PI) + burstCircle.pos.x;
			newbox.pos.y = len * sinf(rad / 180 * PI) + burstCircle.pos.y;
			//エフェクトの左上座標に応じて半径をマイナスにする
			if (burstCircle.pos.x < newbox.pos.x) lenX = -lenX;
			if (burstCircle.pos.x < newbox.pos.x) lenY = -lenY;
			newbox.radiusX = lenX;
			newbox.radiusY = lenY;

			//座標+半径がサークルを出なければ座標確定
			if (newbox.pos.x + lenX <= burstCircle.pos.x + burstCircle.radius &&
				newbox.pos.x - lenX >= burstCircle.pos.x - burstCircle.radius &&
				newbox.pos.y + lenY <= burstCircle.pos.y + burstCircle.radius &&
				newbox.pos.y - lenY >= burstCircle.pos.y - burstCircle.radius) {
				break;
			}
		}
		burstCircleEffects.push_back(newbox);
		int newcolor = 256;
		burstEffectColorParam.push_back(newcolor);
		Color c;
		c = HexadecimalColor(RED);
		c.red +=   Random(-16, 16);
		c.blue +=  Random(-16, 16);
		c.green += Random(-16, 16);
		newcolor = ColorHexadecimal(c);
		burstEffectColor.push_back(newcolor);
	}

}
