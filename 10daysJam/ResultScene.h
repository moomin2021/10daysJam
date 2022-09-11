#pragma once
// --コントローラークラス-- //
#include "JoyPadInput.h"

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
#pragma endregion

	// --選択表示の中心座標-- //
	Box selectBox;

#pragma region クラス宣言
	// --コントローラークラス-- //
	JoyPadInput* pad;
#pragma endregion

	// --背景画像ハンドル-- //
	int backGroundGraph;

	// --選択中のシーン-- //
	int selectScene;

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