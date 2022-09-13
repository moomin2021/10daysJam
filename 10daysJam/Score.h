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


#pragma region �摜�n���h��
	// --����-- //
	int numberGraph[10];

	// --�X�R�A�e�L�X�g-- //
	int scoreGraph;

	// --�X�R�A�{�[�h-- //
	int scoreBoardGraph[2];
#pragma endregion

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