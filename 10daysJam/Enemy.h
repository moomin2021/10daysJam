#pragma once
#include <vector>
#include "Util.h"
#include "Camera.h"
#include"BezireCurve.h"
#include"Particle.h"



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

	std::vector<Particle> spawnEffect;
	float spawnAddRadius;

	// --�摜�n���h��-- //
	int handle[2];

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
	void Draw(Camera camera_,int graph);

	// --�`��Ŏg���摜�n���h����ݒ�-- //
	void SetHandle(int handle[]);

	//���@�̉~�̃Z�b�^�[
	Circle GetCircle() const { return obj; }

	//�X�e�[�g�̃Z�b�^�[
	void SetState(State state_);

	//�X�e�[�g�̃Q�b�^�[
	State GetState()const { return state; }

	//�G�̃X�e�[�g�ύX�t���O�̃Q�b�^�[
	bool GetIsChange()const { return isChange;}

	//�X�e�[�g�`�F���W���s��ꂽ�Ƃ��ɍs���R�[���o�b�N�֐�
	void StateChange();

	//�X�|�[���������̃G�t�F�N�g
	void EffectInitialize(int color);

	//�I�u�W�F�N�g�̏��̃Z�b�^�[
	void SetObj(Circle obj_);

	//�G�l�~�[�����S�����Ƃ��ɌĂ΂��R�[���o�b�N�֐�
	void Death();


	//void AllEnemyDeath();

private:

	/// --�����o�֐�END-- ///
};