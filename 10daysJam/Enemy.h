#pragma once
#include <vector>
#include "Util.h"

class Enemy {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Enemy* myInstance;

	// --�G�l�~�[-- //
	std::vector<Circle> enemys;

	int spawnDelay;		//�G�̃X�|�[���x���̎c�莞��
	int delayMax;		//�G�̃X�|�[���ʒu���m�肵�Ă���X�|�[��������܂ł̎���
	int spawnInterval;	//���ɓG����������܂ł̊Ԋu
	int spawnTimer;		//�G�̔����^�C�}�[
	float enemyLength;	//�G���Z�j��̂ǂ��ŃX�|�[�����邩�̕ϐ� 
	Vector2 enemyPos;	//�m�肵���G�̃X�|�[���ʒu��ۑ�����p�ϐ�

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
	void Update(Line hourHand, Circle clock);

	// --�`�揈��-- //
	void Draw();

	void AllEnemyDeath();

private:
	// --�R���X�g���N�^-- //
	Enemy();

	/// --�����o�֐�END-- ///
};