#include "GameScene.h"
#include "SceneManager.h"
#include "Score.h"
using namespace Util;
using namespace std;

// --�C���X�^���X��NULL����-- //
GameScene* GameScene::myInstance = nullptr;

bool GameScene::isTutorialSkip = false;

// --�C���X�^���X�ǂݍ���-- //
GameScene* GameScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new GameScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�C���X�^���X���-- 
void GameScene::Relese() {
	// --�C���X�^���X�����������牽�������ɏI������-- //
	if (myInstance == nullptr) return;

	// --�C���X�^���X���-- //
	delete myInstance;
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
GameScene::GameScene() {
#pragma region �C���X�^���X�ǂݍ���
	// --�L�[�{�[�h�N���X-- //
	input = Input::GetInstance();

	// -�R���g���[���[�N���X-- //
	pad = JoyPadInput::GetInstance();

	// --�T�E���h-- //
	sound = Sound::GetInstance();

	// --�v���C���[�N���X-- //
	player = Player::GetInstance();
#pragma endregion

#pragma region �G�l�~�[�̃X�|�[���֌W�ϐ��̏�����

	// --���ɓG����������܂ł̊Ԋu-- //
	spawnInterval = 20;

	// --�G�̔����^�C�}�[-- //
	spawnTimer = spawnInterval;

	// --�G���Z�j��̂ǂ��ŃX�|�[�����邩�̕ϐ�-- //
	enemyLength = 0.0f;

	// --�m�肵���G�̃X�|�[���ʒu��ۑ�����p�ϐ�-- //
	enemyPos = { 0.0f, 0.0f };
#pragma endregion

#pragma region ���v�֌W�ϐ��̏�����
	// --���v-- //
	clock = { {640.0f, 480.0f}, 416.0f };

	// --���j-- //
	longHand = { {640.0f, 480.0f}, {640.0f, 0.0f}, clock.radius, 0.0f, 0xFF0000 };

	// --���j�̑��x-- //
	longHandSpeed = 0.1f;

	// --���j�̑��x�̒ǉ��l-- //
	addHandSpeed = 0.01f;

	// --�Z�j-- //
	hourHand = { {640.0f, 480.0f}, {640.0f, 32.0f}, clock.radius - 32.0f, 0, 0xFF };

	// --�Z�j�̑��x-- //
	hourHandSpeed = 0.8f;

	// --���x���ɂ��Z�j�̑��x�̏オ�蕝-- //
	hourHandlevelSpeed = 0.5f;

	// --�Z�j���t��肷��Ƃ��̑��x-- //
	hourHandReverseSpeed = 4.0f;
#pragma endregion

#pragma region ���x���֌W�ϐ��̏�����
	// --�^�񒆂̃��x����\�L����~-- //
	levelCircle = { {640.0f, 480.0f}, 78.0f };

	// --���x���T�[�N���̐V�������a-- //
	newCircleRadius = 0.0f;

	// --���x��-- //
	level = 0;

	// --�o���l-- //
	point = 0;

	// --���x���ɂ���ĕK�v�Ȍo���l-- //
	int needPointCopy[10] = { 2, 2, 3, 4, 5, 10, 10, 10, 10, 10 };
	for (int i = 0; i < 10; i++) { needPoint[i] = needPointCopy[i]; }
#pragma endregion

#pragma region �G�t�F�N�g�֌W�ϐ��̏�����
	// --�G�̔��������Ƃ��̉~�̑傫���p-- //
	burstCircle = { {0.0f, 0.0f}, 0.0f };
#pragma endregion

#pragma region �摜�ǂݍ���
	// --���v��j�̕`��p�摜-- //
	whiteCircleGraph = LoadGraph("Resources/whiteCircle.png");

	// --�J�E���g-- //
	LoadDivGraph("Resources/countNum.png", 3, 3, 1, 102, 135, countNumGraph);

	particleGraph = LoadGraph("Resources/particle.png");
	particleGraph = whiteCircleGraph;

	// --�A�C�e��-- //
	LoadDivGraph("Resources/Item.png", 2, 2, 1, 48, 48, itemGraph);

	// --�G-- //
	LoadDivGraph("Resources/Enemy.png", 2, 2, 1, 48, 48, enemyGraph);

	// --�w�i-- //
	backGroundGraph = LoadGraph("Resources/backillust.png");

	//UI
	LoadDivGraph("Resources/controller_button.png", 3, 3, 1, 82, 82, ButtonGraph);
	LoadDivGraph("Resources/playUI.png", 4, 4, 1, 190, 190, gameUIGraph);
	LoadDivGraph("Resources/playUIBoard.png", 2, 2, 1, 234, 234, gameUIBoardGraph);

	//�`���[�g���A���֌W
	tutorialTextGraph[0] = LoadGraph("Resources/tutorial_move.png");
	tutorialTextGraph[1] = LoadGraph("Resources/tutorial_enemy.png");
	tutorialTextGraph[2] = LoadGraph("Resources/tutorial_return.png");
	LoadDivGraph("Resources/gamerule.png", 2, 2, 1, 344, 72, gameRuleGraph);
	LoadDivGraph("Resources/tutorialBoard.png", 2, 2, 1, 382, 112, tutorialBoardGraph);
	LoadDivGraph("Resources/skipUI.png", 3, 3, 1, 227, 54, skipGraph);

	successGraph = LoadGraph("Resources/success.png");

	//���]�{�^��
	LoadDivGraph("Resources/returnUI.png", 2, 2, 1, 58, 58, returnButton);
	returnButton[0] = LoadGraph("Resources/LB.png");

	// --���x���T�[�N��-- //
	LoadDivGraph("Resources/levelCircle.png", 2, 2, 1, 160, 160, levelCircleGraph);

	// --���x���\�L-- //
	LoadDivGraph("Resources/levelNumbers.png", 6, 6, 1, 160, 160, levelGraph);

	// --���v�̘g-- //
	clockGraph = LoadGraph("Resources/clock.png");

	//���^�b�N���o
	LoadDivGraph("Resources/titleRogo.png", 2, 2, 1, 572, 572, retuckGraph);

	//���񂾉��o
	LoadDivGraph("Resources/value.png", 3, 3, 1, 212, 46, sandwichEffectGraph);

	tutorialFontGraph = LoadGraph("Resources/tutorial.png");

	finishGraph = LoadGraph("Resources/gameFinish.png");

#pragma endregion

	// --�V�[����؂�ւ���܂ł̎���-- //
	Time = 120;
	Timer = 0;
	isSceneChange = false;
}

// --�f�X�g���N�^-- //
GameScene::~GameScene() {
#pragma region �N���X�̃C���X�^���X���
	player->Relese();
#pragma endregion
}

// --����������-- //
void GameScene::Initialize() {
	// --�A�C�e���E�G�폜-- //
	enemys.clear();

	// --�G�t�F�N�g�폜-- //
	breakEffects.clear();

	// --�Z�j�A���j����ł�p�[�e�B�N���폜-- //
	hourHandParticle.clear();
	longHandParticle.clear();

	// --�G�̔��������Ƃ��̉~�̑傫���p�폜-- //
	burstCircleEffects.clear();
	burstEffectColorParam.clear();
	burstEffectColor.clear();

	// --�v���C���[-- //
	player->Initialize();

#pragma region �G�l�~�[�̃X�|�[���֌W�ϐ��̏�����

	// --���ɓG����������܂ł̊Ԋu-- //
	spawnInterval = 20;

	// --�G�̔����^�C�}�[-- //
	spawnTimer = spawnInterval;

	// --�G���Z�j��̂ǂ��ŃX�|�[�����邩�̕ϐ�-- //
	enemyLength = 0.0f;

	// --�m�肵���G�̃X�|�[���ʒu��ۑ�����p�ϐ�-- //
	enemyPos = { 0.0f, 0.0f };
#pragma endregion

#pragma region ���v�֌W�ϐ��̏�����
	// --���v-- //
	clock = { {640.0f, 480.0f}, 416.0f };

	// --���j-- //
	longHand = { {640.0f, 480.0f}, {640.0f, 0.0f}, clock.radius, 0.0f, 0xFF0000 };

	// --���j�̑��x-- //
	longHandSpeed = 0.1f;

	// --���j�̑��x�̒ǉ��l-- //
	addHandSpeed = 0.03f;

	// --�Z�j-- //
	hourHand = { {640.0f, 480.0f}, {640.0f, 32.0f}, clock.radius - 32.0f, 0, 0xFF };

	// --�Z�j�̑��x-- //
	hourHandSpeed = 0.8f;

	// --���x���ɂ��Z�j�̑��x�̏オ�蕝-- //
	hourHandlevelSpeed = 0.5f;

	// --�Z�j���t��肷��Ƃ��̑��x-- //
	hourHandReverseSpeed = 4.0f;
#pragma endregion

#pragma region ���x���֌W�ϐ��̏�����
	// --�^�񒆂̃��x����\�L����~-- //
	levelCircle = { {640.0f, 480.0f}, 78.0f };

	// --���x���T�[�N���̐V�������a-- //
	newCircleRadius = 0.0f;

	// --���x��-- //
	level = 0;

	// --�o���l-- //
	point = 0;

	// --���x���ɂ���ĕK�v�Ȍo���l-- //
	int needPointCopy[10] = { 2, 2, 3, 4, 5, 10, 10, 10, 10, 10 };
	for (int i = 0; i < 10; i++) { needPoint[i] = needPointCopy[i]; }
#pragma endregion

#pragma region �G�t�F�N�g�֌W�ϐ��̏�����
	// --�G�̔��������Ƃ��̉~�̑傫���p-- //
	burstCircle = { {0.0f, 0.0f}, 0.0f };
#pragma endregion
	Timer = 0;
	isSceneChange = false;

	lineParticleMax = 64;
	for (int i = 0; i < lineParticleMax; i++) {
		Particle newParticle;
		/*Vector2 pos;
		pos.x = Random(hourHand.start.x + levelCircle.radius, hourHand.end.x);
		pos.y = Random(hourHand.start.y + levelCircle.radius, hourHand.end.y);*/
		//newParticle.SetParent(hourHand.start);
		newParticle.SetState(ParticleState::Endress);
		newParticle.Initialize();
		hourHandParticle.push_back(newParticle);
		longHandParticle.push_back(newParticle);
	}

	if (isTutorialSkip == true) {
		isTutorial = true;
		isTutorialClear = true;
		level = 0;
		sceneChangeTime = 75;
		sceneChangeTimer = sceneChangeTime;
	}
	else {
		isTutorial = true;
		isTutorialClear = false;
		level = 1;
		tutorialStep = 0;
		sceneChangeTime = 75;
		sceneChangeTimer = sceneChangeTime;
		for (int i = 0; i < 3; i++) {
			enemySpawnRate = 0;
			EnemySpawn(Random(0.0f, 36.0f) + 36.0f + 108.0f * i);
		}
	}

	//�G�̃X�|�[�����Ԃ̃u��
	opSpawnFrame.clear();
	for (int i = 0; i < opEnemyMax; i++) {
		//�G�̃X�|�[���t���[���������_����
		int spawnFrame;
		spawnFrame = 30 + i * 50;
		opSpawnFrame.push_back(spawnFrame);
	}

	graphRad = 0;
}

// --�X�V����-- //
void GameScene::Update() {

	if (isSceneChange == false) {

#pragma region �j�̍��W�v�Z

		//�`���[�g���A������
		if (isTutorial) {
			UpdateTutorial();
		}
		//�I�[�v�j���O����
		else if (isOpening) {
			OpeningUpdate();
		}
		else {
			//L�{�^���ŒZ�j�̃X�e�[�g���u���]�v��
			if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::Normal && level > 0) {
				hourHand.state = State::Reverse;
			}

			//�t���̑��x�͒Z�j�̑��x * ���x�{����
			hourHandReverseSpeed = (hourHandSpeed + hourHandlevelSpeed * (level - 1)) * reverseVelocityScale;

			//�X�e�[�g���ʏ�Ȃ�Z�j�͎�����]
			if (hourHand.state == State::Normal) {
				hourHand.radian += hourHandSpeed + hourHandlevelSpeed * (level - 1);

				//�C�ӂ̃L�[�ŒZ�j�𓮂���(�f�o�b�O�p)
				//hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
			}//�X�e�[�g�����]���Ă���Ȃ�Z�j���t��������
			else if (hourHand.state == State::Reverse) {
				hourHand.radian -= hourHandReverseSpeed;
				//�Z�j�����j�ɒǂ������璷�j�̃X�e�[�g���u���]�v��
				if (hourHand.radian < longHand.radian + hourHandReverseSpeed && hourHand.radian > longHand.radian - hourHandReverseSpeed) {
					longHand.state = State::Reverse;
					//�Z�j�̃X�e�[�g���Ƃ߂�
					hourHand.state = State::Stop;

					// --���j�̑��x��ύX-- //
					longHandSpeed += addHandSpeed;

					// --�Z�j�̑��x��ύX-- //
					hourHandSpeed += addHandSpeed * 2;

					//�͂��񂾃I�u�W�F�N�g�̐��Ŗ߂��͂𑝂₷
					reverseTime += level * 3;
					reverseTime += ((enemySandwichCount + itemSandwichCount) / 2);

					//�X�R�A�����Z�A�͂��񂾐������Z�b�g
					int sandwichCount = itemSandwichCount + enemySandwichCount;
					int multiSand = 0;
					if (sandwichCount <= 10)
					{
						multiSand = 1;

					}
					if (sandwichCount >= 11 && sandwichCount <= 20)
					{
						multiSand = 2;
					}
					if (sandwichCount >= 21 && sandwichCount <= 30)
					{
						multiSand = 4;
						sandwichValue = GOOD;
						sandwichEffectTimer = 25;
						//���W�v�Z
						sandwichEffectPos.x = (hourHand.length / 2.0f) * cosf((hourHand.radian - 45) / 180 * PI) + clock.pos.x;
						sandwichEffectPos.y = (hourHand.length / 2.0f) * sinf((hourHand.radian - 45) / 180 * PI) + clock.pos.y;
					}
					if (sandwichCount >= 31 && sandwichCount <= 40)
					{
						multiSand = 6;
						sandwichValue = GREAT;
						sandwichEffectTimer = 25;
						sandwichEffectPos.x = (hourHand.length / 2.0f) * cosf((hourHand.radian - 45) / 180 * PI) + clock.pos.x;
						sandwichEffectPos.y = (hourHand.length / 2.0f) * sinf((hourHand.radian - 45) / 180 * PI) + clock.pos.y;
					}
					if (sandwichCount >= 50)
					{
						multiSand = 8;
						sandwichValue = EXCELLENT;
						sandwichEffectTimer = 25;
						sandwichEffectPos.x = (hourHand.length / 2.0f) * cosf((hourHand.radian - 45) / 180 * PI) + clock.pos.x;
						sandwichEffectPos.y = (hourHand.length / 2.0f) * sinf((hourHand.radian - 45) / 180 * PI) + clock.pos.y;
					}

					Score::AddScore(100 * itemSandwichCount * multiSand);
					Score::AddScore(500 * enemySandwichCount * multiSand);
					itemSandwichCount = 0;
					enemySandwichCount = 0;

					//���j�̋t�����x���v�Z
					longHandReverseSpeed = hourHandReverseSpeed * reverseVelocityScaleLong;
					//���x�����Z�b�g
					LevelReset();



					//�͂��񂾏u�Ԃɂ͂��܂�Ă���G�����ł�����
					for (int i = enemys.size() - 1; i >= 0; i--) {
						if (enemys[i].GetState() == State::Reverse) {
							enemys[i].Death();
						}
					}
				}
			}

			//�X�e�[�g���ʏ�Ȃ璷�j�͎�����]
			if (longHand.state == State::Normal) {
				longHand.radian += longHandSpeed;
			}//�X�e�[�g���u���]�v���A���]����͂��܂��c���Ă���Ȃ�t��
			else if (longHand.state == State::Reverse) {
				if (reverseTime > 0) {
					//���x�͒Z�j�Ɠ���
					longHand.radian -= longHandReverseSpeed;
					//���j�̊p�x��0�ɂȂ����璷�j�ƒZ�j�̃X�e�[�g��߂��A�p�x��������(���j�̂�)
					if (longHand.radian < hourHandReverseSpeed) {
						longHand.state = State::Normal;
						hourHand.state = State::Normal;
						longHand.radian = 0;
						//�X�e�[�g���f�X�łȂ��G�͍폜�A�f�X�͂��̂܂�
						for (int i = enemys.size() - 1; i >= 0; i--) {
							if (enemys[i].GetState() != State::Death) {
								enemys.erase(enemys.begin() + i);
							}
						}
						//���x�����Z�b�g
						LevelReset();
						// --�X�R�A���Z-- //
						Score::AddScore(1000);
						//�V�F�C�N
						camera.SetShakeCount(10);
						//�G�̃X�|�[���^�C�}�[�����Z�b�g
						spawnTimer = spawnInterval;
						//�Ռ��G�t�F�N�g���쐬
						CreateBreakEffect(clock.pos, 128);
						//���x���A�b�v�G�t�F�N�g���쐬(�Y��Ȃ̂�)
						LevelUpEfffect(64 * 3);
						//�^�C�g�����S�̕`�掞�ԃ��Z�b�g
						retuckEffectTimer = 30;
						//�߂��͂����Z�b�g
						reverseTime = 0;
						//�T�E���h�Đ�
						//�T�E���h�Đ�
						sound->PlaySE(SANDSE);
						//�G��5�̃X�|�[��������
						for (int i = 0; i < 5; i++) {
							EnemySpawn(Random(0.0f, 72.0f) + 72.0f * i);
						}

					}
					//���]���x�̌��Z
					reverseTime--;
				}//�߂��͂��Ȃ��Ȃ�����X�e�[�g���m�[�}���ɖ߂�
				else if (reverseTime <= 0) {
					longHand.state = State::Normal;
					hourHand.state = State::Normal;
					//�G�̃X�|�[���^�C�}�[�����Z�b�g
					spawnTimer = spawnInterval;

					//�G��5�̃X�|�[��������
					for (int i = 0; i < 5; i++) {
						EnemySpawn(Random(0.0f, 72.0f) + 72.0f * i);
					}
				}
			}

			//360�x��������0�ɖ߂��A0�����������360���Z����
			hourHand.radian = fmodf(hourHand.radian, 360.0f);
			if (hourHand.radian <= 0)hourHand.radian += 360.0f;

			//�ʒu�������`��p�̃��W�A���錾
			float radL = longHand.radian - 90;
			float radH = hourHand.radian - 90;

			//�j�̊p�x�ŏI�_���W���v�Z
			longHand.end.x = (longHand.length * cosf(radL / 180 * PI)) + clock.pos.x;
			longHand.end.y = (longHand.length * sinf(radL / 180 * PI)) + clock.pos.y;
			//�j�̊p�x�ŏI�_���W���v�Z
			hourHand.end.x = (hourHand.length * cosf(radH / 180 * PI)) + clock.pos.x;
			hourHand.end.y = (hourHand.length * sinf(radH / 180 * PI)) + clock.pos.y;

			// --���j����������烊�U���g
			if (longHand.radian >= 360.0f) {
				isSceneChange = true;
			}

#pragma endregion

#pragma region �v���C���[�X�V����
			player->Update(hourHand, clock, levelCircle.radius);
#pragma endregion

#pragma region �G�l�~�[�֌W�̏���
			// --�G�l�~�[�̃X�|�[������-- //
			//�Z�j���ʏ��ԂȂ�s��
			if (hourHand.state == State::Normal) {
				//�X�|�[���^�C�}�[�����炷
				if (spawnTimer > 0) {
					spawnTimer--;
					//�^�C�}�[��0�ɂȂ�����X�|�[���ʒu�����߂�
				}
				else if (spawnTimer == 0) {

					EnemySpawn(hourHand.radian - 5);
					//�^�C�}�[�����Z�b�g
					spawnTimer = spawnInterval;
				}
			}



			// --�G�l�~�[�N���X�X�V����-- //
			for (int i = enemys.size() - 1; i >= 0; i--) {
				Vector2 scorePos = { 1200,60 };
				//DrawCircle({ scorePos,32 }, 0xffffff, true);
				enemys[i].Update(hourHand, scorePos);
				//�Z�j�����]���[�h�Ȃ画����Ƃ�
				if (hourHand.state == State::Reverse) {
					//�Z�j�ƓG�̓����蔻��
					if (CollisionCtoL(enemys[i].GetCircle(), hourHand, hourHandReverseSpeed)) {
						//�I�u�W�F�N�g�̃X�e�[�g���܂��u���]�v�łȂ��A����ł����Ȃ��Ȃ瓖���蔻��̃R�[���o�b�N�֐����Ăяo���A���񂾐����J�E���g����
						if (enemys[i].GetState() != State::Reverse && enemys[i].GetState() != State::Death) {
							if (enemys[i].GetState() == State::Item) {
								itemSandwichCount++;
							}
							else if (enemys[i].GetState() == State::Enemy) {
								enemySandwichCount++;
							}

							enemys[i].OnCollison();
						}
					}
				}

				//���j���m�[�}�����[�h�Ȃ画����Ƃ�
				if (longHand.state == State::Normal) {
					//���j�ƓG�̓����蔻��
					if (CollisionCtoL(enemys[i].GetCircle(), longHand, longHandSpeed)) {
						//��x���X�e�[�g�ύX���s���Ă��Ȃ��Ȃ�
						if (!enemys[i].GetIsChange()) {
							//�G�̏�Ԃ��A�C�e���Ȃ�G��
							if (enemys[i].GetState() == State::Item) {
								enemys[i].SetState(State::Enemy);
								enemys[i].SetHandle(enemyGraph);
							}//�G�Ȃ�A�C�e����
							else if (enemys[i].GetState() == State::Enemy) {
								enemys[i].SetState(State::Item);
								enemys[i].SetHandle(itemGraph);
							}
							enemys[i].StateChange();
						}
					}
				}

				//�����~�Ƃ̓����蔻��
				if (CollisionCtoC(enemys[i].GetCircle(), burstCircle)) {
					//���������A�C�e��������
					enemys[i].SetState(State::Delete);
				}

				for (int i = burstCircleEffects.size() - 1; i >= 0; i--) {
					//�o�[�X�g�T�[�N���̐F�𗎂Ƃ�
					burstEffectColorParam[i] -= Random(-5, 15);
					if (burstEffectColorParam[i] <= 0) {
						burstEffectColorParam.erase(burstEffectColorParam.begin() + i);
						burstEffectColor.erase(burstEffectColor.begin() + i);
						burstCircleEffects.erase(burstCircleEffects.begin() + i);
					}
				}

				if (enemys[i].GetState() == State::Delete) {
					enemys.erase(enemys.begin() + i);
				}
			}
#pragma endregion

#pragma region �G�t�F�N�g����
			//�@--�����~�̍��W���Z�b�g-- //
			burstCircle = { {0.0f,0.0f}, 0.0f };

			//�G�t�F�N�g�X�V����
			for (int i = 0; i < breakEffects.size(); i++) {
				breakEffects[i].Update();
				//�����t���O��false�Ȃ�Y���v�f������
				if (!breakEffects[i].GetAllive()) {
					breakEffects.erase(breakEffects.begin() + i);
				}
			}

			for (int i = 0; i < 5; i++) {
				star[i].Update(hourHand);
				//star2[i].SetSpd(0.8f);
				star2[i].Update(hourHand);
				//if(star[i].)
			}

			for (int i = 0; i < lineParticleMax; i++) {
				Vector2 pos;
				float len, rad;
				len = Random(levelCircle.radius, hourHand.length);
				rad = hourHand.radian - 90.0f;
				pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
				pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
				hourHandParticle[i].SetParent(pos);
				hourHandParticle[i].SetSpeed(Random(0.0f, 0.2f));
				hourHandParticle[i].SetRadius(Random(3.0f, 6.0f));
				hourHandParticle[i].Update();

				len = Random(levelCircle.radius, longHand.length);
				rad = longHand.radian - 90.0f;
				pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
				pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
				longHandParticle[i].SetParent(pos);
				longHandParticle[i].SetSpeed(Random(0.5f, 2.0f));
				hourHandParticle[i].SetRadius(Random(1.0f, 3.0f));
				longHandParticle[i].SetRadian(Random(rad - 135, rad - 45));
				longHandParticle[i].Update();
			}

			for (int i = levelChangeParticle.size() - 1; i >= 0; i--) {
				Vector2 pos;
				float len, rad;
				len = longHand.length;
				rad = Random(0.0f, 360.0f);
				pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
				pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
				levelChangeParticle[i].SetParent(pos);
				levelChangeParticle[i].SetSpeed(Random(3.0f, 8.0f));
				levelChangeParticle[i].SetRadius(Random(6.0f, 10.0f));
				//levelChangeParticle[i].SetRadian(Random(rad - 60, rad + 60));
				//levelChangeParticle[i].SetRadian(rad);
				levelChangeParticle[i].Update();
				//�A�N�e�B�u����Ȃ��Ȃ��������
				if (!levelChangeParticle[i].GetActive()) {
					levelChangeParticle.erase(levelChangeParticle.begin() + i);
				}
			}

			//�^�C�g�����S���o�̎��Ԍ��炷
			if (retuckEffectTimer > 0) {
				retuckEffectTimer--;
			}

			//���񂾃G�t�F�N�g�̎��Ԃ����炷
			if (sandwichEffectTimer > 0) {
				sandwichEffectTimer--;
			}

#pragma endregion

#pragma region �J�����V�F�C�N����
			camera.CameraShake();
#pragma endregion

#pragma region �Q�[���V�[���̓����蔻�菈��
			Collision();
#pragma endregion

#pragma region ���x���̍X�V����
			LevelUpdate();
#pragma endregion

		graphRad += 4.0f;
		if (graphRad > 360.0f) {
			graphRad -= 360.0f;
		}


#pragma region �f�o�b�O�p����
			if (SceneManager::GetDebugMode() == true) {
				// --���x���T�[�N���̔��a�ύX-- //
				levelCircle.radius += input->IsPress(KEY_INPUT_A) - input->IsPress(KEY_INPUT_D);

				// --���x���T�[�N���̔��a����-- //
				levelCircle.radius = Clamp(levelCircle.radius, 300.0f, 8.0f);

				// --�Z�j�̑��x�ύX-- //
				hourHandSpeed += (input->IsTrigger(KEY_INPUT_Z) - input->IsTrigger(KEY_INPUT_C)) * 0.1f;

				// --���j�̑��x�ύX-- //
				longHandSpeed += (input->IsTrigger(KEY_INPUT_I) - input->IsTrigger(KEY_INPUT_P)) * 0.1f;

				// --SPACE�L�[�������Ɖ�ʂ��V�F�C�N����-- //
				if (input->IsTrigger(KEY_INPUT_SPACE)) { camera.SetShakeCount(5); }

				// --S�L�[�������ƃX�R�A��������-- //
				if (input->IsTrigger(KEY_INPUT_S)) Score::AddScore(10000);
			}
#pragma endregion
		}
	}

	if (isSceneChange == true) {
		Timer++;
		if (Timer >= Time) {
			// --�V�[����ς���-- //
			SceneManager::SetScene(RESULTSCENE);
		}
	}
}

// --�`�揈��-- //
void GameScene::Draw() {
	if (isTutorial) {
		DrawTutorial();
	}
	else {

		// --�w�i�`��-- //
		DrawGraph(0, 0, backGroundGraph, true);

		//���ݎ��Ԃ��Q�Ƃ��ă��C�g�A�b�v
		int brightLongHand = 0;
		brightLongHand = (256.0f / 25.0f) * (nowTime - 175) + 16.0f;
		int brightClock = 0;
		brightClock = (256.0f / 25.0f) * (nowTime - 125) + 16.0f;
		int brightHourHand = 0;
		brightHourHand = (256.0f / 25.0f) * (nowTime - 75) + 16.0f;

#pragma region �v���C���[�`��
		player->Draw(camera, brightHourHand);
#pragma endregion

#pragma region �G�l�~�[�`��
		for (int i = 0; i < enemys.size(); i++) {
			enemys[i].Draw(camera, particleGraph);
		}

#pragma endregion

#pragma region ���v�̊O�g�̕`��
		// --���v�̊O�g�̍��W�ƃJ�����V�F�C�N�̍��W������Circle�ϐ�-- //
		Circle clockCircle = { clock.pos + camera.GetPos(), clock.radius };

		SetDrawBlendMode(DX_BLENDMODE_ADD, brightClock);
		Color color = HexadecimalColor(LIGHTBLUE);
		SetDrawBright(color.red, color.green, color.blue);
		for (int i = 0; i < 20; i++) {
			DrawRotaGraph(640 + camera.GetPos().x, 480 + camera.GetPos().y, 1.0f, 0.0f, clockGraph, true);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

		//�j�̃p�[�e�B�N���̕`��
		SetDrawBlendMode(DX_BLENDMODE_ADD, (256) * (!isOpening));
		for (int i = 0; i < lineParticleMax; i++) {
			hourHandParticle[i].Draw(camera, PURPLE, particleGraph);
			longHandParticle[i].Draw(camera, EFFECT_GREEN, particleGraph);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);

#pragma region ���j�̕`��
		// --���j�̍��W�ƃJ�����V�F�C�N�̍��W������Line�ϐ�-- //
		Line longHandLine;
		longHandLine.start = { longHand.start + camera.GetPos() };
		longHandLine.end = { longHand.end + camera.GetPos() };
		longHandLine.color = longHand.color;

		SetDrawBlendMode(DX_BLENDMODE_ADD, brightLongHand);
		//etDrawBright(119, 28, 28);
		Color c;
		c = HexadecimalColor(GREEN);
		SetDrawBright(c.red, c.green, c.blue);
		// --���j�̕`��-- //
		for (int i = 0; i < longHand.length * 1.3f; i++) {
			DrawRotaGraph(
				longHandLine.start.x + cosf(Degree2Radian(longHand.radian - 90)) * (levelCircle.radius + i * 0.8f / 1.3f),
				longHandLine.start.y + sinf(Degree2Radian(longHand.radian - 90)) * (levelCircle.radius + i * 0.8f / 1.3f),
				0.5f, 0.0f, whiteCircleGraph, true);
		}

		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

#pragma region �Z�j�̕`��
		// --�Z�j�̍��W�ƃJ�����V�F�C�N�̍��W������Line�ϐ�-- //
		Line hourHandLine;
		hourHandLine.start = { hourHand.start + camera.GetPos() };
		hourHandLine.end = { hourHand.end + camera.GetPos() };
		hourHandLine.color = hourHand.color;

		SetDrawBlendMode(DX_BLENDMODE_ADD, brightHourHand);
		SetDrawBright(39, 32, 225);

		// --�Z�j�̕`��-- //
		for (int i = 0; i < longHand.length; i++) {
			DrawRotaGraph(
				hourHandLine.start.x + cosf(Degree2Radian(hourHand.radian - 90)) * (levelCircle.radius + i * 0.8f),
				hourHandLine.start.y + sinf(Degree2Radian(hourHand.radian - 90)) * (levelCircle.radius + i * 0.8f),
				0.5f, 0.0f, whiteCircleGraph, true);
		}



		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

#pragma region 12���ɐj��`��
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightLongHand);
		color = HexadecimalColor(GREEN);
		SetDrawBright(color.red, color.green, color.blue);
		Line line;
		line.start = { Vector2(640.0f, 480.0f) + camera.GetPos() };
		line.end = { Vector2(640.0f, 480.0f + longHand.length) + camera.GetPos() };
		line.color = hourHand.color;

		// --�j�̕`��-- //
		for (int i = 0; i < longHand.length * 0.5f; i++) {
			DrawRotaGraph(
				hourHandLine.start.x + cosf(Degree2Radian(-90)) * (levelCircle.radius + i * 1.6f),
				hourHandLine.start.y + sinf(Degree2Radian(-90)) * (levelCircle.radius + i * 1.6f),
				0.5f, 0.0f, whiteCircleGraph, true);
		}

		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion





#pragma region ���x���T�[�N���̕`��
		// -- ���x���T�[�N���`��-- //
		DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelCircleGraph[1], true);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		color = HexadecimalColor(LIGHTBLUE);
		SetDrawBright(color.red, color.green, color.blue);
		for (int i = 0; i < 5; i++) {
			DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelCircleGraph[0], true);
			// --���x���̕`��-- //
			if (isOpening == false) DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelGraph[level], true);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

#pragma region �ڈ�p0���̐j�̕`��
		// --0���̐j�̍��W�ƃJ�����V�F�C�N�̍��W������Circle�ϐ�-- //
		line;
		line.start = { clock.pos + camera.GetPos() };
		line.end = { clock.pos.x + camera.GetPos().x, clock.pos.y - clock.radius + 16 + camera.GetPos().y };
		line.color = 0x60FFBF;

		// --0���̐j�`��-- //
		//DrawLine(line, 6);
#pragma endregion

#pragma region �G�̔����~�`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		//DrawCircle(burstCircle, 0xff0000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);

		for (int i = 0; i < burstCircleEffects.size(); i++) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, burstEffectColorParam[i]);
			int X1 = burstCircleEffects[i].pos.x;
			int Y1 = burstCircleEffects[i].pos.y;
			int X2 = burstCircleEffects[i].pos.x + burstCircleEffects[i].radiusX;
			int Y2 = burstCircleEffects[i].pos.y + burstCircleEffects[i].radiusY;
			DrawBox(X1, Y1, X2, Y2, burstEffectColor[i], true);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, burstEffectColorParam[i]);
		}
#pragma endregion

#pragma region �G�t�F�N�g�`��
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		for (int i = 0; i < breakEffects.size(); i++) {
			int graph;
			if (Random(0, 100) > 50)graph = itemGraph[0];
			else graph = enemyGraph[0];
			breakEffects[i].Draw(camera, graph);
		}

		//�p�[�e�B�N���X�^�[�̕`��
		/*for (int i = 0; i < 5; i++) {
			if (!isOpening) {
				star[i].Draw(camera, PURPLE, particleGraph);
				star2[i].Draw(camera, ORANGE, particleGraph);
			}
		}*/

		//���x���ϓ��G�t�F�N�g
		for (int i = 0; i < levelChangeParticle.size(); i++) {
			int graph;
			if (Random(0, 100) > 50)graph = itemGraph[0];
			else graph = enemyGraph[0];
			levelChangeParticle[i].Draw(camera, Random(0, 0xffffff), graph);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		//���񂾎��̃G�t�F�N�g
		if (sandwichEffectTimer > 0) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, (256.0f / 25.0f) * sandwichEffectTimer);
			if (sandwichValue == GOOD) {
				SetDrawBright2(GREEN);
				for (int i = 0; i < 10; i++) {
					DrawRotaGraph(sandwichEffectPos.x, sandwichEffectPos.y, 1, 0, sandwichEffectGraph[2], true);
				}
			}//��
			else if (sandwichValue == GREAT) {
				SetDrawBright2(ORANGE);
				for (int i = 0; i < 10; i++) {
					DrawRotaGraph(sandwichEffectPos.x, sandwichEffectPos.y, 1, 0, sandwichEffectGraph[1], true);
				}//��
			}
			else if (sandwichValue == EXCELLENT) {
				SetDrawBright2(YELLOW);
				for (int i = 0; i < 10; i++) {
					DrawRotaGraph(sandwichEffectPos.x, sandwichEffectPos.y, 1, 0, sandwichEffectGraph[0], true);
				}	//���F
			}
		}

#pragma endregion

		//�J�E���g�_�E���̕`��
		//����
		int countDownBright;
		int graphNum = (nowTime - animationTime) / 50 * (nowTime >= animationTime);	//�摜�z��̏��Ԃ�321�Ȃ炱����
		if (graphNum > 2)graphNum = 2;					//1,2,3�Ȃ炱����
		int graphNumR = 2 - graphNum;

		countDownBright = (256 - ((256.0f / 50.0f) * (nowTime - (animationTime + (graphNum * 50))))) * (nowTime >= animationTime);
		SetDrawBlendMode(DX_BLENDMODE_ADD, countDownBright);
		// --�摜�`���������-- //
		DrawGraphF(589.0f, 412.5f, countNumGraph[graphNum], true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, countDownBright);

		//X�{�^���̓��x�����P�ȏ�̎��̂ݕ`��
		SetDrawBlendMode(DX_BLENDMODE_ADD, sinf(graphRad/180 * PI) * 64 + 128);
		if (level > 0) {
			float rad, len, radius;
			Vector2 pos;
			radius = 16;
			rad = hourHand.radian - 90 - 5;
			len = hourHand.length - 16;
			//pos = player->GetPlayer().pos;
			pos.x = len * cosf(rad / 180 * PI) + clock.pos.x;
			pos.y = len * sinf(rad / 180 * PI) + clock.pos.y;
			c = HexadecimalColor(LIGHTBLUE);
			SetDrawBright(c.red, c.green, c.blue);
			for (int i = 0; i < 10; i++) {
				DrawExtendGraph(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, returnButton[0], true);
			}
			//pos = player->GetPlayer().pos;

			len = hourHand.length - 44;
			pos.x = len * cosf(rad / 180 * PI) + clock.pos.x;
			pos.y = len * sinf(rad / 180 * PI) + clock.pos.y;
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(pos.x, pos.y, (32.0f / 58.0f), (hourHand.radian - 90) / 180 * PI, returnButton[1], true);
			}
		}

		if (!isOpening) {
			//�E���̑���UI�`��

			int posx = 1280 - 234;
			int posy = 960 - 234;
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawGraph(posx, posy, gameUIBoardGraph[1], true);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			SetDrawBright2(RED);
			for (int i = 0; i < 10; i++) {
				DrawGraph(posx, posy, gameUIBoardGraph[0], true);
			}
			posx = 1280 - 190 - 22;
			posy = 960 - 190 - 22;
			SetDrawBright2(LIGHTBLUE);
			for (int i = 0; i < 10; i++) {
				DrawGraph(posx, posy, gameUIGraph[0], true);
			}
			SetDrawBright2(0xffffff);
			for (int i = 0; i < 10; i++) {
				DrawGraph(posx, posy, gameUIGraph[1], true);
			}
			SetDrawBright2(GREEN);
			for (int i = 0; i < 14; i++) {
				DrawGraph(posx, posy, gameUIGraph[2], true);
			}
			SetDrawBright2(RED);
			for (int i = 0; i < 10; i++) {
				DrawGraph(posx, posy, gameUIGraph[3], true);
			}

			posx = 1280 - 234;
			posy = 960 - 234;
		}

		//�j��0�ɂȂ������̉��o
		if (retuckEffectTimer > 0) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, (256.0f / 25.0f) * retuckEffectTimer);
			SetDrawBright2(PURPLE);
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(clock.pos.x, clock.pos.y, 1.0f, 0, retuckGraph[0], true);
			}
			SetDrawBright2(GREEN);
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(clock.pos.x, clock.pos.y, 1.0f, 0, retuckGraph[1], true);
			}
		}

	
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightLongHand);
		DrawGraph(0, 0, tutorialBoardGraph[1], true);
		SetDrawBright2(RED);
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightLongHand);
		//SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawGraph(0, 0, tutorialBoardGraph[0], true);
		}

		SetDrawBright2(EFFECT_GREEN);
		for (int i = 0; i < 10; i++) {
			DrawGraph(16, 16, gameRuleGraph[0], true);
		}

		SetDrawBright2(LIGHTBLUE);
		for (int i = 0; i < 10; i++) {
			DrawGraph(16, 16, gameRuleGraph[1], true);
		}

		SetDrawBright2(0xffffff);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		color = HexadecimalColor(PURPLE);
		SetDrawBright(color.red, color.green, color.blue);
		if (isSceneChange == true) {
			for (int i = 0; i < 5; i++) {
				DrawRotaGraph(640.0f, 480.0f, 1.0f, 0.0f, finishGraph, true);
			}
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma region �f�o�b�O�`��
		if (SceneManager::GetDebugMode() == true) {
			DrawFormatString(0, 100, 0xFFFFFF, "AD�L�[:���x���T�[�N���̔��a�ύX");
			DrawFormatString(0, 120, 0xFFFFFF, "���x���T�[�N���̔��a:%f", levelCircle.radius);
			DrawFormatString(0, 140, 0xFFFFFF, "ZC�L�[:�Z�j�̑��x�ύX");
			DrawFormatString(0, 160, 0xFFFFFF, "IP�L�[�Œ��j�̑��x��ύX");
			DrawFormatString(0, 180, 0xFFFFFF, "�J�����V�F�C�N:�X�y�[�X�L�[(�U���ʂ̒����͖�����)");
			DrawFormatString(0, 200, longHand.color, "longHand(���j)�̏�� x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
			DrawFormatString(0, 220, hourHand.color, "hourHand(�Z�j)�̏�� x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
			DrawFormatString(0, 240, 0xFFFFFF, "�Z�j�̑��x:%f", hourHandSpeed + hourHandlevelSpeed * (level - 1));
			DrawFormatString(0, 260, 0xFFFFFF, "���j�̑��x:%f", longHandSpeed);
			DrawFormatString(0, 280, 0xFFFFFF, "�t���̑��x(�Z�j):%f", hourHandReverseSpeed);
			DrawFormatString(0, 300, 0xFFFFFF, "�t������:%f", reverseTime);
			DrawFormatString(0, 340, 0xFFFFFF, "�G�̑���:%d", enemys.size());
			DrawFormatString(0, 320, 0xFFFFFF, "FPS");
			DrawFormatString(0, 360, 0xFFFFFF, "�A�C�e�������񂾐�:%d", itemSandwichCount);

			DrawFormatString(0, 400, 0xFFFFFF, "�G�����񂾐�:%d", enemySandwichCount);
			DrawFormatString(0, 420, 0xFFFFFF, "point:%d", point);
			DrawFormatString(0, 440, 0xFFFFFF, "���񂾎���:%d", sandwichEffectTimer);

			/*SetFontSize(80);*/
			/*SetFontSize(16);*/
		}
#pragma endregion

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		//for (int i = 0; i < 3; i++) {
		//	DrawGraph(0, 800, enemyGraph[0], true);
		//}
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

// --�G�̃X�|�[������-- //
void GameScene::EnemySpawn(float radian) {

	enemyLength = Random(levelCircle.radius + 8.0f, hourHand.length);
	float rad = radian - 90;
	enemyPos.x = (enemyLength * cosf(rad / 180 * PI)) + clock.pos.x;
	enemyPos.x -= (10.0f * cosf((rad + 90) / 180 * PI));
	enemyPos.y = (enemyLength * sinf(rad / 180 * PI)) + clock.pos.y;
	enemyPos.y -= (10.0f * sinf((rad + 90) / 180 * PI));
	Enemy newEnemy;
	//Circle newPos = {enemyPos,8.0f}
	newEnemy.SetObj({ {enemyPos} , 8.0f });

	if (Random(0, 100) < enemySpawnRate) {
		//5%�̊m���œG�Ƃ��ăX�|�[��
		newEnemy.SetState(State::Enemy);
		newEnemy.SetHandle(enemyGraph);
	}
	else {//����ȊO��95%�ŃA�C�e���Ƃ��ăX�|�[��
		newEnemy.SetState(State::Item);
		newEnemy.SetHandle(itemGraph);
	}
	newEnemy.Initialize();
	enemys.push_back(newEnemy);
}

// --���@�ƓG�̓����蔻�菈��-- //
void GameScene::Collision() {
	// --���@�ƓG�̓����蔻����s��-- //
	for (int i = enemys.size() - 1; i >= 0; i--) {
		if (CollisionCtoC(player->player, enemys[i].obj)) {
			//�G�̃X�e�[�g��Item�Ȃ����
			if (enemys[i].GetState() == State::Item) {
				enemys[i].Death();
				//enemys.erase(enemys.begin() + i);
				point++;
				Score::AddScore(100);
				AddReversePower(1);

				//�T�E���h�Đ�
				sound->PlaySE(GETITEMSE);

			}//�G�̃X�e�[�g��enemy�Ȃ烌�x�������炵�ď��ł�����
			else if (enemys[i].GetState() == State::Enemy) {
				//���x���������āA�����T�[�N�����o��
				if (level > 0) {
					level--;
					point = 0;
				}
				burstCircle.pos = enemys[i].GetCircle().pos + camera.GetPos();
				burstCircle.radius = 96.0f;
				CreateBurstEffect(burstCircle, 128);
				//�G������
				enemys.erase(enemys.begin() + i);
				//�t������͂����Z�b�g
				reverseTime = 0;

				//�T�E���h�Đ�
				sound->PlaySE(HITENEMYSE);
			}
		}
	}

	// --���x���T�[�N���ƃG�l�~�[�̓����蔻��-- //
	//for (int i = 0; i < enemys.size(); i++) {
	//	if (CollisionCtoC(levelCircle, enemys[i].obj)) {
	//		//�G�̃X�e�[�g�����S�łȂ��Ȃ�(���S���o���łȂ��Ȃ�)
	//		if (enemys[i].GetState() != State::Death) {
	//			enemys.erase(enemys.begin() + i);
	//		}
	//	}
	//}
}

// --���x��-- //
void GameScene::LevelUpdate() {
#pragma region �o���l�ɂ���ă��x����ς��鏈��
	// --���݂̃��x���̕K�v�o���l����ɓ������烌�x�����グ��-- //
	//�`���[�g���A�����͕K�v�o���l�Œ�
	if (isTutorial) {
		if (tutorialStep == 0) {
			enemySpawnRate = 0;
		}
		if (point == 3) {
			level++;
			point = 0;
			LevelUpEfffect(96);
			//�T�E���h�Đ�
			sound->PlaySE(LEVELUPSE);
			//�`���[�g���A���̃X�e�b�v��i�߂�
			tutorialStep++;
			//�G�̃X�|�[������100%�ɂ��ēG���ʂɃX�|�[��
			enemySpawnRate = 100;
			for (int i = 0; i < 16; i++) {
				EnemySpawn(Random(205, 215));
			}
		}

	}
	else {

		if (needPoint[level] == point && level < 5) {
			level++;
			point = 0;
			LevelUpEfffect(96);
			//�T�E���h�Đ�
			sound->PlaySE(LEVELUPSE);
		}

		//�t�����x�̑��x�{��
		reverseVelocityScale = 2.0f;		//�Z�j	
		reverseVelocityScaleLong = 2.0f;	//���j

	}
	//���x���œG�̏o�����𒲐�
	switch (level)
	{
	case 0:
		enemySpawnRate = 0.0f;
		spawnInterval = 100;
		break;
	case 1:
		//�`���[�g���A�����͓G���N���Ȃ��悤��
		if (isTutorial)enemySpawnRate = 0.0f;
		else enemySpawnRate = 15.0f;

		spawnInterval = 45;
		reverseVelocityScale = 3.5f;
		reverseVelocityScaleLong = 1.5f;
		break;
	case 2:
		enemySpawnRate = 19.0f;
		spawnInterval = 32;
		reverseVelocityScale = 3.5f;
		reverseVelocityScaleLong = 1.5f;
		break;
	case 3:
		enemySpawnRate = 23.0f;
		spawnInterval = 24;
		reverseVelocityScale = 3.0f;
		reverseVelocityScaleLong = 1.2f;
		break;
	case 4:
		enemySpawnRate = 26.0f;
		spawnInterval = 20;
		reverseVelocityScale = 2.5f;
		reverseVelocityScaleLong = 1.2f;
		break;
	case 5:
		enemySpawnRate = 28.0f;
		spawnInterval = 15;
		reverseVelocityScale = 2.5f;
		reverseVelocityScaleLong = 1.2f;
		break;
	case 6:
		enemySpawnRate = 29.0f;
		break;
	case 7:
		enemySpawnRate = 30.0f;
		break;
	case 8:
		enemySpawnRate = 31.0f;
		break;
	case 9:
		enemySpawnRate = 32.0f;
		break;
	case 10:
		enemySpawnRate = 33.5f;
		break;
	}



#pragma endregion
}

// --���x�����Z�b�g-- //
void GameScene::LevelReset() {
	level = 0;
	point = 0;
}

void GameScene::CreateBreakEffect(Vector2 pos, int effectParam) {

	//�쐬����G�t�F�N�g�̐��������I�z��ɓ����
	for (int i = 0; i < effectParam; i++) {
		BreakEffect newEffect;
		newEffect.Initialize(pos);
		breakEffects.push_back(newEffect);
	}
}

void GameScene::AddReversePower(int power) {
	//���Z
	reverseTime += power;
}

void GameScene::OpeningUpdate() {
	if (!isOpening) {
		return;
	}
	//���Ԃ����Z
	nowTime++;

	if (nowTime <= animationTime) {

		//1�b�ň��]����悤�ɉ�]���x��ύX
		hourHandReverseSpeed = 360.0f / 250.0f;

		hourHand.radian -= hourHandReverseSpeed;
		float radH = hourHand.radian - 90;
		//�j�̊p�x�ŏI�_���W���v�Z
		hourHand.end.x = (hourHand.length * cosf(radH / 180 * PI)) + clock.pos.x;
		hourHand.end.y = (hourHand.length * sinf(radH / 180 * PI)) + clock.pos.y;

	}
	//�o�ߎ��Ԃ��w��̃t���[���ɗ�����X�|�[��
	for (int i = 0; i < opSpawnFrame.size(); i++) {
		if (nowTime == opSpawnFrame[i]) {
			EnemySpawn(hourHand.radian - 5.0f);
		}
	}

	player->Update(hourHand, clock, levelCircle.radius);

	for (int i = enemys.size() - 1; i >= 0; i--) {
		enemys[i].Update(hourHand, { 0,0 });
	}
	if (nowTime == openingTime) {
		isOpening = false;
		retuckEffectTimer = 30;
	}
}

void GameScene::LevelUpEfffect(int effectNum)
{
	for (int i = 0; i < effectNum; i++) {
		Particle newpaticle;
		Vector2 pos;
		float len, rad;
		len = longHand.length;
		rad = Random(0.0f, 360.0f);
		pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
		pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
		newpaticle.SetParent(pos);
		newpaticle.SetSpeed(Random(3.0f, 8.0f));
		newpaticle.SetRadius(Random(8.0f, 12.0f));
		newpaticle.SetRadian(Random(rad - 60, rad + 60));
		newpaticle.SetRadian(rad);
		newpaticle.Initialize(true);
		levelChangeParticle.push_back(newpaticle);
	}
}

void GameScene::CreateBurstEffect(Circle burstRange, int effectNum) {
	for (int i = 0; i < effectNum; i++) {
		Box newbox;
		float rad = Random(0.0f, 360.0f);
		float len = Random(0.0f, burstCircle.radius);
		float lenX;
		float lenY;

		while (true) {
			lenX = Random(0.0f, burstRange.radius / 3);
			lenY = Random(0.0f, burstRange.radius / 3);
			newbox.pos.x = len * cosf(rad / 180 * PI) + burstCircle.pos.x;
			newbox.pos.y = len * sinf(rad / 180 * PI) + burstCircle.pos.y;
			//�G�t�F�N�g�̍�����W�ɉ����Ĕ��a���}�C�i�X�ɂ���
			if (burstCircle.pos.x < newbox.pos.x) lenX = -lenX;
			if (burstCircle.pos.x < newbox.pos.x) lenY = -lenY;
			newbox.radiusX = lenX;
			newbox.radiusY = lenY;

			//���W+���a���T�[�N�����o�Ȃ���΍��W�m��
			if (newbox.pos.x + lenX <= burstCircle.pos.x + burstCircle.radius &&
				newbox.pos.x - lenX >= burstCircle.pos.x - burstCircle.radius &&
				newbox.pos.y + lenY <= burstCircle.pos.y + burstCircle.radius &&
				newbox.pos.y - lenY >= burstCircle.pos.y - burstCircle.radius) {
				break;
			}
		}
		burstCircleEffects.push_back(newbox);
		int newcolor = 256;
		burstEffectColorParam.push_back(newcolor);
		Color c;
		c = HexadecimalColor(RED);
		c.red += Random(-16, 16);
		c.blue += Random(-16, 16);
		c.green += Random(-16, 16);
		newcolor = ColorHexadecimal(c);
		burstEffectColor.push_back(newcolor);
	}

}

void GameScene::UpdateTutorial() {

	//�`���[�g���A�����N���A����Ă���Ȃ�
	if (isTutorialClear) {
		//�V�[���J�ڃ^�C�}�[�����炷
		sceneChangeTimer--;
		//�G������
		enemys.clear();
		LevelReset();
		if (sceneChangeTimer < 24) {
			longHand.radian = 0;
			hourHand.radian = 0;
			if (sceneChangeTimer <= 0) {
				isOpening = true;
				nowTime = 0;
				isTutorial = false;
			}
		}

	}

	//�摜�p���W�A������
	graphRad += 4;
	if (graphRad >= 360.0f) {
		graphRad -= 360.0f;
	}

	//�X�^�[�g�{�^���Ń`���[�g���A���N���A
	if (pad->GetButton(PAD_INPUT_8)) {
		isTutorialClear = true;
	}

	//L�{�^���ŒZ�j�̃X�e�[�g���u���]�v��(�`���[�g���A���̃X�e�b�v���Ō�Ȃ�)
	if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::Normal && level > 0) {
		if (tutorialStep == 2)hourHand.state = State::Reverse;
	}

	//�t���̑��x�͒Z�j�̑��x * ���x�{����
	hourHandReverseSpeed = (hourHandSpeed + hourHandlevelSpeed * (level - 1)) * reverseVelocityScale;

	//�X�e�[�g���ʏ�Ȃ�Z�j�͎�����]
	if (hourHand.state == State::Normal) {
		hourHand.radian += hourHandSpeed + hourHandlevelSpeed * (level - 1);

		//�C�ӂ̃L�[�ŒZ�j�𓮂���(�f�o�b�O�p)
		//hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
	}//�X�e�[�g�����]���Ă���Ȃ�Z�j���t��������
	else if (hourHand.state == State::Reverse) {
		hourHand.radian -= hourHandReverseSpeed;
		//�Z�j�����j�ɒǂ������璷�j�̃X�e�[�g���u���]�v��
		if (hourHand.radian < longHand.radian + hourHandReverseSpeed && hourHand.radian > longHand.radian - hourHandReverseSpeed) {
			longHand.state = State::Reverse;
			//�Z�j�̃X�e�[�g���Ƃ߂�
			hourHand.state = State::Stop;
			//�͂��񂾃I�u�W�F�N�g�̐��Ŗ߂��͂𑝂₷
			reverseTime = 200;

			itemSandwichCount = 0;
			enemySandwichCount = 0;

			//���j�̋t�����x���v�Z
			longHandReverseSpeed = hourHandReverseSpeed * reverseVelocityScaleLong;
			//���x�����Z�b�g
			LevelReset();

			//�͂��񂾏u�Ԃɂ͂��܂�Ă���G�����ł�����
			for (int i = enemys.size() - 1; i >= 0; i--) {
				if (enemys[i].GetState() == State::Reverse) {
					enemys[i].Death();
				}
			}
		}
	}

	if (tutorialStep == 2) {
		//�X�e�[�g���ʏ�Ȃ璷�j�͎�����]
		if (longHand.state == State::Normal) {
			longHand.radian += longHandSpeed;
		}//�X�e�[�g���u���]�v���A���]����͂��܂��c���Ă���Ȃ�t��
		else if (longHand.state == State::Reverse) {
			if (reverseTime > 0) {
				//���x�͒Z�j�Ɠ���
				longHand.radian -= longHandReverseSpeed;
				//���j�̊p�x��0�ɂȂ����璷�j�ƒZ�j�̃X�e�[�g��߂��A�p�x��������(���j�̂�)
				if (longHand.radian < hourHandReverseSpeed) {
					longHand.state = State::Normal;
					hourHand.state = State::Normal;
					longHand.radian = 0;
					//�X�e�[�g���f�X�łȂ��G�͍폜�A�f�X�͂��̂܂�
					for (int i = enemys.size() - 1; i >= 0; i--) {
						if (enemys[i].GetState() != State::Death) {
							enemys.erase(enemys.begin() + i);
						}
					}
					//���x�����Z�b�g
					LevelReset();
					//�V�F�C�N
					camera.SetShakeCount(10);
					//�G�̃X�|�[���^�C�}�[�����Z�b�g
					spawnTimer = spawnInterval;
					//�Ռ��G�t�F�N�g���쐬
					CreateBreakEffect(clock.pos, 128);
					//���x���A�b�v�G�t�F�N�g���쐬(�Y��Ȃ̂�)
					LevelUpEfffect(64 * 3);
					//�߂��͂����Z�b�g
					reverseTime = 0;
					//�T�E���h�Đ�
					sound->PlaySE(SANDSE);
					//�`���[�g���A�����N���A��
					isTutorialClear = true;
				}
				//���]���x�̌��Z
				reverseTime--;
			}//�߂��͂��Ȃ��Ȃ�����X�e�[�g���m�[�}���ɖ߂�
			else if (reverseTime <= 0) {
				longHand.state = State::Normal;
				hourHand.state = State::Normal;
				//�G�̃X�|�[���^�C�}�[�����Z�b�g
				spawnTimer = spawnInterval;
			}
		}
	}

	//360�x��������0�ɖ߂��A0�����������360���Z����
	hourHand.radian = fmodf(hourHand.radian, 360.0f);
	if (hourHand.radian <= 0)hourHand.radian += 360.0f;

	//�ʒu�������`��p�̃��W�A���錾
	float radL = longHand.radian - 90;
	float radH = hourHand.radian - 90;

	//�j�̊p�x�ŏI�_���W���v�Z
	longHand.end.x = (longHand.length * cosf(radL / 180 * PI)) + clock.pos.x;
	longHand.end.y = (longHand.length * sinf(radL / 180 * PI)) + clock.pos.y;
	//�j�̊p�x�ŏI�_���W���v�Z
	hourHand.end.x = (hourHand.length * cosf(radH / 180 * PI)) + clock.pos.x;
	hourHand.end.y = (hourHand.length * sinf(radH / 180 * PI)) + clock.pos.y;

	// --���j�����������G��3�̃X�|�[��������
	if (longHand.radian >= 360.0f) {
		longHand.radian -= 360.0f;
		//�O�ɂ����G�͂��ׂď���
		enemys.clear();
		//���@���x�����Z�b�g
		LevelReset();
		for (int i = 0; i < 3; i++) {
			EnemySpawn(Random(0.0f, 36.0f) + 36.0f + 108.0f * i);
		}
	}

	//���@�X�V
	player->Update(hourHand, clock, levelCircle.radius);

	//�G�l�~�[�֌W
	//�G�l�~�[�X�V
	for (int i = enemys.size() - 1; i >= 0; i--) {

		Vector2 scorePos = { 1200,60 };
		enemys[i].Update(hourHand, scorePos);
		//�Z�j�����]���[�h�Ȃ画����Ƃ�
		if (hourHand.state == State::Reverse) {
			//�Z�j�ƓG�̓����蔻��
			if (CollisionCtoL(enemys[i].GetCircle(), hourHand, hourHandReverseSpeed)) {
				//�I�u�W�F�N�g�̃X�e�[�g���܂��u���]�v�łȂ��A����ł����Ȃ��Ȃ瓖���蔻��̃R�[���o�b�N�֐����Ăяo���A���񂾐����J�E���g����
				if (enemys[i].GetState() != State::Reverse && enemys[i].GetState() != State::Death) {
					if (enemys[i].GetState() == State::Item) {
						itemSandwichCount++;
					}
					else if (enemys[i].GetState() == State::Enemy) {
						enemySandwichCount++;
					}

					enemys[i].OnCollison();
				}
			}
		}

		//���j���m�[�}�����[�h�Ȃ画����Ƃ�
		if (longHand.state == State::Normal) {
			//���j�ƓG�̓����蔻��
			if (CollisionCtoL(enemys[i].GetCircle(), longHand, longHandSpeed)) {
				//��x���X�e�[�g�ύX���s���Ă��Ȃ��Ȃ�
				if (!enemys[i].GetIsChange()) {
					//�G�̏�Ԃ��A�C�e���Ȃ�G��
					if (enemys[i].GetState() == State::Item) {
						enemys[i].SetState(State::Enemy);
						enemys[i].SetHandle(enemyGraph);
					}//�G�Ȃ�A�C�e����
					else if (enemys[i].GetState() == State::Enemy) {
						enemys[i].SetState(State::Item);
						enemys[i].SetHandle(itemGraph);
					}
					enemys[i].StateChange();
				}

			}

		}



		//�����~�Ƃ̓����蔻��
		if (CollisionCtoC(enemys[i].GetCircle(), burstCircle)) {
			//���������A�C�e��������
			enemys[i].SetState(State::Delete);
		}



		//�`���[�g���A�����ŏI�X�e�b�v�ɂ��Ă���G��S�폜
		if (tutorialStep == 2) {
			enemys[i].SetState(State::Delete);
			level = 1;
		}

		if (enemys[i].GetState() == State::Delete) {
			enemys.erase(enemys.begin() + i);
		}
	}

	//�G�t�F�N�g�֌W
	//�@--�����~�̍��W���Z�b�g-- //
	burstCircle = { {0.0f,0.0f}, 0.0f };

	for (int i = burstCircleEffects.size() - 1; i >= 0; i--) {
		//�o�[�X�g�T�[�N���̐F�𗎂Ƃ�
		burstEffectColorParam[i] -= Random(-5, 15);
		if (burstEffectColorParam[i] <= 0) {
			burstEffectColorParam.erase(burstEffectColorParam.begin() + i);
			burstEffectColor.erase(burstEffectColor.begin() + i);
			burstCircleEffects.erase(burstCircleEffects.begin() + i);
		}
	}

	//�G�t�F�N�g�X�V����
	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Update();
		//�����t���O��false�Ȃ�Y���v�f������
		if (!breakEffects[i].GetAllive()) {
			breakEffects.erase(breakEffects.begin() + i);
		}
	}

	for (int i = 0; i < lineParticleMax; i++) {
		Vector2 pos;
		float len, rad;
		len = Random(levelCircle.radius, hourHand.length);
		rad = hourHand.radian - 90.0f;
		pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
		pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
		hourHandParticle[i].SetParent(pos);
		hourHandParticle[i].SetSpeed(Random(0.0f, 0.2f));
		hourHandParticle[i].SetRadius(Random(3.0f, 6.0f));
		hourHandParticle[i].Update();

		len = Random(levelCircle.radius, longHand.length);
		rad = longHand.radian - 90.0f;
		pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
		pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
		longHandParticle[i].SetParent(pos);
		longHandParticle[i].SetSpeed(Random(0.5f, 2.0f));
		hourHandParticle[i].SetRadius(Random(1.0f, 3.0f));
		longHandParticle[i].SetRadian(Random(rad - 135, rad - 45));
		longHandParticle[i].Update();
	}

	for (int i = levelChangeParticle.size() - 1; i >= 0; i--) {
		Vector2 pos;
		float len, rad;
		len = longHand.length;
		rad = Random(0.0f, 360.0f);
		pos.x = (len * cosf(rad / 180 * PI)) + clock.pos.x;
		pos.y = (len * sinf(rad / 180 * PI)) + clock.pos.y;
		levelChangeParticle[i].SetParent(pos);
		levelChangeParticle[i].SetSpeed(Random(3.0f, 8.0f));
		levelChangeParticle[i].SetRadius(Random(6.0f, 10.0f));
		//levelChangeParticle[i].SetRadian(Random(rad - 60, rad + 60));
		//levelChangeParticle[i].SetRadian(rad);
		levelChangeParticle[i].Update();
		//�A�N�e�B�u����Ȃ��Ȃ��������
		if (!levelChangeParticle[i].GetActive()) {
			levelChangeParticle.erase(levelChangeParticle.begin() + i);
		}
	}

	//�J��������
	camera.CameraShake();

	//�����蔻��(�{�҂̃Q�[������X�R�A���Z���Ȃ������肵��ver)
	for (int i = enemys.size() - 1; i >= 0; i--) {
		if (CollisionCtoC(player->player, enemys[i].obj)) {
			//�G�̃X�e�[�g��Item�Ȃ����
			if (enemys[i].GetState() == State::Item) {
				enemys[i].Death();
				//enemys.erase(enemys.begin() + i);
				point++;
				AddReversePower(1);

				//�T�E���h�Đ�
				sound->PlaySE(GETITEMSE);

			}//�G�̃X�e�[�g��enemy�Ȃ烌�x�������炵�ď��ł�����
			else if (enemys[i].GetState() == State::Enemy) {
				//���x���������āA�����T�[�N�����o��
				if (level > 0) {
					level--;
					point = 0;
				}
				burstCircle.pos = enemys[i].GetCircle().pos + camera.GetPos();
				burstCircle.radius = 96.0f;
				CreateBurstEffect(burstCircle, 128);
				//�G������
				enemys.erase(enemys.begin() + i);
				//�t������͂����Z�b�g
				reverseTime = 0;

				//�T�E���h�Đ�
				sound->PlaySE(HITENEMYSE);

				//�`���[�g���A����i�߂āA�G�����ׂď���
				if (tutorialStep == 1) {
					tutorialStep++;
				}
			}
		}
	}

	//���x���X�V����
	LevelUpdate();


}

void GameScene::DrawTutorial() {
	// --�w�i�`��-- //
	DrawGraph(0, 0, backGroundGraph, true);
	//�摜�̉��Z�l�̓`���[�g���A���I�����ɈÂ�����
	int brightParam = (256.0f / 25.0f) * (sceneChangeTimer - 25);

	if (!isTutorialSkip) {
		player->Draw(camera, brightParam);

		for (int i = 0; i < enemys.size(); i++) {
			enemys[i].Draw(camera, particleGraph);
		}

		// --���v�̊O�g�̍��W�ƃJ�����V�F�C�N�̍��W������Circle�ϐ�-- //
		Circle clockCircle = { clock.pos + camera.GetPos(), clock.radius };
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		Color color = HexadecimalColor(LIGHTBLUE);
		SetDrawBright(color.red, color.green, color.blue);

		// --���v�̊O�g�̕`��-- //
		for (int i = 0; i < 20; i++) {
			DrawRotaGraph(640 + camera.GetPos().x, 480 + camera.GetPos().y, 1.0f, 0.0f, clockGraph, true);
		}
		SetDrawBright(255, 255, 255);

		//�j�̃p�[�e�B�N���̕`��
		for (int i = 0; i < lineParticleMax; i++) {
			hourHandParticle[i].Draw(camera, PURPLE, particleGraph);
			longHandParticle[i].Draw(camera, EFFECT_GREEN, particleGraph);
		}

		// --���j�̍��W�ƃJ�����V�F�C�N�̍��W������Line�ϐ�-- //
		Line longHandLine;
		longHandLine.start = { longHand.start + camera.GetPos() };
		longHandLine.end = { longHand.end + camera.GetPos() };
		longHandLine.color = longHand.color;

		//etDrawBright(119, 28, 28);
		Color c;
		c = HexadecimalColor(GREEN);
		SetDrawBright(c.red, c.green, c.blue);
		// --���j�̕`��-- //

		for (int i = 0; i < longHand.length * 1.3f; i++) {
			DrawRotaGraph(
				longHandLine.start.x + cosf(Degree2Radian(longHand.radian - 90)) * (levelCircle.radius + i * 0.8f / 1.3f),
				longHandLine.start.y + sinf(Degree2Radian(longHand.radian - 90)) * (levelCircle.radius + i * 0.8f / 1.3f),
				0.5f, 0.0f, whiteCircleGraph, true);
		}

		SetDrawBright(255, 255, 255);

#pragma region 12���ɐj��`��
		color = HexadecimalColor(GREEN);
		SetDrawBright(color.red, color.green, color.blue);
		Line line;
		line.start = { Vector2(640.0f, 480.0f) + camera.GetPos() };
		line.end = { Vector2(640.0f, 480.0f + longHand.length) + camera.GetPos() };
		line.color = hourHand.color;

		// --�j�̕`��-- //
		for (int i = 0; i < longHand.length * 0.5f; i++) {
			DrawRotaGraph(
				line.start.x + cosf(Degree2Radian(-90)) * (levelCircle.radius + i * 1.6f),
				line.start.y + sinf(Degree2Radian(-90)) * (levelCircle.radius + i * 1.6f),
				0.5f, 0.0f, whiteCircleGraph, true);
		}

		SetDrawBright(255, 255, 255);
#pragma endregion

		// --�Z�j�̍��W�ƃJ�����V�F�C�N�̍��W������Line�ϐ�-- //
		Line hourHandLine;
		hourHandLine.start = { hourHand.start + camera.GetPos() };
		hourHandLine.end = { hourHand.end + camera.GetPos() };
		hourHandLine.color = hourHand.color;

		SetDrawBright(39, 32, 225);

		// --�Z�j�̕`��-- //
		for (int i = 0; i < longHand.length; i++) {
			DrawRotaGraph(
				hourHandLine.start.x + cosf(Degree2Radian(hourHand.radian - 90)) * (levelCircle.radius + i * 0.8f),
				hourHandLine.start.y + sinf(Degree2Radian(hourHand.radian - 90)) * (levelCircle.radius + i * 0.8f),
				0.5f, 0.0f, whiteCircleGraph, true);
		}

		SetDrawBright(255, 255, 255);

		for (int i = 0; i < burstCircleEffects.size(); i++) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, burstEffectColorParam[i]);
			int X1 = burstCircleEffects[i].pos.x;
			int Y1 = burstCircleEffects[i].pos.y;
			int X2 = burstCircleEffects[i].pos.x + burstCircleEffects[i].radiusX;
			int Y2 = burstCircleEffects[i].pos.y + burstCircleEffects[i].radiusY;
			DrawBox(X1, Y1, X2, Y2, burstEffectColor[i], true);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, burstEffectColorParam[i]);
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);

		for (int i = 0; i < breakEffects.size(); i++) {
			int graph;
			if (Random(0, 100) > 50)graph = itemGraph[0];
			else graph = enemyGraph[0];
			breakEffects[i].Draw(camera, graph);
		}

		for (int i = 0; i < levelChangeParticle.size(); i++) {
			int graph;
			if (Random(0, 100) > 50)graph = itemGraph[0];
			else graph = enemyGraph[0];
			levelChangeParticle[i].Draw(camera, Random(0, 0xffffff), graph);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, brightParam);

		//UI�`��
	//	SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		//�X�R�A�{�[�h
		int posx = 1280 - 384;
		int posy = 2;
		c = HexadecimalColor(RED);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightParam);
		DrawGraph(posx, posy, tutorialBoardGraph[1], true);
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawGraph(posx, posy, tutorialBoardGraph[0], true);
		}

		//�`���[�g���A���X�e�b�v�ŉ摜��`��
		c = HexadecimalColor(LIGHTBLUE);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			c = HexadecimalColor(LIGHTBLUE);
			SetDrawBright(c.red, c.green, c.blue);
			DrawGraph(posx + 16, posy + 16, tutorialTextGraph[tutorialStep], true);
			//�X�e�b�v1�Ń{�^���`��
			if (tutorialStep == 0) {
				c = HexadecimalColor(GREEN);
				SetDrawBright(c.red, c.green, c.blue);
				DrawExtendGraph(posx + 48, posy + 20, posx + 84, posy + 56, ButtonGraph[1], true);
				c = HexadecimalColor(RED);
				SetDrawBright(c.red, c.green, c.blue);
				DrawExtendGraph(posx + 120, posy + 20, posx + 156, posy + 56, ButtonGraph[2], true);
				SetDrawBright(255, 255, 255);
			}
		}

		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightParam);
		DrawGraph(0, 0, tutorialBoardGraph[1], true);
		SetDrawBright2(RED);
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawGraph(0, 0, tutorialBoardGraph[0], true);
		}

		SetDrawBright2(EFFECT_GREEN);
		for (int i = 0; i < 10; i++) {
			DrawGraph(16, 16, gameRuleGraph[0], true);
		}

		SetDrawBright2(LIGHTBLUE);
		for (int i = 0; i < 10; i++) {
			DrawGraph(16, 16, gameRuleGraph[1], true);
		}


		Vector2 pos;
		float len = 48;
		pos = player->GetPlayer().pos;
		float rad = hourHand.radian - 90;
		pos.x -= len * cosf(rad / 180 * PI);
		pos.y -= len * sinf(rad / 180 * PI);
		float radius = 16;

		c = HexadecimalColor(RED);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawExtendGraph(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, ButtonGraph[2], true);
		}

		pos = player->GetPlayer().pos;
		pos.x += len * cosf(rad / 180 * PI);
		pos.y += len * sinf(rad / 180 * PI);
		c = HexadecimalColor(GREEN);
		SetDrawBright(c.red, c.green, c.blue);
		for (int i = 0; i < 10; i++) {
			DrawExtendGraph(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, ButtonGraph[1], true);
		}

		//X�{�^���͍Ō�̃`���[�g���A���̂ݕ`��
		if (tutorialStep == 2) {
			if (!isTutorialClear) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, sinf(graphRad / 180 * PI) * 64 + 128);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
			}
			rad = hourHand.radian - 90 - 5;
			len = hourHand.length - 16;
			//pos = player->GetPlayer().pos;
			pos.x = len * cosf(rad / 180 * PI) + clock.pos.x;
			pos.y = len * sinf(rad / 180 * PI) + clock.pos.y;
			c = HexadecimalColor(LIGHTBLUE);
			SetDrawBright(c.red, c.green, c.blue);
			for (int i = 0; i < 10; i++) {
				DrawExtendGraph(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, returnButton[0], true);
			}
			//pos = player->GetPlayer().pos;

			len = hourHand.length - 44;
			pos.x = len * cosf(rad / 180 * PI) + clock.pos.x;
			pos.y = len * sinf(rad / 180 * PI) + clock.pos.y;
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(pos.x, pos.y, (32.0f / 58.0f), (hourHand.radian - 90) / 180 * PI, returnButton[1], true);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD,255);
		//�`���[�g���A���N���A���̕`��
		if (isTutorialClear) {
			SetDrawBright2(YELLOW);
			Vector2 pos;
			pos = clock.pos + camera.GetPos();
			pos.y -= 200;
			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(pos.x, pos.y, 1, 0, successGraph, true);
			}
		}

		//�X�L�b�v�{�^��UI�̒ǉ�
		//Vector2 pos;
		pos.x = 1280 - 227;
		pos.y = 960 - 54;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightParam);
		DrawGraph(pos.x, pos.y, skipGraph[2], true);
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightParam);
		SetDrawBright2(LIGHTBLUE);
		for (int i = 0; i < 10; i++) {
			DrawGraph(pos.x, pos.y, skipGraph[0], true);
		}
		SetDrawBright2(RED);
		for (int i = 0; i < 10; i++) {
			DrawGraph(pos.x, pos.y, skipGraph[1], true);
		}

		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//�`���[�g���A���̃t�H���g�`��
		SetDrawBright2(YELLOW);
		SetDrawBlendMode(DX_BLENDMODE_ADD, sinf(graphRad / 180 * PI) * 255);
		for (int i = 0; i < 10; i++) {
			DrawGraph(0, 120, tutorialFontGraph, true);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// -- ���x���T�[�N���`��-- //
	DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelCircleGraph[1], true);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	Color color = HexadecimalColor(LIGHTBLUE);
	SetDrawBright(color.red, color.green, color.blue);
	for (int i = 0; i < 10; i++) {
		DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelCircleGraph[0], true);
		// --���x���̕`��-- //
		if (!isTutorialSkip) {
			DrawGraph(560 + camera.GetPos().x, 400 + camera.GetPos().y, levelGraph[level], true);
		}
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (SceneManager::GetDebugMode() == true) {
		DrawFormatString(0, 100, 0xFFFFFF, "AD�L�[:���x���T�[�N���̔��a�ύX");
		DrawFormatString(0, 120, 0xFFFFFF, "���x���T�[�N���̔��a:%f", levelCircle.radius);
		DrawFormatString(0, 140, 0xFFFFFF, "ZC�L�[:�Z�j�̑��x�ύX");
		DrawFormatString(0, 160, 0xFFFFFF, "IP�L�[�Œ��j�̑��x��ύX");
		DrawFormatString(0, 180, 0xFFFFFF, "�J�����V�F�C�N:�X�y�[�X�L�[(�U���ʂ̒����͖�����)");
		DrawFormatString(0, 200, 0xff, "�`���[�g���A�����ǂ���:%d", isTutorial);
		DrawFormatString(0, 220, 0xff, "�`���[�g���A�����N���A�������ǂ���:%d", isTutorialClear);
		//DrawFormatString(0, 240, 0xFFFFFF, "�Z�j�̑��x:%f", hourHandSpeed + hourHandlevelSpeed * (level - 1));
		//DrawFormatString(0, 260, 0xFFFFFF, "���j�̑��x:%f", longHandSpeed);
		//DrawFormatString(0, 280, 0xFFFFFF, "�t���̑��x(�Z�j):%f", hourHandReverseSpeed);
		//DrawFormatString(0, 300, 0xFFFFFF, "�G�l�~�[�̃X�|�[���܂ł̎c�莞��:%d", spawnTimer);
		//DrawFormatString(0, 340, 0xFFFFFF, "�G�̑���:%d", enemys.size());
		//DrawFormatString(0, 320, 0xFFFFFF, "FPS");
		//DrawFormatString(0, 360, 0xFFFFFF, "�A�C�e�������񂾐�:%d", itemSandwichCount);
		//
		//DrawFormatString(0, 400, 0xFFFFFF, "�G�����񂾐�:%d", enemySandwichCount);
		//DrawFormatString(0, 420, 0xFFFFFF, "point:%d", point);

		/*SetFontSize(80);*/
		/*SetFontSize(16);*/
	}
}

void GameScene::TutorialSkip(bool flag)
{
	isTutorialSkip = flag;
}
