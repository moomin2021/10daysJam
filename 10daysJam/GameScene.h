#pragma once
#include "Input.h"
#include<vector>
#include "Util.h"
#include "Player.h"
#include "Enemy.h"
#include "JoyPadInput.h"
#include"Camera.h"
#include"BreakEffect.h"
#include"Particle.h"
#include"Star.h"
#include "Sound.h"

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

	// --�T�E���h�N���X-- //
	Sound* sound;

	// --�v���C���[�N���X-- //
	Player* player;

	// --�G�l�~�[-- //
	std::vector<Enemy> enemys;

	// --�G�t�F�N�g�̔z��-- //
	std::vector<BreakEffect> breakEffects;

	// --�J����-- //
	Camera camera;
#pragma endregion

//�I�[�v�j���O���o�n�̕ϐ�
	bool isOpening;
	int opEnemyMax = 5;
	std::vector<int> opSpawnFrame;
	int openingTime = 400; //8�b
	int animationTime = 250; //5�b
	int nowTime;

	//�`���[�g���A���̕ϐ�
	bool isTutorial;
	int tutorialEnemyMax;
	std::vector<Enemy> tutorialEnemy;
	bool isTutorialClear;
	int sceneChangeTime = 50;
	int sceneChangeTimer;


#pragma region �G�l�~�[�̃X�|�[���֌W�ϐ��̐錾
	
	// --���ɓG����������܂ł̊Ԋu-- //
	int spawnInterval;

	// --�G�̔����^�C�}�[-- //
	int spawnTimer;

	// --�G�̃X�|�[����-- //
	float enemySpawnRate;

	// --�G���Z�j��̂ǂ��ŃX�|�[�����邩�̕ϐ�-- //
	float enemyLength; 

	// --�G�����񂾐����J�E���g����ϐ�-- //
	int enemySandwichCount;

	// --�A�C�e�������񂾐����J�E���g����ϐ�-- //
	int itemSandwichCount;


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
	float hourHandReverseSpeed;

	float longHandReverseSpeed;

	//�@--�t���̑��x�{��
	float reverseVelocityScale;
	float reverseVelocityScaleLong;

	// --�t���̗�-- //
	float reverseTime;

	// --��]����p�[�e�B�N��-- //
	float starLen;
	Star star[5];
	Star star2[5];

	//�Z�j�A���j����ł�p�[�e�B�N��
	int lineParticleMax;
	std::vector<Particle> hourHandParticle;
	std::vector<Particle> longHandParticle;



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
	std::vector<Box> burstCircleEffects;
	std::vector<int> burstEffectColorParam;
	std::vector<int> burstEffectColor;

	// --���x�����ϓ��������̃G�t�F�N�g--
	std::vector<Particle> levelChangeParticle;
#pragma endregion

#pragma region �摜�p�n���h���ϐ��̐錾
	// --���v��j�̕`��p�摜-- //
	int whiteCircleGraph;

	// --�J�E���g-- //
	int countNumGraph[3];

	// --�p�[�e�B�N��--
	int particleGraph;

	// --�A�C�e��-- //
	int itemGraph[2];

	// --�G-- //
	int enemyGraph[2];

	// --�w�i-- //
	int backGroundGraph;
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
	void EnemySpawn(float radian);

	// --���x���X�V-- //
	void LevelUpdate();

	// --���x�������Z�b�g����-- //
	void LevelReset();

	// --�j�̔��]�͂𑝉�������֐�-- //
	void AddReversePower(int power);

	// --�Q�[�����J�n���ꂽ�Ƃ��̍X�V����--
	void OpeningUpdate();

	void LevelUpEfffect(int effectNum);

	void CreateBurstEffect(Circle burstRange , int effectNum);

	void UpdateTutorial();

	void DrawTutorial();

/// <summary>
/// ���j�̏Ռ��G�t�F�N�g�쐬�֐�
/// </summary>
void CreateBreakEffect(Vector2 pos ,int effectParam);

private:
	// --�R���X�g���N�^-- //
	GameScene();

	/// --�����o�֐�END-- ///
};