#include "Sound.h"

// --DXライブラリ-- //
#include "DxLib.h"

// --インスタンスにNULLを代入-- //
Sound* Sound::myInstance = nullptr;

// --インスタンス読み込み-- //
Sound* Sound::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new Sound();

	// --インスタンスを返す-- //
	return myInstance;
}

// --インスタンス解放-- //
void Sound::Relese() {
	// --インスタンスが無かったら何もせずに終了する-- //
	if (myInstance == nullptr) return;

	// --インスタンス解放-- //
	delete myInstance;
	myInstance = nullptr;
}

// --コンストラクタ-- //
Sound::Sound() {
#pragma region BGM読み込み
	// --ゲームシーンBGM読み込み-- //
	gameSceneBGM = LoadSoundMem("Sounds/playBGM.mp3");
#pragma endregion

	// --ボリューム設定-- //
	ChangeVolumeSoundMem(10, gameSceneBGM);
}

// --デストラクタ-- //
Sound::~Sound() {

}

// --サウンド読み込み-- //
void Sound::LoadSound() {

}

// --BGMを再生する-- //
void Sound::PlayBGM(int bgmName) {
	// --タイトルシーンBGM再生-- //
	if (bgmName == TITLESCENEBGM) {
		// --既に再生している場合何もしない-- //
		if (CheckSoundMem(titleSceneBGM)) return;

		// --BGMをループ設定で再生-- //
		PlaySoundMem(titleSceneBGM, DX_PLAYTYPE_LOOP, true);
	}

	// --ゲームシーンBGM再生-- //
	if (bgmName == GAMESCENEBGM) {
		// --既に再生している場合何もしない-- //
		if (CheckSoundMem(gameSceneBGM)) return;

		// --BGMをループ設定で再生-- //
		PlaySoundMem(gameSceneBGM, DX_PLAYTYPE_LOOP, true);
	}

	// --リザルトシーン再生-- //
	if (bgmName == RESULTSCENEBGM) {
		// --既に再生している場合何もしない-- //
		if (CheckSoundMem(resultSceneBGM)) return;
		
		// --BGMをループ設定で再生-- //
		PlaySoundMem(resultSceneBGM, DX_PLAYTYPE_LOOP, true);
	}
}

// --SEを再生する-- //
void Sound::PlaySE(int seName) {

}

// --BGMの再生を止める-- //
void Sound::StopBGM(int bgmName) {
	// --タイトルシーンBGMの再生を止める-- //
	if (bgmName == TITLESCENEBGM) {
		// --再生していなかった場合何もしない-- //
		if (!CheckSoundMem(titleSceneBGM)) return;

		// --BGMの再生を止める-- //
		StopSoundMem(titleSceneBGM);
	}

	// --ゲームシーンBGMの再生を止める-- //
	if (bgmName == GAMESCENEBGM) {
		// --再生していなかった場合何もしない-- //
		if (!CheckSoundMem(gameSceneBGM)) return;

		// --BGMの再生を止める-- //
		StopSoundMem(gameSceneBGM);
	}

	// --リザルトシーンの再生を止める-- //
	if (bgmName == RESULTSCENEBGM) {
		// --再生していなかった場合何もしない-- //
		if (!CheckSoundMem(resultSceneBGM)) return;

		// --BGMの再生を止める-- //
		StopSoundMem(resultSceneBGM);
	}
}

// --SEの再生を止める-- //
void Sound::StopSE(int seName) {

}