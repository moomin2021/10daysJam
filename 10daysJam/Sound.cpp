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
	// --�Q�[���V�[��BGM�ǂݍ���-- //
	gameSceneBGM = LoadSoundMem("Sounds/playBGM.mp3");
#pragma endregion

	// --�{�����[���ݒ�-- //
	ChangeVolumeSoundMem(10, gameSceneBGM);
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
	}

	// --�Q�[���V�[��BGM�Đ�-- //
	if (bgmName == GAMESCENEBGM) {
		// --���ɍĐ����Ă���ꍇ�������Ȃ�-- //
		if (CheckSoundMem(gameSceneBGM)) return;

		// --BGM�����[�v�ݒ�ōĐ�-- //
		PlaySoundMem(gameSceneBGM, DX_PLAYTYPE_LOOP, true);
	}

	// --���U���g�V�[���Đ�-- //
	if (bgmName == RESULTSCENEBGM) {
		// --���ɍĐ����Ă���ꍇ�������Ȃ�-- //
		if (CheckSoundMem(resultSceneBGM)) return;
		
		// --BGM�����[�v�ݒ�ōĐ�-- //
		PlaySoundMem(resultSceneBGM, DX_PLAYTYPE_LOOP, true);
	}
}

// --SE���Đ�����-- //
void Sound::PlaySE(int seName) {

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