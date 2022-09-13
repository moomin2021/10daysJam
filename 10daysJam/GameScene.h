#pragma once
#include "Input.h"
#include<vector>
#include "Util.h"
#include "Player.h"
#include "Enemy.h"
#include "JoyPadInput.h"
#include"Camera.h"
#include"BreakEffect.h"
#include"Particle.h"
#include"Star.h"
#include "Sound.h"

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

	// --サウンドクラス-- //
	Sound* sound;

	// --プレイヤークラス-- //
	Player* player;

	// --エネミー-- //
	std::vector<Enemy> enemys;

	// --エフェクトの配列-- //
	std::vector<BreakEffect> breakEffects;

	// --カメラ-- //
	Camera camera;
#pragma endregion

//オープニング演出系の変数
	bool isOpening;
	int opEnemyMax = 5;
	std::vector<int> opSpawnFrame;
	int openingTime = 400; //8秒
	int animationTime = 250; //5秒
	int nowTime;

	//チュートリアルの変数
	bool isTutorial;
	int tutorialEnemyMax;
	std::vector<Enemy> tutorialEnemy;
	bool isTutorialClear;
	int sceneChangeTime = 50;
	int sceneChangeTimer;


#pragma region エネミーのスポーン関係変数の宣言
	
	// --次に敵が発生するまでの間隔-- //
	int spawnInterval;

	// --敵の発生タイマー-- //
	int spawnTimer;

	// --敵のスポーン率-- //
	float enemySpawnRate;

	// --敵が短針上のどこでスポーンするかの変数-- //
	float enemyLength; 

	// --敵を挟んだ数をカウントする変数-- //
	int enemySandwichCount;

	// --アイテムを挟んだ数をカウントする変数-- //
	int itemSandwichCount;


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
	float hourHandReverseSpeed;

	float longHandReverseSpeed;

	//　--逆回りの速度倍率
	float reverseVelocityScale;
	float reverseVelocityScaleLong;

	// --逆回りの力-- //
	float reverseTime;

	// --回転するパーティクル-- //
	float starLen;
	Star star[5];
	Star star2[5];

	//短針、長針からでるパーティクル
	int lineParticleMax;
	std::vector<Particle> hourHandParticle;
	std::vector<Particle> longHandParticle;



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
	std::vector<Box> burstCircleEffects;
	std::vector<int> burstEffectColorParam;
	std::vector<int> burstEffectColor;

	// --レベルが変動した時のエフェクト--
	std::vector<Particle> levelChangeParticle;
#pragma endregion

#pragma region 画像用ハンドル変数の宣言
	// --時計や針の描画用画像-- //
	int whiteCircleGraph;

	// --カウント-- //
	int countNumGraph[3];

	// --パーティクル--
	int particleGraph;

	// --アイテム-- //
	int itemGraph[2];

	// --敵-- //
	int enemyGraph[2];

	// --背景-- //
	int backGroundGraph;
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
	void EnemySpawn(float radian);

	// --レベル更新-- //
	void LevelUpdate();

	// --レベルをリセットする-- //
	void LevelReset();

	// --針の反転力を増加させる関数-- //
	void AddReversePower(int power);

	// --ゲームが開始されたときの更新処理--
	void OpeningUpdate();

	void LevelUpEfffect(int effectNum);

	void CreateBurstEffect(Circle burstRange , int effectNum);

	void UpdateTutorial();

	void DrawTutorial();

/// <summary>
/// 長針の衝撃エフェクト作成関数
/// </summary>
void CreateBreakEffect(Vector2 pos ,int effectParam);

private:
	// --コンストラクタ-- //
	GameScene();

	/// --メンバ関数END-- ///
};