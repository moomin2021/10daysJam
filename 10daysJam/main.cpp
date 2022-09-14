#include "DxLib.h"
#include "Util.h"
#include"Input.h"
#include"JoyPadInput.h"
#include "SceneManager.h"

// --サウンドクラス-- //
#include "Sound.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "2005_Retuck";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

int counter = 0, FpsTime[2] = { 0, }, FpsTime_i = 0;
int color_white;
double Fps = 0.0;
char Key[256];

void SetColor() {
	color_white = GetColor(255, 255, 255);            //白色ハンドルを取得
	return;
}

void FpsTimeFanction() {
	if (FpsTime_i == 0)
		FpsTime[0] = GetNowCount();               //1周目の時間取得
	if (FpsTime_i == 49) {
		FpsTime[1] = GetNowCount();               //50周目の時間取得
		Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//測定した値からfpsを計算
		FpsTime_i = 0;//カウントを初期化
	}
	else
		FpsTime_i++;//現在何周目かカウント
	if (Fps != 0) {
		if (SceneManager::GetDebugMode() == true)
		DrawFormatString(0, 380, 0xFFFFFF, "FPS %.1f", Fps); //fpsを表示
	}
	return;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	//log.txtを出さないように
	SetOutApplicationLogValidFlag(FALSE);

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
	int backColor = 44;
	SetBackgroundColor(backColor,backColor,backColor);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	
	// --シーン管理クラスインスタンス取得-- //
	SceneManager* sceneM = SceneManager::GetInstance();

	// --シーン管理クラス初期化-- //
	sceneM->Initialize();

	// --入力クラス-- //
	Input* input = Input::GetInstance();

	// --コントローラークラスインスタンス取得-- //
	JoyPadInput* pad = JoyPadInput::GetInstance();

	// --サウンドクラスインスタンス読み込み-- //
	Sound* sound = Sound::GetInstance();

	// --サウンドの読み込み-- //
	sound->LoadSound();

	// ゲームループ
	while (true) {

		//キーボード更新
		input->Update();
		pad->Update();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//---------  更新処理  -----------------------//

		// --シーン管理クラスの更新処理-- //
		sceneM->Update();

		//---------  描画処理  -----------------------//

		// --シーン管理クラス描画処理-- //
		sceneM->Draw();

		FpsTimeFanction();

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// --ゲームエンドフラグがtrueだったらループを抜ける-- //
		if (sceneM->GetEndFlag() == true) {
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