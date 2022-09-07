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

// --コンストラクタ-- //
Score::Score() : displayScore(0), scoreTime(10) {

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
	DrawFormatString(800, 0, 0xFFFFFF, "%06d", displayScore);
	DrawFormatString(0, 200, 0xFFFFFF, "実際のスコア = %d", realScore);
	DrawFormatString(0, 220, 0xFFFFFF, "表示するスコア = %d", displayScore);
}

// --指定した分だけスコア加算-- //
void Score::AddScore(int value) {
	realScore += value;
}