#include "GameScene.h"
#include "SceneManager.h"
using namespace Util;

void DrawCircle(Circle c, int color, bool fillFlag);

void DrawLine(Line l, int thickness = 1);

// --インスタンスにNULLを代入-- //
GameScene* GameScene::myInstance = nullptr;

// --インスタンス読み込み-- //
GameScene* GameScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new GameScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --コンストラクタ-- //
GameScene::GameScene() : clock{ 640, 480, 416 }, player{ 0, 0, 16 }, playerSpd(2.0f),
longHand{ {640, 480}, {640, 0}, clock.radius, 180, 0xFF0000},
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 180, 0xFF }
{
	// --入力クラスインスタンス取得-- //
	input = Input::GetInstance();
}

// --デストラクタ-- //
GameScene::~GameScene() {

}

// --初期化処理-- //
void GameScene::Initialize() {

}

// --更新処理-- //
void GameScene::Update() {



#pragma region 針の座標計算

	//長針を常時回転
	longHand.radian -= 0.5f;
	//-360度超えたら0に戻す
	longHand.radian = fmodf(longHand.radian, 360.0f);
	//針の角度で終点座標を計算
	longHand.end.x = (longHand.length * sinf(longHand.radian / 180 * PI)) + clock.x;
	longHand.end.y = (longHand.length * cosf(longHand.radian / 180 * PI)) + clock.y;

	//長針を常時回転
	hourHand.radian -= 2.0f;
	//-360度超えたら0に戻す
	hourHand.radian = fmodf(hourHand.radian, 360.0f);
	//針の角度で終点座標を計算
	hourHand.end.x = (hourHand.length * sinf(hourHand.radian / 180 * PI)) + clock.x;
	hourHand.end.y = (hourHand.length * cosf(hourHand.radian / 180 * PI)) + clock.y;


#pragma endregion

#pragma region 自機移動関係
	//自機移動
	if (input->IsPress(KEY_INPUT_A) || input->IsPress(KEY_INPUT_S) || input->IsPress(KEY_INPUT_W) || input->IsPress(KEY_INPUT_D)) {

		//ADキーで短針上での位置を変更
		playerPos += ((input->IsPress(KEY_INPUT_D) - input->IsPress(KEY_INPUT_A)) * playerSpd);
		//最大値は短針の長さ
		if (playerPos > hourHand.length)playerPos = hourHand.length;
	
	}

	//短針上での自機の位置を参照して自機座標計算
	//自機は短針上に位置するので、角度は短針のものを使う
	player.x = (playerPos * sinf(hourHand.radian / 180 * PI)) + clock.x;
	player.y = (playerPos * cosf(hourHand.radian / 180 * PI)) + clock.y;


	//アローキーで自機速度変更
	playerSpd += ((input->IsPress(KEY_INPUT_E) - input->IsPress(KEY_INPUT_Q)) * 0.2f);
	if (input->IsPress(KEY_INPUT_R)) playerSpd = 2.0f;

#pragma endregion

}

// --描画処理-- //
void GameScene::Draw() {
	DrawCircle(player, 0xffffff, true);
	DrawCircle(clock, 0xffffff, false);
	DrawLine(longHand, 4);
	DrawLine(hourHand);
	DrawFormatString(0, 0, 0x00ffff, "playerSpeed:%f", playerSpd);
	DrawFormatString(0, 20, 0x00ffff, "Rキー:速度リセット");
	DrawFormatString(0, 40, longHand.color, "longHand(長針)の情報 x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 60, hourHand.color, "hourHand(短針)の情報 x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
}

void DrawCircle(Circle c, int color, bool fillFlag)
{

	DrawCircle(c.x, c.y, c.radius, color, fillFlag);
}

void DrawLine(Line l, int thickness)
{
	DrawLine(l.start.x, l.start.y, l.end.x, l.end.y, l.color, thickness);
}
