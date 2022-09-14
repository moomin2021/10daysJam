#pragma once
// --コントローラークラス-- //
#include "JoyPadInput.h"

// --サウンドクラス-- //
#include "Sound.h"

// --便利関数-- //
#include "Util.h"

class ResultScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static ResultScene* myInstance;

#pragma region 画像ハンドル
	// --タイトルへ戻るテキスト-- //
	int gotitleGraph;

	// --リトライテキスト-- //
	int retryGraph;

	// --ASBCランクのテキスト（小）-- //
	int sabcSmallGraph[4];

	// --ASBCランクのテキスト（大）-- //
	int sabcBigGraph[4];

	// --スコア表示に使う番号のテキスト-- //
	int numberGraph[10];

	// --ランクテキスト-- //
	int rankGraph;

	// --スコアテキスト-- //
	int scoreGraph;

	// --リザルトテキスト-- //
	int resultGraph;

	// --スコアゲージ-- //
	int scoreGaugeGraph;

	// --スコアゲージの枠-- //
	int scoreGaugeLineGraph;

	// --背景-- //
	int backGroundGraph;

	// --十字キー-- //
	int selectUIGraph[4];

	// --ボタン-- //
	int buttonGraph[3];

	float graphRad = 0;

#pragma endregion

	// --選択表示の中心座標-- //
	Box selectBox;

	Vector2 pos;

#pragma region クラス宣言
	// --コントローラークラス-- //
	JoyPadInput* pad;

	// --サウンドクラス-- //
	Sound* sound;
#pragma endregion

	// --選択中のシーン-- //
	int selectScene;

	// --スコアゲージ座標-- //
	BoxAA gaugeMax;
	BoxAA gaugeS;
	BoxAA gaugeA;
	BoxAA gaugeB;
	BoxAA gaugeC;

	// --各ランクのスコア-- //
	int scoreValueMax;
	int scoreValueS;
	int scoreValueA;
	int scoreValueB;
	int scoreValueC;

	// --入力受付-- //
	bool isActive;

	// --表示するスコア-- //
	int displayScore;

	// --ランクの添字-- //
	int rankIndex;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static ResultScene* GetInstance();

	// --インスタンス解放-- //
	void Relese();

	// --デストラクタ-- //
	~ResultScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	ResultScene();

	/// --メンバ関数END-- ///
};