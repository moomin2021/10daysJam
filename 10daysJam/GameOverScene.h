#pragma once

class GameOverScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static GameOverScene* myInstance;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static GameOverScene* GetInstance();

	// --�f�X�g���N�^-- //
	~GameOverScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	GameOverScene();

	/// --�����o�֐�END-- ///
};