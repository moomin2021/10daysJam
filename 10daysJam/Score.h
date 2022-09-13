#pragma once

class Score {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Score* myInstance;

	// --実際のスコア-- //
	static int realScore;

	// --表示するスコア-- //
	int displayScore;

	// --スコア加算する時間-- //
	int scoreTime;


#pragma region 画像ハンドル
	// --数字-- //
	int numberGraph[10];

	// --スコアテキスト-- //
	int scoreGraph;

	// --スコアボード-- //
	int scoreBoardGraph[2];
#pragma endregion

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス読み込み-- //
	static Score* GetInstance();

	// --インスタンス解放-- //
	void Relese();

	// --デストラクタ-- //
	~Score();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	// --指定した分だけスコア加算-- //
	static void AddScore(int value);

	// --スコアを参照-- //
	static int GetScore();

private:
	// --コンストラクタ-- //
	Score();

	/// --メンバ関数END-- ///
};