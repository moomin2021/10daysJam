#pragma once
#include "Input.h"
#include<vector>
#include "Util.h"
#include "Player.h"
#include "Enemy.h"
#include "JoyPadInput.h"
#include"Camera.h"
#include"BreakEffect.h"

class GameScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static GameScene* myInstance;

#pragma region �N���X�錾
	// --���̓N���X-- //
	Input* input;

	// --�R���g���[���[�N���X-- //
	JoyPadInput* pad;

	// --�v���C���[�N���X-- //
	Player* player;

	// --�G�l�~�[-- //
	std::vector<Enemy> enemys;

	// --�G�t�F�N�g�̔z��-- //
	std::vector<BreakEffect> breakEffects;

	// --�J����-- //
	Camera camera;
#pragma endregion

#pragma region �G�l�~�[�̃X�|�[���֌W�ϐ��̐錾
	// --�G�̃X�|�[���ʒu���m�肵�Ă���X�|�[��������܂ł̎���-- //
	int delayMax;
	
	// --���ɓG����������܂ł̊Ԋu-- //
	int spawnInterval;

	// --�G�̃X�|�[���x���̎c�莞��-- //
	int spawnDelay;

	// --�G�̔����^�C�}�[-- //
	int spawnTimer;

	// --�G�̃X�|�[����-- //
	float enemySpawnRate;

	// --�G���Z�j��̂ǂ��ŃX�|�[�����邩�̕ϐ�-- //
	float enemyLength; 

	// --�m�肵���G�̃X�|�[���ʒu��ۑ�����p�ϐ�-- //
	Vector2 enemyPos;
#pragma endregion

#pragma region ���v�֌W�ϐ��̐錾
	// --���v-- //
	Circle clock;

	// --���j-- //
	Line longHand;

	// --���j�̑��x-- //
	float longHandSpeed;

	// --�Z�j-- //
	Line hourHand;

	// --�Z�j�̑��x-- //
	float hourHandSpeed;

	// --���x���ɂ��Z�j�̑��x�̏オ�蕝-- //
	float hourHandlevelSpeed;

	// --�Z�j���t��肷��Ƃ��̑��x-- //
	float reverseSpeed;
#pragma endregion

#pragma region ���x���֌W�ϐ��̐錾
	// --�^�񒆂̃��x����\�L����~-- //
	Circle levelCircle;

	// --���x���T�[�N���̐V�������a-- //
	float newCircleRadius;

	// --���x��-- //
	int level;

	// --�o���l-- //
	int point;

	// --���x���ɂ���ĕK�v�Ȍo���l-- //
	int needPoint[10];

#pragma endregion

#pragma region �G�t�F�N�g�֌W�ϐ��̐錾
	// --�G�̔��������Ƃ��̉~�̑傫���p-- //
	Circle burstCircle;
#pragma endregion

#pragma region �摜�p�n���h���ϐ��̐錾
	// --���v��j�̕`��p�摜-- //
	int whiteCircleGraph;
#pragma endregion

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static GameScene* GetInstance();

	// --�C���X�^���X���-- //
	void Relese();

	// --�f�X�g���N�^-- //
	~GameScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	// --�Q�[���V�[���N���X�ōs�������蔻������ׂď�������-- //
	void Collision();

	// --�G�̃X�|�[������-- //
	void EnemySpawn();

	// --���x���X�V-- //
	void LevelUpdate();

	// --���x�������Z�b�g����-- //
	void LevelReset();

/// <summary>
/// ���j�̏Ռ��G�t�F�N�g�쐬�֐�
/// </summary>
void CreateBreakEffect(Vector2 pos ,int effectParam);

private:
	// --�R���X�g���N�^-- //
	GameScene();

	/// --�����o�֐�END-- ///
};