#pragma once
#include "Input.h"
#include<list>
#include<vector>
#include "Util.h"
#include "Player.h"

class GameScene {

	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static GameScene* myInstance;

	// --���̓N���X-- //
	Input* input;

	// --�v���C���[�N���X-- //
	Player* player;

	// --���v-- //
	Circle clock;

	// --���j-- //
	Line longHand;

	// --�Z�j-- //
	Line hourHand;

	// --�G�l�~�[--//
	std::list<Circle> enemys;
	float spawnDelay;	//�G�̔����̒x���x
	int spawnInterval;	//���ɓG����������܂ł̊Ԋu
	int spawnTimer;		//�G�̔����^�C�}�[

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