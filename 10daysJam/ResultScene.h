#pragma once
// --コントローラークラス-- //
#include "JoyPadInput.h"

class ResultScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static ResultScene* myInstance;

#pragma region クラス宣言
	// --コントローラークラス-- //
	JoyPadInput* pad;
#pragma endregion

	// --背景画像ハンドル-- //
	int backGroundGraph;

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