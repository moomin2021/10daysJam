#pragma once
#include <vector>
#include "Util.h"

class Enemy {
	/// --�����o�ϐ�-- ///
public:
	// --�G�l�~�[-- //
	Circle enemy;

private:

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�R���X�g���N�^-- //
	Enemy();
	Enemy(Vector2 pos, float radius);

	// --�f�X�g���N�^-- //
	~Enemy();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	//void AllEnemyDeath();

private:

	/// --�����o�֐�END-- ///
};