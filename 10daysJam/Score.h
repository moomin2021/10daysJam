#pragma once

class Score {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Score* myInstance;

	// --���ۂ̃X�R�A-- //
	static int realScore;

	// --�\������X�R�A-- //
	int displayScore;

	// --�X�R�A���Z���鎞��-- //
	int scoreTime;

	// --�X�R�A�̉摜�n���h��-- //
	int scoreGraph[10];

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�ǂݍ���-- //
	static Score* GetInstance();

	// --�C���X�^���X���-- //
	void Relese();

	// --�f�X�g���N�^-- //
	~Score();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	// --�w�肵���������X�R�A���Z-- //
	static void AddScore(int value);

	// --�X�R�A���Q��-- //
	static int GetScore();

private:
	// --�R���X�g���N�^-- //
	Score();

	/// --�����o�֐�END-- ///
};