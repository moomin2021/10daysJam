#pragma once
#include "Input.h"
#include<vector>
#include "Util.h"
#include "Player.h"
#include "Enemy.h"
#include "JoyPadInput.h"
#include"Camera.h"
#include"BreakEffect.h"

class GameScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static GameScene* myInstance;

#pragma region クラス宣言
	// --入力クラス-- //
	Input* input;

	// --コントローラークラス-- //
	JoyPadInput* pad;

	// --プレイヤークラス-- //
	Player* player;

	// --エネミー-- //
	std::vector<Enemy> enemys;

	// --エフェクトの配列-- //
	std::vector<BreakEffect> breakEffects;

	// --カメラ-- //
	Camera camera;
#pragma endregion

#pragma region エネミーのスポーン関係変数の宣言
	// --敵のスポーン位置を確定してからスポーンさせるまでの時間-- //
	int delayMax;
	
	// --次に敵が発生するまでの間隔-- //
	int spawnInterval;

	// --敵のスポーン遅延の残り時間-- //
	int spawnDelay;

	// --敵の発生タイマー-- //
	int spawnTimer;

	// --敵のスポーン率-- //
	float enemySpawnRate;

	// --敵が短針上のどこでスポーンするかの変数-- //
	float enemyLength; 

	// --確定した敵のスポーン位置を保存する用変数-- //
	Vector2 enemyPos;
#pragma endregion

#pragma region 時計関係変数の宣言
	// --時計-- //
	Circle clock;

	// --長針-- //
	Line longHand;

	// --長針の速度-- //
	float longHandSpeed;

	// --短針-- //
	Line hourHand;

	// --短針の速度-- //
	float hourHandSpeed;

	// --レベルによる短針の速度の上がり幅-- //
	float hourHandlevelSpeed;

	// --短針が逆回りするときの速度-- //
	float reverseSpeed;
#pragma endregion

#pragma region レベル関係変数の宣言
	// --真ん中のレベルを表記する円-- //
	Circle levelCircle;

	// --レベルサークルの新しい半径-- //
	float newCircleRadius;

	// --レベル-- //
	int level;

	// --経験値-- //
	int point;

	// --レベルによって必要な経験値-- //
	int needPoint[10];

#pragma endregion

#pragma region エフェクト関係変数の宣言
	// --敵の爆発したときの円の大きさ用-- //
	Circle burstCircle;
#pragma endregion

#pragma region 画像用ハンドル変数の宣言
	// --時計や針の描画用画像-- //
	int whiteCircleGraph;
#pragma endregion

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static GameScene* GetInstance();

	// --インスタンス解放-- //
	void Relese();

	// --デストラクタ-- //
	~GameScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	// --ゲームシーンクラスで行う当たり判定をすべて処理する-- //
	void Collision();

	// --敵のスポーン処理-- //
	void EnemySpawn();

	// --レベル更新-- //
	void LevelUpdate();

	// --レベルをリセットする-- //
	void LevelReset();

/// <summary>
/// 長針の衝撃エフェクト作成関数
/// </summary>
void CreateBreakEffect(Vector2 pos ,int effectParam);

private:
	// --コンストラクタ-- //
	GameScene();

	/// --メンバ関数END-- ///
};