#pragma once

enum BGM {
	TITLESCENEBGM,
	GAMESCENEBGM,
	RESULTSCENEBGM,
};

class Sound {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Sound* myInstance;

#pragma region BGMハンドル変数
	// --タイトルシーンBGM-- //
	int titleSceneBGM;

	// --ゲームシーンBGM-- //
	int gameSceneBGM;

	// --リザルトシーンBGM-- //
	int resultSceneBGM;
#pragma endregion

#pragma region SEハンドル変数

#pragma endregion

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス読み込み-- //
	static Sound* GetInstance();

	// --インスタンス解放-- //
	void Relese();

	// --デストラクタ-- //
	~Sound();

	// --サウンド読み込み-- //
	void LoadSound();

	// --BGMを再生する-- //
	void PlayBGM(int bgmName);

	// --SEを再生する-- //
	void PlaySE(int seName);

	// --BGMの再生を止める-- //
	void StopBGM(int bgmName);

	// --SEの再生を止める-- //
	void StopSE(int seName);

private:
	// --コンストラクタ-- //
	Sound();

	/// --メンバ関数END-- ///
};