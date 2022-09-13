#include "Score.h"
#include "DxLib.h"
#include "Util.h"
using namespace Util;

// --インスタンスにNULLを代入-- //
Score* Score::myInstance = nullptr;

// --スコアに0を代入-- //
int Score::realScore = 0;

// --インスタンス読み込み-- //
Score* Score::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new Score();

	// --インスタンスを返す-- //
	return myInstance;
}

// --インスタンス解放-- //
void Score::Relese() {
	// --インスタンスが無かったら何もせずに終了する-- //
	if (myInstance == nullptr) return;

	// --インスタンス解放-- //
	delete myInstance;
	myInstance = nullptr;
}

// --コンストラクタ-- //
Score::Score() : displayScore(0), scoreTime(10) {
	// --表示するスコア-- //
	displayScore = 0;

	// --スコア加算する時間-- //
	scoreTime = 10;

#pragma region 画像読み込み
	// --数字-- //
	LoadDivGraph("Resources/numbers_small.png", 10, 10, 1, 32, 58, numberGraph);

	// --スコアテキスト-- //
	scoreGraph = LoadGraph("Resources/score_small.png");
#pragma endregion
}

// --デストラクタ-- //
Score::~Score() {

}

// --初期化処理-- //
void Score::Initialize() {
	// --表示するスコアの初期化-- //
	displayScore = 0;

	// --実際のスコアの初期化-- //
	realScore = 0;

	// --スコア加算の時間初期化-- //
	scoreTime = 10;
}

// --更新処理-- //
void Score::Update() {
	// --表示するスコアが実際のスコアより小さいとき-- //
	if (displayScore < realScore) {
		// --実際のスコアと表示するスコアの差分-- //
		int addScore = realScore - displayScore;

		// --2つのスコアの差分を時間で割る-- //
		displayScore += addScore / scoreTime + scoreTime;

		// --実際のスコアを超えたら同じ値にする-- //
		if (displayScore > realScore) {
			displayScore = realScore;
		}
	}
}

// --描画処理-- //
void Score::Draw() {
	int num = displayScore;
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(119, 28, 28);

	// --スコア描画-- //
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 15; j++) {
			DrawGraph(1088 + i * 32, 0, numberGraph[num / (int)pow(10, 5 - i)], true);
		}
		num = num % (int)pow(10, 5 - i);
	}

	// --スコアテキスト描画-- //
	for (int i = 0; i < 15; i++) {
		DrawGraph(1149, 58, scoreGraph, true);
	}

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// --指定した分だけスコア加算-- //
void Score::AddScore(int value) {
	realScore += value;
}

// --スコアを参照-- //
int Score::GetScore() { return realScore; }