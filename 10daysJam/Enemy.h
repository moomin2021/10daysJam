#pragma once
#include <vector>
#include "Util.h"
#include "Camera.h"

class Enemy {
	/// --�����o�ϐ�-- ///
public:
	// --�G�l�~�[-- //
	Circle enemy;


private:

	//�X�e�[�g
	State state = State::Normal;

	int color = 0xffff00;

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
	void Update(Line hourLine_);

	//�ʏ��Ԃ̍X�V����
	void UpdateNormal();

	//���]��Ԃ̍X�V����
	void UpdateReverse(Line hourLine_);

	//�Փˌ��m�ǐ�
	void OnCollison();

	// --�`�揈��-- //
	void Draw(Camera camera_);

	Circle GetCircle() const { return enemy; }

	//void AllEnemyDeath();

private:

	/// --�����o�֐�END-- ///
};