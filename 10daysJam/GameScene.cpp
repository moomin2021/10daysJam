#include "GameScene.h"
#include "SceneManager.h"
#include "Score.h"
using namespace Util;
using namespace std;

// --インスタンスにNULLを代入-- //
GameScene* GameScene::myInstance = nullptr;

bool GameScene::isTutorialSkip = false;

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

	// --長針の速度の追加値-- //
	addHandSpeed = 0.01f;

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

	//UI
	LoadDivGraph("Resources/controller_button.png", 3, 3, 1, 82, 82, ButtonGraph);
	LoadDivGraph("Resources/playUI.png", 4, 4, 1, 190, 190, gameUIGraph);
	LoadDivGraph("Resources/playUIBoard.png", 2, 2, 1, 234, 234, gameUIBoardGraph);

	//チュートリアル関係
	tutorialTextGraph[0] = LoadGraph("Resources/tutorial_move.png");
	tutorialTextGraph[1] = LoadGraph("Resources/tutorial_enemy.png");
	tutorialTextGraph[2] = LoadGraph("Resources/tutorial_return.png");
	LoadDivGraph("Resources/gamerule.png", 2, 2, 1, 344, 72, gameRuleGraph);
	LoadDivGraph("Resources/tutorialBoard.png", 2, 2, 1, 382, 112, tutorialBoardGraph);
	LoadDivGraph("Resources/skipUI.png", 3, 3, 1, 227, 54, skipGraph);

	successGraph = LoadGraph("Resources/success.png");

	//反転ボタン
	LoadDivGraph("Resources/returnUI.png", 2, 2, 1, 58, 58, returnButton);
	returnButton[0] = LoadGraph("Resources/LB.png");

	// --レベルサークル-- //
	LoadDivGraph("Resources/levelCircle.png", 2, 2, 1, 160, 160, levelCircleGraph);

	// --レベル表記-- //
	LoadDivGraph("Resources/levelNumbers.png", 6, 6, 1, 160, 160, levelGraph);

	// --時計の枠-- //
	clockGraph = LoadGraph("Resources/clock.png");

	//リタック演出
	LoadDivGraph("Resources/titleRogo.png", 2, 2, 1, 572, 572, retuckGraph);

	//挟んだ演出
	LoadDivGraph("Resources/value.png", 3, 3, 1, 212, 46, sandwichEffectGraph);

	tutorialFontGraph = LoadGraph("Resources/tutorial.png");

	finishGraph = LoadGraph("Resources/gameFinish.png");

#pragma endregion

	// --シーンを切り替えるまでの時間-- //
	Time = 120;
	Timer = 0;
	isSceneChange = false;
}

// --デストラクタ-- //
GameScene::~GameScene() {
#pragma region クラスのインスタンス解放
	player->Relese();
#pragma endregion
}

// --初期化処理-- //
void GameScene::Initialize() {
	// --アイテム・敵削除-- //
	enemys.clear();

	// --エフェクト削除-- //
	breakEffects.clear();

	// --短針、長針からでるパーティクル削除-- //
	hourHandParticle.clear();
	longHandParticle.clear();

	// --敵の爆発したときの円の大きさ用削除-- //
	burstCircleEffects.clear();
	burstEffectColorParam.clear();
	burstEffectColor.clear();

	// --プレイヤー-- //
	player->Initialize();

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

	// --長針の速度の追加値-- //
	addHandSpeed = 0.03f;

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
	Timer = 0;
	isSceneChange = false;

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

	if (isTutorialSkip == true) {
		isTutorial = true;
		isTutorialClear = true;
		level = 0;
		sceneChangeTime = 75;
		sceneChangeTimer = sceneChangeTime;
	}
	else {
		isTutorial = true;
		isTutorialClear = false;
		level = 1;
		tutorialStep = 0;
		sceneChangeTime = 75;
		sceneChangeTimer = sceneChangeTime;
		for (int i = 0; i < 3; i++) {
			enemySpawnRate = 0;
			EnemySpawn(Random(0.0f, 36.0f) + 36.0f + 108.0f * i);
		}
	}

	//敵のスポーン時間のブレ
	opSpawnFrame.clear();
	for (int i = 0; i < opEnemyMax; i++) {
		//敵のスポーンフレームをランダムに
		int spawnFrame;
		spawnFrame = 30 + i * 50;
		opSpawnFrame.push_back(spawnFrame);
	}

	graphRad = 0;
}

// --更新処理-- //
void GameScene::Update() {

	if (isSceneChange == false) {

#pragma region 針の座標計算

		//チュートリアル処理
		if (isTutorial) {
			UpdateTutorial();
		}
		//オープニング処理
		else if (isOpening) {
			OpeningUpdate();
		}
		else {
			//Lボタンで短針のステートを「反転」に
			if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::Normal && level > 0) {
				hourHand.state = State::Reverse;
			}

			//逆走の速度は短針の速度 * 速度倍率に
			hourHandReverseSpeed = (hourHandSpeed + hourHandlevelSpeed * (level - 1)) * reverseVelocityScale;

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

					// --長針の速度を変更-- //
					longHandSpeed += addHandSpeed;

					// --短針の速度を変更-- //
					hourHandSpeed += addHandSpeed * 2;

					//はさんだオブジェクトの数で戻す力を増やす
					reverseTime += level * 3;
					reverseTime += ((enemySandwichCount + itemSandwichCount) / 2);

					//スコアを加算、はさんだ数をリセット
					int sandwichCount = itemSandwichCount + enemySandwichCount;
					int multiSand = 0;
					if (sandwichCount <= 10)
					{
						multiSand = 1;

					}
					if (sandwichCount >= 11 && sandwichCount <= 20)
					{
						multiSand = 2;
					}
					if (sandwichCount >= 21 && sandwichCount <= 30)
					{
						multiSand = 4;
						sandwichValue = GOOD;
						sandwichEffectTimer = 25;
						//座標計算
						sandwichEffectPos.x = (hourHand.length / 2.0f) * cosf((hourHand.radian - 45) / 180 * PI) + clock.pos.x;
						sandwichEffectPos.y = (hourHand.length / 2.0f) * sinf((hourHand.radian - 45) / 180 * PI) + clock.pos.y;
					}
					if (sandwichCount >= 31 && sandwichCount <= 40)
					{
						multiSand = 6;
						sandwichValue = GREAT;
						sandwichEffectTimer = 25;
						sandwichEffectPos.x = (hourHand.length / 2.0f) * cosf((hourHand.radian - 45) / 180 * PI) + clock.pos.x;
						sandwichEffectPos.y = (hourHand.length / 2.0f) * sinf((hourHand.radian - 45) / 180 * PI) + clock.pos.y;
					}
					if (sandwichCount >= 50)
					{
						multiSand = 8;
						sandwichValue = EXCELLENT;
						sandwichEffectTimer = 25;
						sandwichEffectPos.x = (hourHand.length / 2.0f) * cosf((hourHand.radian - 45) / 180 * PI) + clock.pos.x;
						sandwichEffectPos.y = (hourHand.length / 2.0f) * sinf((hourHand.radian - 45) / 180 * PI) + clock.pos.y;
					}

					Score::AddScore(100 * itemSandwichCount * multiSand);
					Score::AddScore(500 * enemySandwichCount * multiSand);
					itemSandwichCount = 0;
					enemySandwichCount = 0;

					//長針の逆走速度を計算
					longHandReverseSpeed = hourHandReverseSpeed * reverseVelocityScaleLong;
					//レベルリセット
					LevelReset();



					//はさんだ瞬間にはさまれている敵を消滅させる
					for (int i = enemys.size() - 1; i >= 0; i--) {
						if (enemys[i].GetState() == State::Reverse) {
							enemys[i].Death();
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
					//長針の角度が0になったら長針と短針のステートを戻し、角度も初期化(長針のみ)
					if (longHand.radian < hourHandReverseSpeed) {
						longHand.state = State::Normal;
						hourHand.state = State::Normal;
						longHand.radian = 0;
						//ステートがデスでない敵は削除、デスはそのまま
						for (int i = enemys.size() - 1; i >= 0; i--) {
							if (enemys[i].GetState() != State::Death) {
								enemys.erase(enemys.begin() + i);
							}
						}
						//レベルリセット
						LevelReset();
						// --スコア加算-- //
						Score::AddScore(1000);
						//シェイク
						camera.SetShakeCount(10);
						//敵のスポーンタイマーもリセット
						spawnTimer = spawnInterval;
						//衝撃エフェクトを作成
						CreateBreakEffect(clock.pos, 128);
						//レベルアップエフェクトを作成(綺麗なので)
						LevelUpEfffect(64 * 3);
						//タイトルロゴの描画時間リセット
						retuckEffectTimer = 30;
						//戻す力をリセット
						reverseTime = 0;
						//サウンド再生
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
				isSceneChange = true;
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
				enemys[i].Update(hourHand, scorePos);
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

			for (int i = levelChangeParticle.size() - 1; i >= 0; i--) {
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

			//タイトルロゴ演出の時間減らす
			if (retuckEffectTimer > 0) {
				retuckEffectTimer--;
			}

			//挟んだエフェクトの時間を減らす
			if (sandwichEffectTimer > 0) {
				sandwichEffectTimer--;
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

		graphRad += 4.0f;
		if (graphRad > 360.0f) {
			graphRad -= 360.0f;
		}


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

				// --Sキーを押すとスコアが増える-- //
				if (input->IsTrigger(KEY_INPUT_S)) Score::AddScore(10000);
			}
#pragma endregion
		}
	}

	if (isSceneChange == true) {
		Timer++;
		if (Timer >= Time) {
			// --シーンを変える-- //
			SceneManager::SetScene(RESULTSCENE);
		}
	}
}

// --描画処理-- //
void GameScene::Draw() {
	if (isTutorial) {
		DrawTutorial();
	}
	else {

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
		Color color = HexadecimalColor(LIGHTBLUE);
		SetDrawBright(color.red, color.green, color.blue);
		for (int i = 0; i < 20; i++) {
			DrawRotaGraph(640 + camera.GetPos().x, 480 + camera.GetPos().y, 1.0f, 0.0f, clockGraph, true);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

		//針のパーティクルの描画
		SetDrawBlendMode(DX_BLENDMODE_ADD, (256) * (!isOpening));
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

#pragma region 12時に針を描画
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightLongHand);
		color = HexadecimalColor(GREEN);
		SetDrawBright(color.red, color.green, color.blue);
		Line line;
		line.start = { Vector2(640.0f, 480.0f) + camera.GetPos() };
		line.end = { Vector2(640.0f, 480.0f + longHand.length) + camera.GetPos() };
		line.color = hourHand.color;

		// --針の描画-- //
		for (int i = 0; i < longHand.length * 0.5f; i++) {
			DrawRotaGraph(
				hourHandLine.start.x + cosf(Degree2Radian(-90)) * (levelCircle.radius + i * 1.6f),
				hourHandLine.start.y + sinf(Degree2Radian(-90)) * (levelCircle.radius + i * 1.6f),
				0.5f, 0.0f, whiteCircleGraph, true);
		}

		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion





#pragma region レベルサークルの描画
		// -- レベルサークル描画-- //
		DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelCircleGraph[1], true);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		color = HexadecimalColor(LIGHTBLUE);
		SetDrawBright(color.red, color.green, color.blue);
		for (int i = 0; i < 5; i++) {
			DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelCircleGraph[0], true);
			// --レベルの描画-- //
			if (isOpening == false) DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelGraph[level], true);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

#pragma region 目印用0時の針の描画
		// --0時の針の座標とカメラシェイクの座標足したCircle変数-- //
		line;
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
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		for (int i = 0; i < breakEffects.size(); i++) {
			int graph;
			if (Random(0, 100) > 50)graph = itemGraph[0];
			else graph = enemyGraph[0];
			breakEffects[i].Draw(camera, graph);
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
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		//挟んだ時のエフェクト
		if (sandwichEffectTimer > 0) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, (256.0f / 25.0f) * sandwichEffectTimer);
			if (sandwichValue == GOOD) {
				SetDrawBright2(GREEN);
				for (int i = 0; i < 10; i++) {
					DrawRotaGraph(sandwichEffectPos.x, sandwichEffectPos.y, 1, 0, sandwichEffectGraph[2], true);
				}
			}//緑
			else if (sandwichValue == GREAT) {
				SetDrawBright2(ORANGE);
				for (int i = 0; i < 10; i++) {
					DrawRotaGraph(sandwichEffectPos.x, sandwichEffectPos.y, 1, 0, sandwichEffectGraph[1], true);
				}//橙
			}
			else if (sandwichValue == EXCELLENT) {
				SetDrawBright2(YELLOW);
				for (int i = 0; i < 10; i++) {
					DrawRotaGraph(sandwichEffectPos.x, sandwichEffectPos.y, 1, 0, sandwichEffectGraph[0], true);
				}	//黄色
			}
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

		//Xボタンはレベルが１以上の時のみ描画
		SetDrawBlendMode(DX_BLENDMODE_ADD, sinf(graphRad/180 * PI) * 64 + 128);
		if (level > 0) {
			float rad, len, radius;
			Vector2 pos;
			radius = 16;
			rad = hourHand.radian - 90 - 5;
			len = hourHand.length - 16;
			//pos = player->GetPlayer().pos;
			pos.x = len * cosf(rad / 180 * PI) + clock.pos.x;
			pos.y = len * sinf(rad / 180 * PI) + clock.pos.y;
			c = HexadecimalColor(LIGHTBLUE);
			SetDrawBright(c.red, c.green, c.blue);
			for (int i = 0; i < 10; i++) {
				DrawExtendGraph(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, returnButton[0], true);
			}
			//pos = player->GetPlayer().pos;

			len = hourHand.length - 44;
			pos.x = len * cosf(rad / 180 * PI) + clock.pos.x;
			pos.y = len * sinf(rad / 180 * PI) + clock.pos.y;
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(pos.x, pos.y, (32.0f / 58.0f), (hourHand.radian - 90) / 180 * PI, returnButton[1], true);
			}
		}

		if (!isOpening) {
			//右下の操作UI描画

			int posx = 1280 - 234;
			int posy = 960 - 234;
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawGraph(posx, posy, gameUIBoardGraph[1], true);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			SetDrawBright2(RED);
			for (int i = 0; i < 10; i++) {
				DrawGraph(posx, posy, gameUIBoardGraph[0], true);
			}
			posx = 1280 - 190 - 22;
			posy = 960 - 190 - 22;
			SetDrawBright2(LIGHTBLUE);
			for (int i = 0; i < 10; i++) {
				DrawGraph(posx, posy, gameUIGraph[0], true);
			}
			SetDrawBright2(0xffffff);
			for (int i = 0; i < 10; i++) {
				DrawGraph(posx, posy, gameUIGraph[1], true);
			}
			SetDrawBright2(GREEN);
			for (int i = 0; i < 14; i++) {
				DrawGraph(posx, posy, gameUIGraph[2], true);
			}
			SetDrawBright2(RED);
			for (int i = 0; i < 10; i++) {
				DrawGraph(posx, posy, gameUIGraph[3], true);
			}

			posx = 1280 - 234;
			posy = 960 - 234;
		}

		//針が0になった時の演出
		if (retuckEffectTimer > 0) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, (256.0f / 25.0f) * retuckEffectTimer);
			SetDrawBright2(PURPLE);
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(clock.pos.x, clock.pos.y, 1.0f, 0, retuckGraph[0], true);
			}
			SetDrawBright2(GREEN);
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(clock.pos.x, clock.pos.y, 1.0f, 0, retuckGraph[1], true);
			}
		}

	
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightLongHand);
		DrawGraph(0, 0, tutorialBoardGraph[1], true);
		SetDrawBright2(RED);
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightLongHand);
		//SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawGraph(0, 0, tutorialBoardGraph[0], true);
		}

		SetDrawBright2(EFFECT_GREEN);
		for (int i = 0; i < 10; i++) {
			DrawGraph(16, 16, gameRuleGraph[0], true);
		}

		SetDrawBright2(LIGHTBLUE);
		for (int i = 0; i < 10; i++) {
			DrawGraph(16, 16, gameRuleGraph[1], true);
		}

		SetDrawBright2(0xffffff);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		color = HexadecimalColor(PURPLE);
		SetDrawBright(color.red, color.green, color.blue);
		if (isSceneChange == true) {
			for (int i = 0; i < 5; i++) {
				DrawRotaGraph(640.0f, 480.0f, 1.0f, 0.0f, finishGraph, true);
			}
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
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
			DrawFormatString(0, 300, 0xFFFFFF, "逆走時間:%f", reverseTime);
			DrawFormatString(0, 340, 0xFFFFFF, "敵の総数:%d", enemys.size());
			DrawFormatString(0, 320, 0xFFFFFF, "FPS");
			DrawFormatString(0, 360, 0xFFFFFF, "アイテムを挟んだ数:%d", itemSandwichCount);

			DrawFormatString(0, 400, 0xFFFFFF, "敵を挟んだ数:%d", enemySandwichCount);
			DrawFormatString(0, 420, 0xFFFFFF, "point:%d", point);
			DrawFormatString(0, 440, 0xFFFFFF, "挟んだ時間:%d", sandwichEffectTimer);

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

	if (Random(0, 100) < enemySpawnRate) {
		//5%の確率で敵としてスポーン
		newEnemy.SetState(State::Enemy);
		newEnemy.SetHandle(enemyGraph);
	}
	else {//それ以外の95%でアイテムとしてスポーン
		newEnemy.SetState(State::Item);
		newEnemy.SetHandle(itemGraph);
	}
	newEnemy.Initialize();
	enemys.push_back(newEnemy);
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
	//チュートリアル中は必要経験値固定
	if (isTutorial) {
		if (tutorialStep == 0) {
			enemySpawnRate = 0;
		}
		if (point == 3) {
			level++;
			point = 0;
			LevelUpEfffect(96);
			//サウンド再生
			sound->PlaySE(LEVELUPSE);
			//チュートリアルのステップを進める
			tutorialStep++;
			//敵のスポーン率を100%にして敵を大量にスポーン
			enemySpawnRate = 100;
			for (int i = 0; i < 16; i++) {
				EnemySpawn(Random(205, 215));
			}
		}

	}
	else {

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

	}
	//レベルで敵の出現率を調整
	switch (level)
	{
	case 0:
		enemySpawnRate = 0.0f;
		spawnInterval = 100;
		break;
	case 1:
		//チュートリアル中は敵が湧かないように
		if (isTutorial)enemySpawnRate = 0.0f;
		else enemySpawnRate = 15.0f;

		spawnInterval = 45;
		reverseVelocityScale = 3.5f;
		reverseVelocityScaleLong = 1.5f;
		break;
	case 2:
		enemySpawnRate = 19.0f;
		spawnInterval = 32;
		reverseVelocityScale = 3.5f;
		reverseVelocityScaleLong = 1.5f;
		break;
	case 3:
		enemySpawnRate = 23.0f;
		spawnInterval = 24;
		reverseVelocityScale = 3.0f;
		reverseVelocityScaleLong = 1.2f;
		break;
	case 4:
		enemySpawnRate = 26.0f;
		spawnInterval = 20;
		reverseVelocityScale = 2.5f;
		reverseVelocityScaleLong = 1.2f;
		break;
	case 5:
		enemySpawnRate = 28.0f;
		spawnInterval = 15;
		reverseVelocityScale = 2.5f;
		reverseVelocityScaleLong = 1.2f;
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
		enemys[i].Update(hourHand, { 0,0 });
	}
	if (nowTime == openingTime) {
		isOpening = false;
		retuckEffectTimer = 30;
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
		float lenX;
		float lenY;

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
		c.red += Random(-16, 16);
		c.blue += Random(-16, 16);
		c.green += Random(-16, 16);
		newcolor = ColorHexadecimal(c);
		burstEffectColor.push_back(newcolor);
	}

}

void GameScene::UpdateTutorial() {

	//チュートリアルがクリアされているなら
	if (isTutorialClear) {
		//シーン遷移タイマーを減らす
		sceneChangeTimer--;
		//敵を消す
		enemys.clear();
		LevelReset();
		if (sceneChangeTimer < 24) {
			longHand.radian = 0;
			hourHand.radian = 0;
			if (sceneChangeTimer <= 0) {
				isOpening = true;
				nowTime = 0;
				isTutorial = false;
			}
		}

	}

	//画像用ラジアン処理
	graphRad += 4;
	if (graphRad >= 360.0f) {
		graphRad -= 360.0f;
	}

	//スタートボタンでチュートリアルクリア
	if (pad->GetButton(PAD_INPUT_8)) {
		isTutorialClear = true;
	}

	//Lボタンで短針のステートを「反転」に(チュートリアルのステップが最後なら)
	if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::Normal && level > 0) {
		if (tutorialStep == 2)hourHand.state = State::Reverse;
	}

	//逆走の速度は短針の速度 * 速度倍率に
	hourHandReverseSpeed = (hourHandSpeed + hourHandlevelSpeed * (level - 1)) * reverseVelocityScale;

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
			reverseTime = 200;

			itemSandwichCount = 0;
			enemySandwichCount = 0;

			//長針の逆走速度を計算
			longHandReverseSpeed = hourHandReverseSpeed * reverseVelocityScaleLong;
			//レベルリセット
			LevelReset();

			//はさんだ瞬間にはさまれている敵を消滅させる
			for (int i = enemys.size() - 1; i >= 0; i--) {
				if (enemys[i].GetState() == State::Reverse) {
					enemys[i].Death();
				}
			}
		}
	}

	if (tutorialStep == 2) {
		//ステートが通常なら長針は自動回転
		if (longHand.state == State::Normal) {
			longHand.radian += longHandSpeed;
		}//ステートが「反転」かつ、反転する力がまだ残っているなら逆走
		else if (longHand.state == State::Reverse) {
			if (reverseTime > 0) {
				//速度は短針と等速
				longHand.radian -= longHandReverseSpeed;
				//長針の角度が0になったら長針と短針のステートを戻し、角度も初期化(長針のみ)
				if (longHand.radian < hourHandReverseSpeed) {
					longHand.state = State::Normal;
					hourHand.state = State::Normal;
					longHand.radian = 0;
					//ステートがデスでない敵は削除、デスはそのまま
					for (int i = enemys.size() - 1; i >= 0; i--) {
						if (enemys[i].GetState() != State::Death) {
							enemys.erase(enemys.begin() + i);
						}
					}
					//レベルリセット
					LevelReset();
					//シェイク
					camera.SetShakeCount(10);
					//敵のスポーンタイマーもリセット
					spawnTimer = spawnInterval;
					//衝撃エフェクトを作成
					CreateBreakEffect(clock.pos, 128);
					//レベルアップエフェクトを作成(綺麗なので)
					LevelUpEfffect(64 * 3);
					//戻す力をリセット
					reverseTime = 0;
					//サウンド再生
					sound->PlaySE(SANDSE);
					//チュートリアルをクリアに
					isTutorialClear = true;
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

	// --長針が一周したら敵を3体スポーンさせる
	if (longHand.radian >= 360.0f) {
		longHand.radian -= 360.0f;
		//前にいた敵はすべて消す
		enemys.clear();
		//自機レベルリセット
		LevelReset();
		for (int i = 0; i < 3; i++) {
			EnemySpawn(Random(0.0f, 36.0f) + 36.0f + 108.0f * i);
		}
	}

	//自機更新
	player->Update(hourHand, clock, levelCircle.radius);

	//エネミー関係
	//エネミー更新
	for (int i = enemys.size() - 1; i >= 0; i--) {

		Vector2 scorePos = { 1200,60 };
		enemys[i].Update(hourHand, scorePos);
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



		//チュートリアルが最終ステップにきてたら敵を全削除
		if (tutorialStep == 2) {
			enemys[i].SetState(State::Delete);
			level = 1;
		}

		if (enemys[i].GetState() == State::Delete) {
			enemys.erase(enemys.begin() + i);
		}
	}

	//エフェクト関係
	//　--爆発円の座標リセット-- //
	burstCircle = { {0.0f,0.0f}, 0.0f };

	for (int i = burstCircleEffects.size() - 1; i >= 0; i--) {
		//バーストサークルの色を落とす
		burstEffectColorParam[i] -= Random(-5, 15);
		if (burstEffectColorParam[i] <= 0) {
			burstEffectColorParam.erase(burstEffectColorParam.begin() + i);
			burstEffectColor.erase(burstEffectColor.begin() + i);
			burstCircleEffects.erase(burstCircleEffects.begin() + i);
		}
	}

	//エフェクト更新処理
	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Update();
		//生存フラグがfalseなら該当要素を消す
		if (!breakEffects[i].GetAllive()) {
			breakEffects.erase(breakEffects.begin() + i);
		}
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

	for (int i = levelChangeParticle.size() - 1; i >= 0; i--) {
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

	//カメラ処理
	camera.CameraShake();

	//当たり判定(本編のゲームからスコア加算をなくしたりしたver)
	for (int i = enemys.size() - 1; i >= 0; i--) {
		if (CollisionCtoC(player->player, enemys[i].obj)) {
			//敵のステートがItemなら消滅
			if (enemys[i].GetState() == State::Item) {
				enemys[i].Death();
				//enemys.erase(enemys.begin() + i);
				point++;
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

				//チュートリアルを進めて、敵をすべて消す
				if (tutorialStep == 1) {
					tutorialStep++;
				}
			}
		}
	}

	//レベル更新処理
	LevelUpdate();


}

void GameScene::DrawTutorial() {
	// --背景描画-- //
	DrawGraph(0, 0, backGroundGraph, true);
	//画像の加算値はチュートリアル終了時に暗くする
	int brightParam = (256.0f / 25.0f) * (sceneChangeTimer - 25);

	if (!isTutorialSkip) {
		player->Draw(camera, brightParam);

		for (int i = 0; i < enemys.size(); i++) {
			enemys[i].Draw(camera, particleGraph);
		}

		// --時計の外枠の座標とカメラシェイクの座標足したCircle変数-- //
		Circle clockCircle = { clock.pos + camera.GetPos(), clock.radius };
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		Color color = HexadecimalColor(LIGHTBLUE);
		SetDrawBright(color.red, color.green, color.blue);

		// --時計の外枠の描画-- //
		for (int i = 0; i < 20; i++) {
			DrawRotaGraph(640 + camera.GetPos().x, 480 + camera.GetPos().y, 1.0f, 0.0f, clockGraph, true);
		}
		SetDrawBright(255, 255, 255);

		//針のパーティクルの描画
		for (int i = 0; i < lineParticleMax; i++) {
			hourHandParticle[i].Draw(camera, PURPLE, particleGraph);
			longHandParticle[i].Draw(camera, EFFECT_GREEN, particleGraph);
		}

		// --長針の座標とカメラシェイクの座標足したLine変数-- //
		Line longHandLine;
		longHandLine.start = { longHand.start + camera.GetPos() };
		longHandLine.end = { longHand.end + camera.GetPos() };
		longHandLine.color = longHand.color;

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

#pragma region 12時に針を描画
		color = HexadecimalColor(GREEN);
		SetDrawBright(color.red, color.green, color.blue);
		Line line;
		line.start = { Vector2(640.0f, 480.0f) + camera.GetPos() };
		line.end = { Vector2(640.0f, 480.0f + longHand.length) + camera.GetPos() };
		line.color = hourHand.color;

		// --針の描画-- //
		for (int i = 0; i < longHand.length * 0.5f; i++) {
			DrawRotaGraph(
				line.start.x + cosf(Degree2Radian(-90)) * (levelCircle.radius + i * 1.6f),
				line.start.y + sinf(Degree2Radian(-90)) * (levelCircle.radius + i * 1.6f),
				0.5f, 0.0f, whiteCircleGraph, true);
		}

		SetDrawBright(255, 255, 255);
#pragma endregion

		// --短針の座標とカメラシェイクの座標足したLine変数-- //
		Line hourHandLine;
		hourHandLine.start = { hourHand.start + camera.GetPos() };
		hourHandLine.end = { hourHand.end + camera.GetPos() };
		hourHandLine.color = hourHand.color;

		SetDrawBright(39, 32, 225);

		// --短針の描画-- //
		for (int i = 0; i < longHand.length; i++) {
			DrawRotaGraph(
				hourHandLine.start.x + cosf(Degree2Radian(hourHand.radian - 90)) * (levelCircle.radius + i * 0.8f),
				hourHandLine.start.y + sinf(Degree2Radian(hourHand.radian - 90)) * (levelCircle.radius + i * 0.8f),
				0.5f, 0.0f, whiteCircleGraph, true);
		}

		SetDrawBright(255, 255, 255);

		for (int i = 0; i < burstCircleEffects.size(); i++) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, burstEffectColorParam[i]);
			int X1 = burstCircleEffects[i].pos.x;
			int Y1 = burstCircleEffects[i].pos.y;
			int X2 = burstCircleEffects[i].pos.x + burstCircleEffects[i].radiusX;
			int Y2 = burstCircleEffects[i].pos.y + burstCircleEffects[i].radiusY;
			DrawBox(X1, Y1, X2, Y2, burstEffectColor[i], true);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, burstEffectColorParam[i]);
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);

		for (int i = 0; i < breakEffects.size(); i++) {
			int graph;
			if (Random(0, 100) > 50)graph = itemGraph[0];
			else graph = enemyGraph[0];
			breakEffects[i].Draw(camera, graph);
		}

		for (int i = 0; i < levelChangeParticle.size(); i++) {
			int graph;
			if (Random(0, 100) > 50)graph = itemGraph[0];
			else graph = enemyGraph[0];
			levelChangeParticle[i].Draw(camera, Random(0, 0xffffff), graph);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, brightParam);

		//UI描画
	//	SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		//スコアボード
		int posx = 1280 - 384;
		int posy = 2;
		c = HexadecimalColor(RED);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightParam);
		DrawGraph(posx, posy, tutorialBoardGraph[1], true);
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawGraph(posx, posy, tutorialBoardGraph[0], true);
		}

		//チュートリアルステップで画像を描画
		c = HexadecimalColor(LIGHTBLUE);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			c = HexadecimalColor(LIGHTBLUE);
			SetDrawBright(c.red, c.green, c.blue);
			DrawGraph(posx + 16, posy + 16, tutorialTextGraph[tutorialStep], true);
			//ステップ1でボタン描画
			if (tutorialStep == 0) {
				c = HexadecimalColor(GREEN);
				SetDrawBright(c.red, c.green, c.blue);
				DrawExtendGraph(posx + 48, posy + 20, posx + 84, posy + 56, ButtonGraph[1], true);
				c = HexadecimalColor(RED);
				SetDrawBright(c.red, c.green, c.blue);
				DrawExtendGraph(posx + 120, posy + 20, posx + 156, posy + 56, ButtonGraph[2], true);
				SetDrawBright(255, 255, 255);
			}
		}

		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightParam);
		DrawGraph(0, 0, tutorialBoardGraph[1], true);
		SetDrawBright2(RED);
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawGraph(0, 0, tutorialBoardGraph[0], true);
		}

		SetDrawBright2(EFFECT_GREEN);
		for (int i = 0; i < 10; i++) {
			DrawGraph(16, 16, gameRuleGraph[0], true);
		}

		SetDrawBright2(LIGHTBLUE);
		for (int i = 0; i < 10; i++) {
			DrawGraph(16, 16, gameRuleGraph[1], true);
		}


		Vector2 pos;
		float len = 48;
		pos = player->GetPlayer().pos;
		float rad = hourHand.radian - 90;
		pos.x -= len * cosf(rad / 180 * PI);
		pos.y -= len * sinf(rad / 180 * PI);
		float radius = 16;

		c = HexadecimalColor(RED);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawExtendGraph(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, ButtonGraph[2], true);
		}

		pos = player->GetPlayer().pos;
		pos.x += len * cosf(rad / 180 * PI);
		pos.y += len * sinf(rad / 180 * PI);
		c = HexadecimalColor(GREEN);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawExtendGraph(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, ButtonGraph[1], true);
		}

		//Xボタンは最後のチュートリアルのみ描画
		if (tutorialStep == 2) {
			if (!isTutorialClear) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, sinf(graphRad / 180 * PI) * 64 + 128);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
			}
			rad = hourHand.radian - 90 - 5;
			len = hourHand.length - 16;
			//pos = player->GetPlayer().pos;
			pos.x = len * cosf(rad / 180 * PI) + clock.pos.x;
			pos.y = len * sinf(rad / 180 * PI) + clock.pos.y;
			c = HexadecimalColor(LIGHTBLUE);
			SetDrawBright(c.red, c.green, c.blue);
			for (int i = 0; i < 10; i++) {
				DrawExtendGraph(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, returnButton[0], true);
			}
			//pos = player->GetPlayer().pos;

			len = hourHand.length - 44;
			pos.x = len * cosf(rad / 180 * PI) + clock.pos.x;
			pos.y = len * sinf(rad / 180 * PI) + clock.pos.y;
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(pos.x, pos.y, (32.0f / 58.0f), (hourHand.radian - 90) / 180 * PI, returnButton[1], true);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD,255);
		//チュートリアルクリア時の描画
		if (isTutorialClear) {
			SetDrawBright2(YELLOW);
			Vector2 pos;
			pos = clock.pos + camera.GetPos();
			pos.y -= 200;
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(pos.x, pos.y, 1, 0, successGraph, true);
			}
		}

		//スキップボタンUIの追加
		//Vector2 pos;
		pos.x = 1280 - 227;
		pos.y = 960 - 54;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightParam);
		DrawGraph(pos.x, pos.y, skipGraph[2], true);
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		SetDrawBright2(LIGHTBLUE);
		for (int i = 0; i < 10; i++) {
			DrawGraph(pos.x, pos.y, skipGraph[0], true);
		}
		SetDrawBright2(RED);
		for (int i = 0; i < 10; i++) {
			DrawGraph(pos.x, pos.y, skipGraph[1], true);
		}

		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//チュートリアルのフォント描画
		SetDrawBright2(YELLOW);
		SetDrawBlendMode(DX_BLENDMODE_ADD, sinf(graphRad / 180 * PI) * 255);
		for (int i = 0; i < 10; i++) {
			DrawGraph(0, 120, tutorialFontGraph, true);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// -- レベルサークル描画-- //
	DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelCircleGraph[1], true);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	Color color = HexadecimalColor(LIGHTBLUE);
	SetDrawBright(color.red, color.green, color.blue);
	for (int i = 0; i < 10; i++) {
		DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelCircleGraph[0], true);
		// --レベルの描画-- //
		if (!isTutorialSkip) {
			DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelGraph[level], true);
		}
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (SceneManager::GetDebugMode() == true) {
		DrawFormatString(0, 100, 0xFFFFFF, "ADキー:レベルサークルの半径変更");
		DrawFormatString(0, 120, 0xFFFFFF, "レベルサークルの半径:%f", levelCircle.radius);
		DrawFormatString(0, 140, 0xFFFFFF, "ZCキー:短針の速度変更");
		DrawFormatString(0, 160, 0xFFFFFF, "IPキーで長針の速度を変更");
		DrawFormatString(0, 180, 0xFFFFFF, "カメラシェイク:スペースキー(振動量の調整は未実装)");
		DrawFormatString(0, 200, 0xff, "チュートリアルかどうか:%d", isTutorial);
		DrawFormatString(0, 220, 0xff, "チュートリアルをクリアしたかどうか:%d", isTutorialClear);
		//DrawFormatString(0, 240, 0xFFFFFF, "短針の速度:%f", hourHandSpeed + hourHandlevelSpeed * (level - 1));
		//DrawFormatString(0, 260, 0xFFFFFF, "長針の速度:%f", longHandSpeed);
		//DrawFormatString(0, 280, 0xFFFFFF, "逆走の速度(短針):%f", hourHandReverseSpeed);
		//DrawFormatString(0, 300, 0xFFFFFF, "エネミーのスポーンまでの残り時間:%d", spawnTimer);
		//DrawFormatString(0, 340, 0xFFFFFF, "敵の総数:%d", enemys.size());
		//DrawFormatString(0, 320, 0xFFFFFF, "FPS");
		//DrawFormatString(0, 360, 0xFFFFFF, "アイテムを挟んだ数:%d", itemSandwichCount);
		//
		//DrawFormatString(0, 400, 0xFFFFFF, "敵を挟んだ数:%d", enemySandwichCount);
		//DrawFormatString(0, 420, 0xFFFFFF, "point:%d", point);

		/*SetFontSize(80);*/
		/*SetFontSize(16);*/
	}
}

void GameScene::TutorialSkip(bool flag)
{
	isTutorialSkip = flag;
}
