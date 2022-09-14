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
	// --タイトルシーンBGM-- //
	titleSceneBGM = LoadSoundMem("Sounds/titleBGM.mp3");

	// --ゲームシーンBGM-- //
	gameSceneBGM = LoadSoundMem("Sounds/playBGM.mp3");

	// --リザルトシーンBGM-- //
	resultSceneBGM = LoadSoundMem("Sounds/resultBGM.mp3");
#pragma endregion

#pragma region SE読み込み
	// --レベルアップSE-- //
	levelUpSE = LoadSoundMem("Sounds/lvUp.mp3");

	// --挟んだ（長針と短針がぶつかった）時のSE
	sandSE = LoadSoundMem("Sounds/sand.mp3");

	// --アイテム獲得SE-- //
	getItemSE = LoadSoundMem("Sounds/getItem.mp3");

	// --敵に当たったSE-- //
	hitEnemySE = LoadSoundMem("Sounds/hitEnemy.mp3");

	// --決定SE-- //
	selectSE = LoadSoundMem("Sounds/select.mp3");

	// --選択SE-- //
	buttonSE = LoadSoundMem("Sounds/button.mp3");
#pragma endregion

	// --BGM全体の音量初期化-- //
	volumeBGM = 50;

	// --SE全体の音量初期化-- //
	volumeSE = 50;

#pragma region BGMの音量設定
	// --タイトルシーン-- //
	ChangeVolumeSoundMem(volumeBGM, titleSceneBGM);

	// --ゲームシーン-- //
	ChangeVolumeSoundMem(volumeBGM, gameSceneBGM);

	// --リザルトシーン-- //
	ChangeVolumeSoundMem(volumeBGM, resultSceneBGM);
#pragma endregion

#pragma region SEの音量設定
	// --レベルアップSE-- //
	ChangeVolumeSoundMem(volumeSE, levelUpSE);

	// --挟んだ（長針と短針がぶつかった）時のSE
	ChangeVolumeSoundMem(volumeSE, sandSE);

	// --アイテム獲得SE-- //
	ChangeVolumeSoundMem(volumeSE, getItemSE);

	// --敵に当たったSE-- //
	ChangeVolumeSoundMem(volumeSE, hitEnemySE);

	// --決定SE-- //
	ChangeVolumeSoundMem(volumeSE, selectSE);

	// --選択SE-- //
	ChangeVolumeSoundMem(volumeSE, buttonSE);
#pragma endregion
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
		return;
	}

	// --ゲームシーンBGM再生-- //
	if (bgmName == GAMESCENEBGM) {
		// --既に再生している場合何もしない-- //
		if (CheckSoundMem(gameSceneBGM)) return;

		// --BGMをループ設定で再生-- //
		PlaySoundMem(gameSceneBGM, DX_PLAYTYPE_LOOP, true);
		return;
	}

	// --リザルトシーン再生-- //
	if (bgmName == RESULTSCENEBGM) {
		// --既に再生している場合何もしない-- //
		if (CheckSoundMem(resultSceneBGM)) return;
		
		// --BGMをループ設定で再生-- //
		PlaySoundMem(resultSceneBGM, DX_PLAYTYPE_LOOP, true);
		return;
	}
}

// --SEを再生する-- //
void Sound::PlaySE(int seName) {
	// --レベルアップSE再生-- //
	if (seName == LEVELUPSE) {
		// --SEを再生-- //
		PlaySoundMem(levelUpSE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --挟んだ（長針と短針がぶつかった）時のSE再生-- //
	if (seName == SANDSE) {
		// --SEを再生-- //
		PlaySoundMem(sandSE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --アイテム獲得SE再生-- //
	if (seName == GETITEMSE) {
		// --SEを再生-- //
		PlaySoundMem(getItemSE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --敵に当たった再生-- //
	if (seName == HITENEMYSE) {
		// --SEを再生-- //
		PlaySoundMem(hitEnemySE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --決定SE再生-- //
	if (seName == SELECTSE) {
		// --SEを再生-- //
		PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --選択SE再生-- //
	if (seName == BUTTONSE) {
		// --SEを再生-- //
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK, true);
		return;
	}
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