#pragma once

class Player {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Player* myInstance;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Player* GetInstance();

	// --�f�X�g���N�^-- //
	~Player();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	Player();

	/// --�����o�֐�END-- ///
};