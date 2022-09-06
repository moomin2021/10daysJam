#include "DxLib.h"
#include"Input.h"
#include"Vector2.h"
#include"JoyPadInput.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2A_14_タムラ_フミヤ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

struct  Circle
{
	float x;
	float y;
	float radius;
};

void DrawCircle(Circle c, int color, bool fillFlag);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	int iguigu;
	int iguiug8;
	int fumiya;
	int moomin;
	int test01;
	int test072;
	int gitTest;

	int superrrrrrrrrrrrrrrr;

	Circle clock{
		WIN_WIDTH / 2,
		WIN_HEIGHT / 2,
		WIN_HEIGHT / 2
	};

	Circle player{
		0,
		0,
		16
	};

	float playerSpd = 2.0f;

	//インプット系クラス宣言
	Input key{};



	// ゲームループ
	while (true) {

		//キーボード更新
		key.KeyUpdate();


		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//---------  更新処理  -----------------------//

		//自機移動
		if (key.IsPress(KEY_INPUT_A) || key.IsPress(KEY_INPUT_S) || key.IsPress(KEY_INPUT_W) || key.IsPress(KEY_INPUT_D)) {
		
			player.x += ((key.IsPress(KEY_INPUT_D) - key.IsPress(KEY_INPUT_A)) * playerSpd);
			player.y += ((key.IsPress(KEY_INPUT_S) - key.IsPress(KEY_INPUT_W)) * playerSpd);
		}

		//アローキーで自機速度変更
		playerSpd += ( (key.IsPress(KEY_INPUT_E) - key.IsPress(KEY_INPUT_Q)) * 0.2f);

		//---------  描画処理  -----------------------//

		DrawCircle(player, 0xffffff, true);
		DrawCircle(clock, 0xffffff, false);
		DrawFormatString(0, 0, 0x00ffff, "playerSpeed:%f", playerSpd);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

void DrawCircle(Circle c, int color, bool fillFlag)
{
	
	DrawCircle(c.x, c.y, c.radius, color, fillFlag);
}
