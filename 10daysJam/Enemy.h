#pragma once

class Enemy {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Enemy* myInstance;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Enemy* GetInstance();

	// --�f�X�g���N�^-- //
	~Enemy();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	Enemy();

	/// --�����o�֐�END-- ///
};