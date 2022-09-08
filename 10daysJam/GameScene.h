#pragma once
#include "Input.h"
#include<list>
#include<vector>
#include "Util.h"
#include "Player.h"
#include "Enemy.h"
#include "JoyPadInput.h"
#include"Camera.h"

class GameScene {

	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static GameScene* myInstance;

	// --���̓N���X-- //
	Input* input;

	JoyPadInput* pad;

	// --�v���C���[�N���X-- //
	Player* player;

	// --�G�l�~�[-- //
	std::vector<Enemy> enemys;

	int spawnDelay;		//�G�̃X�|�[���x���̎c�莞��
	int delayMax;		//�G�̃X�|�[���ʒu���m�肵�Ă���X�|�[��������܂ł̎���
	int spawnInterval;	//���ɓG����������܂ł̊Ԋu
	int spawnTimer;		//�G�̔����^�C�}�[
	float enemyLength;	//�G���Z�j��̂ǂ��ŃX�|�[�����邩�̕ϐ� 
	Vector2 enemyPos;	//�m�肵���G�̃X�|�[���ʒu��ۑ�����p�ϐ�

	// --���x��-- //
	int level;

	// --�o���l-- //
	int point;

	// --�Z�j�̑��x-- //
	float hourHandSpeed;

	// --���v-- //
	Circle clock;

	// --���j-- //
	Line longHand;

	// --���j�̑��x-- //
	float longHandSpeed;

	// --�Z�j-- //
	Line hourHand;
	float reverseSpd = 4.0f;

	// --�^�񒆂̃��x����\�L����~-- //
	Circle levelCircle;

	// --���x���T�[�N���̐V�������a-- //
	float newCircleRadius;

	//�J����
	Camera camera;

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

	// --�v���C���[�ƃG�l�~�[�̓����蔻�菈��-- //
	void PlayerAndEnemyCol();

	// --�G�̃X�|�[������-- //
	void EnemySpawn();

	// --���x���X�V-- //
	void LevelUpdate();
	void LevelReset();

	/// <summary>
	/// �~�Ɖ~�̏Փ˔���
	/// </summary>
	/// <param name="cA"></param>
	/// <param name="cB"></param>
	/// <returns></returns>
	bool CollisionCtoC(Circle cA, Circle cB);

	/// <summary>
	/// �~�Ɛ��̏Փ˔���
	/// </summary>
	/// <param name="c"></param>
	/// <param name="l"></param>
bool CollisionCtoL(Circle c, Line l ,float lineSpd);

private:
	// --�R���X�g���N�^-- //
	GameScene();

	/// --�����o�֐�END-- ///
};