#pragma once

enum BGM {
	TITLESCENEBGM,
	GAMESCENEBGM,
	RESULTSCENEBGM,
};

class Sound {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Sound* myInstance;

#pragma region BGM�n���h���ϐ�
	// --�^�C�g���V�[��BGM-- //
	int titleSceneBGM;

	// --�Q�[���V�[��BGM-- //
	int gameSceneBGM;

	// --���U���g�V�[��BGM-- //
	int resultSceneBGM;
#pragma endregion

#pragma region SE�n���h���ϐ�

#pragma endregion

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�ǂݍ���-- //
	static Sound* GetInstance();

	// --�C���X�^���X���-- //
	void Relese();

	// --�f�X�g���N�^-- //
	~Sound();

	// --�T�E���h�ǂݍ���-- //
	void LoadSound();

	// --BGM���Đ�����-- //
	void PlayBGM(int bgmName);

	// --SE���Đ�����-- //
	void PlaySE(int seName);

	// --BGM�̍Đ����~�߂�-- //
	void StopBGM(int bgmName);

	// --SE�̍Đ����~�߂�-- //
	void StopSE(int seName);

private:
	// --�R���X�g���N�^-- //
	Sound();

	/// --�����o�֐�END-- ///
};