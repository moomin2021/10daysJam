#pragma once
#include "Input.h"
#include<list>
#include<vector>
#include "Util.h"

class GameScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static GameScene* myInstance;

	// --���̓N���X-- //
	Input* input;

	// --���v-- //
	Circle clock;

	// --�v���C���[-- //
	Circle player;
	float playerPos;	//���@�̐j�̏�ł̏���

	// --���j-- //
	Line longHand;

	// --�Z�j-- //
	Line hourHand;

	// --�G�l�~�[--//
	std::list<Circle> enemys;
	float spawnDelay;	//�G�̔����̒x���x
	int spawnInterval;	//���ɓG����������܂ł̊Ԋu
	int spawnTimer;		//�G�̔����^�C�}�[

	// --�v���C���[�̑��x-- //
	float playerSpd = 2.0f;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static GameScene* GetInstance();

	// --�f�X�g���N�^-- //
	~GameScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	GameScene();

	/// --�����o�֐�END-- ///
};