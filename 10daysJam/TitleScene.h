#pragma once
// --コントローラークラス-- //
#include "JoyPadInput.h"

// --サウンドクラス-- //
#include "Sound.h"

// --便利系クラス-- //
#include "Util.h"

class TitleScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static TitleScene* myInstance;

	// --コントローラークラス-- //
	JoyPadInput* pad;

	// --サウンドクラス-- //
	Sound* sound;

#pragma region 画像ハンドル宣言
	// --タイトルロゴ画像ハンドル-- //
	int titlelogoGraph[4];

	// --背景-- //
	int backGroundGraph;

	// --タイトルのUI-- //
	int titleUIGraph[2];
#pragma endregion

	// --選択表示の中心座標-- //
	Box selectBox;

	//画像明暗用ラジアン
	float graphRad = 0;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static TitleScene* GetInstance();

	// --インスタンス解放-- //
	void Relese();

	// --デストラクタ-- //
	~TitleScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	TitleScene();

	/// --メンバ関数END-- ///
};