#include "Sound.h"

// --DX���C�u����-- //
#include "DxLib.h"

// --�C���X�^���X��NULL����-- //
Sound* Sound::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Sound* Sound::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new Sound();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�C���X�^���X���-- //
void Sound::Relese() {
	// --�C���X�^���X�����������牽�������ɏI������-- //
	if (myInstance == nullptr) return;

	// --�C���X�^���X���-- //
	delete myInstance;
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
Sound::Sound() {
#pragma region BGM�ǂݍ���
	// --�^�C�g���V�[��BGM-- //
	titleSceneBGM = LoadSoundMem("Sounds/titleBGM.mp3");

	// --�Q�[���V�[��BGM-- //
	gameSceneBGM = LoadSoundMem("Sounds/playBGM.mp3");

	// --���U���g�V�[��BGM-- //
	resultSceneBGM = LoadSoundMem("Sounds/resultBGM.mp3");
#pragma endregion

#pragma region SE�ǂݍ���
	// --���x���A�b�vSE-- //
	levelUpSE = LoadSoundMem("Sounds/lvUp.mp3");

	// --���񂾁i���j�ƒZ�j���Ԃ������j����SE
	sandSE = LoadSoundMem("Sounds/sand.mp3");

	// --�A�C�e���l��SE-- //
	getItemSE = LoadSoundMem("Sounds/getItem.mp3");

	// --�G�ɓ�������SE-- //
	hitEnemySE = LoadSoundMem("Sounds/hitEnemy.mp3");

	// --����SE-- //
	selectSE = LoadSoundMem("Sounds/select.mp3");

	// --�I��SE-- //
	buttonSE = LoadSoundMem("Sounds/button.mp3");
#pragma endregion

	// --BGM�S�̂̉��ʏ�����-- //
	volumeBGM = 50;

	// --SE�S�̂̉��ʏ�����-- //
	volumeSE = 50;

#pragma region BGM�̉��ʐݒ�
	// --�^�C�g���V�[��-- //
	ChangeVolumeSoundMem(volumeBGM, titleSceneBGM);

	// --�Q�[���V�[��-- //
	ChangeVolumeSoundMem(volumeBGM, gameSceneBGM);

	// --���U���g�V�[��-- //
	ChangeVolumeSoundMem(volumeBGM, resultSceneBGM);
#pragma endregion

#pragma region SE�̉��ʐݒ�
	// --���x���A�b�vSE-- //
	ChangeVolumeSoundMem(volumeSE, levelUpSE);

	// --���񂾁i���j�ƒZ�j���Ԃ������j����SE
	ChangeVolumeSoundMem(volumeSE, sandSE);

	// --�A�C�e���l��SE-- //
	ChangeVolumeSoundMem(volumeSE, getItemSE);

	// --�G�ɓ�������SE-- //
	ChangeVolumeSoundMem(volumeSE, hitEnemySE);

	// --����SE-- //
	ChangeVolumeSoundMem(volumeSE, selectSE);

	// --�I��SE-- //
	ChangeVolumeSoundMem(volumeSE, buttonSE);
#pragma endregion
}

// --�f�X�g���N�^-- //
Sound::~Sound() {

}

// --�T�E���h�ǂݍ���-- //
void Sound::LoadSound() {

}

// --BGM���Đ�����-- //
void Sound::PlayBGM(int bgmName) {
	// --�^�C�g���V�[��BGM�Đ�-- //
	if (bgmName == TITLESCENEBGM) {
		// --���ɍĐ����Ă���ꍇ�������Ȃ�-- //
		if (CheckSoundMem(titleSceneBGM)) return;

		// --BGM�����[�v�ݒ�ōĐ�-- //
		PlaySoundMem(titleSceneBGM, DX_PLAYTYPE_LOOP, true);
		return;
	}

	// --�Q�[���V�[��BGM�Đ�-- //
	if (bgmName == GAMESCENEBGM) {
		// --���ɍĐ����Ă���ꍇ�������Ȃ�-- //
		if (CheckSoundMem(gameSceneBGM)) return;

		// --BGM�����[�v�ݒ�ōĐ�-- //
		PlaySoundMem(gameSceneBGM, DX_PLAYTYPE_LOOP, true);
		return;
	}

	// --���U���g�V�[���Đ�-- //
	if (bgmName == RESULTSCENEBGM) {
		// --���ɍĐ����Ă���ꍇ�������Ȃ�-- //
		if (CheckSoundMem(resultSceneBGM)) return;
		
		// --BGM�����[�v�ݒ�ōĐ�-- //
		PlaySoundMem(resultSceneBGM, DX_PLAYTYPE_LOOP, true);
		return;
	}
}

// --SE���Đ�����-- //
void Sound::PlaySE(int seName) {
	// --���x���A�b�vSE�Đ�-- //
	if (seName == LEVELUPSE) {
		// --SE���Đ�-- //
		PlaySoundMem(levelUpSE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --���񂾁i���j�ƒZ�j���Ԃ������j����SE�Đ�-- //
	if (seName == SANDSE) {
		// --SE���Đ�-- //
		PlaySoundMem(sandSE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --�A�C�e���l��SE�Đ�-- //
	if (seName == GETITEMSE) {
		// --SE���Đ�-- //
		PlaySoundMem(getItemSE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --�G�ɓ��������Đ�-- //
	if (seName == HITENEMYSE) {
		// --SE���Đ�-- //
		PlaySoundMem(hitEnemySE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --����SE�Đ�-- //
	if (seName == SELECTSE) {
		// --SE���Đ�-- //
		PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		return;
	}

	// --�I��SE�Đ�-- //
	if (seName == BUTTONSE) {
		// --SE���Đ�-- //
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK, true);
		return;
	}
}

// --BGM�̍Đ����~�߂�-- //
void Sound::StopBGM(int bgmName) {
	// --�^�C�g���V�[��BGM�̍Đ����~�߂�-- //
	if (bgmName == TITLESCENEBGM) {
		// --�Đ����Ă��Ȃ������ꍇ�������Ȃ�-- //
		if (!CheckSoundMem(titleSceneBGM)) return;

		// --BGM�̍Đ����~�߂�-- //
		StopSoundMem(titleSceneBGM);
	}

	// --�Q�[���V�[��BGM�̍Đ����~�߂�-- //
	if (bgmName == GAMESCENEBGM) {
		// --�Đ����Ă��Ȃ������ꍇ�������Ȃ�-- //
		if (!CheckSoundMem(gameSceneBGM)) return;

		// --BGM�̍Đ����~�߂�-- //
		StopSoundMem(gameSceneBGM);
	}

	// --���U���g�V�[���̍Đ����~�߂�-- //
	if (bgmName == RESULTSCENEBGM) {
		// --�Đ����Ă��Ȃ������ꍇ�������Ȃ�-- //
		if (!CheckSoundMem(resultSceneBGM)) return;

		// --BGM�̍Đ����~�߂�-- //
		StopSoundMem(resultSceneBGM);
	}
}

// --SE�̍Đ����~�߂�-- //
void Sound::StopSE(int seName) {

}