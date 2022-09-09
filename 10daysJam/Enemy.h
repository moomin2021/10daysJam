#pragma once
#include <vector>
#include "Util.h"
#include "Camera.h"
#include"BezireCurve.h"

class Enemy {
	/// --�����o�ϐ�-- ///
public:
	// --�G�l�~�[-- //
	Circle obj;


private:

	//�X�e�[�g
	State state = State::Normal;

	int color;

	bool isChange = false;	//�X�e�[�g�̕ύX���s��ꂽ��

	BezireCurve bezire;
	int effectTime = 0;

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
	
	//���S��Ԃ̍X�V����
	void UpdateDeath(Vector2 afterPos,float randParam);

	//�Փˌ��m�ǐ�
	void OnCollison();

	// --�`�揈��-- //
	void Draw(Camera camera_);

	Circle GetCircle() const { return obj; }

	void SetState(State state_);

	State GetState()const { return state; }

	bool GetIsChange()const { return isChange;}

	void StateChange();

	//void AllEnemyDeath();

private:

	/// --�����o�֐�END-- ///
};