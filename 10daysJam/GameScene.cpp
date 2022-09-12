#include "GameScene.h"
#include "SceneManager.h"
#include "Score.h"
using namespace Util;
using namespace std;

// --�C���X�^���X��NULL����-- //
GameScene* GameScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
GameScene* GameScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new GameScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�C���X�^���X���-- //
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

	// --�Z�j-- //
	hourHand = { {640.0f, 480.0f}, {640.0f, 32.0f}, clock.radius - 32.0f, 0, 0xFF };

	// --�Z�j�̑��x-- //
	hourHandSpeed = 0.8f;

	// --���x���ɂ��Z�j�̑��x�̏オ�蕝-- //
	hourHandlevelSpeed = 0.5f;

	// --�Z�j���t��肷��Ƃ��̑��x-- //
	reverseSpeed = 4.0f;
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
	int needPointCopy[10] = { 2, 4, 8, 10, 10, 10, 10, 10, 10, 10 };
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
#pragma endregion
}

// --�f�X�g���N�^-- //
GameScene::~GameScene() {
#pragma region �N���X�̃C���X�^���X���
	player->Relese();
#pragma endregion
}

// --����������-- //
void GameScene::Initialize() {
	star.start = clock.pos;
	star.radian = 0;
	star.length = hourHand.length + 96;
	star.end = { star.start.x + star.length,star.start.y + star.length };

	//�ʒu�p�̃��W�A��
	float radStar = star.radian - 90;
	//���W�v�Z
	star.end.x = (star.length * cosf(radStar / 180 * PI)) + star.start.x;
	star.end.y = (star.length * sinf(radStar / 180 * PI)) + star.start.y;

	//�p�[�e�B�N���̐��Ƃ�
	maxStarparticle = 32;
	for (int i = 0; i < maxStarparticle; i++) {
		Particle newParticle;
		newParticle.SetParent(star.end);
		newParticle.SetState(ParticleState::Endress);
		newParticle.Initialize();
		starParticles.push_back(newParticle);
	}

	//�I�[�v�j���O���n�߂�
	isOpening = true;
	nowTime = 0;
	//�I�[�v�j���O�p�ϐ��̏�����

	//�G�̃X�|�[�����Ԃ̃u��

	for (int i = 0; i < opEnemyMax; i++) {
		//�G�̃X�|�[���t���[���������_����
		int spawnFrame;
		spawnFrame = 30 + i * 50;
		opSpawnFrame.push_back(spawnFrame);
	}
}

// --�X�V����-- //
void GameScene::Update() {
#pragma region �j�̍��W�v�Z

	//�I�[�v�j���O����
	if (isOpening) {
		OpeningUpdate();
	} 
	else {
		//L�{�^���ŒZ�j�̃X�e�[�g���u���]�v��
		if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::Normal && level > 0) {
			hourHand.state = State::Reverse;
		}

		//�X�e�[�g���ʏ�Ȃ�Z�j�͎�����]
		if (hourHand.state == State::Normal) {
			hourHand.radian += hourHandSpeed + hourHandlevelSpeed * (level - 1);

			//�C�ӂ̃L�[�ŒZ�j�𓮂���(�f�o�b�O�p)
			//hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
		}//�X�e�[�g�����]���Ă���Ȃ�Z�j���t��������
		else if (hourHand.state == State::Reverse) {
			hourHand.radian -= reverseSpeed;
			//�Z�j�����j�ɒǂ������璷�j�̃X�e�[�g���u���]�v��
			if (hourHand.radian < longHand.radian + reverseSpeed && hourHand.radian > longHand.radian - reverseSpeed) {
				longHand.state = State::Reverse;
				//�Z�j�̃X�e�[�g���Ƃ߂�
				hourHand.state = State::Stop;

				//�͂��񂾃I�u�W�F�N�g�̐��Ŗ߂��͂𑝂₷
				reverseTime += level * 1.5;
				reverseTime += itemSandwichCount / 2 * level;
				reverseTime += enemySandwichCount * 2 * level;

				//�X�R�A�����Z�A�͂��񂾐������Z�b�g
				Score::AddScore(300 * itemSandwichCount);
				Score::AddScore(500 * enemySandwichCount);
				itemSandwichCount = 0;
				enemySandwichCount = 0;

				LevelReset();

				//�͂��񂾏u�Ԃɂ͂��܂�Ă���G�����ł�����
				for (int i = enemys.size() - 1; i >= 0; i--) {
					if (enemys[i].GetState() == State::Reverse) {
						enemys[i].Death();
						//enemys.erase(enemys.begin() + i);
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
				longHand.radian -= reverseSpeed * 3.0f;
				//���j�̊p�x��0�ɂȂ����璷�j�ƒZ�j�̃X�e�[�g��߂��A�p�x��������
				if (longHand.radian < reverseSpeed) {
					longHand.state = State::Normal;
					hourHand.state = State::Normal;
					longHand.radian = 0;
					//	hourHand.radian = 0;
					//�X�e�[�g���f�X�łȂ��G�͍폜�A�f�X�͂��̂܂�
					for (int i = enemys.size() - 1; i >= 0; i--) {
						if (enemys[i].GetState() != State::Death) {
							enemys.erase(enemys.begin() + i);
						}
					}
					LevelReset();
					// --�X�R�A���Z-- //
					Score::AddScore(1000);
					//�V�F�C�N
					camera.SetShakeCount(10);
					//�G�̃X�|�[���^�C�}�[�����Z�b�g
					spawnTimer = spawnInterval;
					//�Ռ��G�t�F�N�g���쐬
					CreateBreakEffect(clock.pos, 128);
					//�߂��͂����Z�b�g
					reverseTime = 0;

					//�G��5�̃X�|�[��������
					for (int i = 0; i < 5; i++) {
						EnemySpawn(Random(0.0f, 360.0f));
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
					EnemySpawn(Random(0.0f, 360.0f));
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
			// --�V�[����ς���-- //
			SceneManager::SetScene(RESULTSCENE);
		}

#pragma endregion


		if (star.state == State::Normal) {
			star.radian += 0.4f;
		}

		//�p�x������A�����𒴂�����߂�
		star.radian = fmodf(star.radian, 360.f);
		if (star.radian <= 0)star.radian += 360.0f;
		//�ʒu�p�̃��W�A��
		float radStar = star.radian - 90;
		//���W�v�Z
		star.end.x = (star.length * cosf(radStar / 180 * PI)) + star.start.x;
		star.end.y = (star.length * sinf(radStar / 180 * PI)) + star.start.y;

		//�p�[�e�B�N���̍X�V
		for (int i = 0; i < starParticles.size(); i++) {
			starParticles[i].SetParent(star.end);

			starParticles[i].Update();
		}


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
			enemys[i].Update(hourHand);
			//�Z�j�����]���[�h�Ȃ画����Ƃ�
			if (hourHand.state == State::Reverse) {
				//�Z�j�ƓG�̓����蔻��
				if (CollisionCtoL(enemys[i].GetCircle(), hourHand, reverseSpeed)) {
					//�I�u�W�F�N�g�̃X�e�[�g���܂��u���]�v�łȂ��Ȃ瓖���蔻��̃R�[���o�b�N�֐����Ăяo���A���񂾐����J�E���g����
					if (enemys[i].GetState() != State::Reverse) {
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
						}//�G�Ȃ�A�C�e����
						else if (enemys[i].GetState() == State::Enemy) {
							enemys[i].SetState(State::Item);
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
		}
#pragma endregion
	}
}

// --�`�揈��-- //
void GameScene::Draw() {
	//���ݎ��Ԃ��Q�Ƃ��ă��C�g�A�b�v
	int brightLongHand = 0;
	brightLongHand = (256.0f / 25.0f) * (nowTime - 175) + 16.0f;
	int brightClock = 0;
	brightClock = (256.0f / 25.0f) * (nowTime - 125) + 16.0f;
	int brightHourHand = 0;
	brightHourHand = (256.0f / 25.0f) * (nowTime - 75) + 16.0f;

#pragma region �v���C���[�`��
	player->Draw(camera,brightHourHand);
#pragma endregion

#pragma region �G�l�~�[�`��
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Draw(camera);
	}

	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Draw(camera);
	}
#pragma endregion

#pragma region ���v�̊O�g�̕`��
	// --���v�̊O�g�̍��W�ƃJ�����V�F�C�N�̍��W������Circle�ϐ�-- //
	Circle clockCircle = { clock.pos + camera.GetPos(), clock.radius };



	SetDrawBlendMode(DX_BLENDMODE_ADD, brightClock);
	SetDrawBright(255, 255, 255);

	// --���v�̊O�g�̕`��-- //
	for (int i = 0; i < 1440; i++) {
		DrawGraphF(
			clockCircle.pos.x + cosf(Degree2Radian(i * 0.25f)) * clockCircle.radius - 16,
			clockCircle.pos.y + sinf(Degree2Radian(i * 0.25f)) * clockCircle.radius - 16,
			whiteCircleGraph, true);
	}

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion

#pragma region ���j�̕`��
	// --���j�̍��W�ƃJ�����V�F�C�N�̍��W������Line�ϐ�-- //
	Line longHandLine;
	longHandLine.start = { longHand.start + camera.GetPos() };
	longHandLine.end = { longHand.end + camera.GetPos() };
	longHandLine.color = longHand.color;

	

	SetDrawBlendMode(DX_BLENDMODE_ADD, brightLongHand);
	SetDrawBright(119, 28, 28);

	// --���j�̕`��-- //
	for (int i = levelCircle.radius; i < longHand.length; i++) {
		DrawRotaGraph(
			longHandLine.start.x + cosf(Degree2Radian(longHand.radian - 90)) * (i),
			longHandLine.start.y + sinf(Degree2Radian(longHand.radian - 90)) * (i),
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

	SetDrawBlendMode(DX_BLENDMODE_ADD, 256);
	for (int i = 0; i < starParticles.size(); i++) {
		starParticles[i].Draw(camera);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//�p�[�e�B�N���X�^�[�̕`��
	Circle starC;
	starC = { star.end + camera.GetPos(),10 };
	DrawCircle(starC, 0xffffff, true);


#pragma region ���x���T�[�N���̕`��
	// --���x���T�[�N���̍��W�ƃJ�����V�F�C�N�̍��W������Circle�ϐ�-- //
	Circle circle;
	circle = { levelCircle.pos + camera.GetPos(), levelCircle.radius };

	// --���x���T�[�N���̕`��-- //
	DrawCircle(circle, 0xFFFFFF, false);
#pragma endregion

#pragma region �ڈ�p0���̐j�̕`��
	// --0���̐j�̍��W�ƃJ�����V�F�C�N�̍��W������Circle�ϐ�-- //
	Line line;
	line.start = { clock.pos + camera.GetPos() };
	line.end = { clock.pos.x + camera.GetPos().x, clock.pos.y - clock.radius + 16 + camera.GetPos().y };
	line.color = 0x60FFBF;

	// --0���̐j�`��-- //
	//DrawLine(line, 6);
#pragma endregion

#pragma region �G�̔����~�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawCircle(burstCircle, 0xff0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);
#pragma endregion

#pragma region �G�t�F�N�g�`��
	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Draw(camera);
	}
#pragma endregion

	//�J�E���g�_�E���̕`��
	//����
	int countDownBright;
	int graphNum = (nowTime - animationTime) / 50 *(nowTime >= animationTime);	//�摜�z��̏��Ԃ�321�Ȃ炱����
	if (graphNum > 2)graphNum = 2;					//1,2,3�Ȃ炱����
	int graphNumR = 2 - graphNum;

	countDownBright = (256-( (256.0f / 50.0f) * (nowTime - (animationTime + ( graphNum *50)) ))) * (nowTime >= animationTime);
	SetDrawBlendMode(DX_BLENDMODE_ADD, countDownBright);
	// --�摜�`���������-- //
	DrawGraphF(589.0f, 412.5f, countNumGraph[graphNum], true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, countDownBright);

	DrawFormatString(1280 / 2 - 20, 960 / 2 - 40, 0xFFFFFF, "%d", level);

#pragma region �f�o�b�O�`��
	if (SceneManager::GetDebugMode() == true) {
		DrawFormatString(0, 100, 0xFFFFFF, "AD�L�[:���x���T�[�N���̔��a�ύX");
		DrawFormatString(0, 120, 0xFFFFFF, "���x���T�[�N���̔��a:%f", levelCircle.radius);
		DrawFormatString(0, 140, 0xFFFFFF, "ZC�L�[:�Z�j�̑��x�ύX");
		DrawFormatString(0, 160, 0xFFFFFF, "�Z�j�̑��x:%f", hourHandSpeed);
		DrawFormatString(0, 180, longHand.color, "longHand(���j)�̏�� x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
		DrawFormatString(0, 200, hourHand.color, "hourHand(�Z�j)�̏�� x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
		DrawFormatString(0, 220, 0xFFFFFF, "IP�L�[�Œ��j�̑��x��ύX");
		DrawFormatString(0, 240, 0xFFFFFF, "���j�̑��x:%f", longHandSpeed);
		DrawFormatString(0, 260, 0xFFFFFF, "�J�����V�F�C�N:�X�y�[�X�L�[(�U���ʂ̒����͖�����)");
		DrawFormatString(0, 280, 0xFFFFFF, "�G�l�~�[�̃X�|�[���܂ł̎c�莞��:%d", spawnTimer);
		DrawFormatString(0, 300, 0xFFFFFF, "�G�̑���:%d", enemys.size());
		DrawFormatString(0, 320, 0xFFFFFF, "FPS");
		DrawFormatString(0, 340, 0xFFFFFF, "�A�C�e�������񂾐�:%d", itemSandwichCount);
		DrawFormatString(0, 360, 0xFFFFFF, "�G�����񂾐�:%d", enemySandwichCount);
		/*SetFontSize(80);*/
		/*SetFontSize(16);*/
	}
#pragma endregion
}

// --�G�̃X�|�[������-- //
void GameScene::EnemySpawn(float radian) {

	enemyLength = Random(levelCircle.radius, hourHand.length);
	float rad = radian - 90;
	enemyPos.x = (enemyLength * cosf(rad / 180 * PI)) + clock.pos.x;
	enemyPos.x -= (10.0f * cosf((rad + 90) / 180 * PI));
	enemyPos.y = (enemyLength * sinf(rad / 180 * PI)) + clock.pos.y;
	enemyPos.y -= (10.0f * sinf((rad + 90) / 180 * PI));
	Enemy newEnemy;
	//Circle newPos = {enemyPos,8.0f}
	newEnemy.SetObj({ {enemyPos} , 8.0f });
	newEnemy.Initialize();
	enemys.push_back(newEnemy);
	if (Random(0, 100) <= enemySpawnRate) {
		//5%�̊m���œG�Ƃ��ăX�|�[��
		enemys.back().SetState(State::Enemy);
	}
	else {//����ȊO��95%�ŃA�C�e���Ƃ��ăX�|�[��
		enemys.back().SetState(State::Item);
	}
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
			}//�G�̃X�e�[�g��enemy�Ȃ烌�x�������炵�ď��ł�����
			else if (enemys[i].GetState() == State::Enemy) {
				//���x���������āA�����T�[�N�����o��
				if (level > 1) {
					level--;
				}
				burstCircle.pos = enemys[i].GetCircle().pos + camera.GetPos();
				burstCircle.radius = 96.0f;
				//�G������
				enemys.erase(enemys.begin() + i);
				//�t������͂����Z�b�g
				reverseTime = 0;
			}
		}
	}

	// --���x���T�[�N���ƃG�l�~�[�̓����蔻��-- //
	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionCtoC(levelCircle, enemys[i].obj)) {
			//�G�̃X�e�[�g�����S�łȂ��Ȃ�(���S���o���łȂ��Ȃ�)
			if (enemys[i].GetState() != State::Death) {
				enemys.erase(enemys.begin() + i);
			}
		}
	}
}

// --���x��-- //
void GameScene::LevelUpdate() {
#pragma region �o���l�ɂ���ă��x����ς��鏈��
	// --���݂̃��x���̕K�v�o���l����ɓ������烌�x�����グ��-- //
	if (needPoint[level] == point && level < 5) {
		level++;
		point = 0;
	}

	//���x���œG�̏o�����𒲐�
	switch (level)
	{
	case 0:
		enemySpawnRate = 0.0f;
		spawnInterval = 100;
		//�f�o�b�O�p���ύX
		/*spawnInterval = 40;*/
		break;
	case 1:
		enemySpawnRate = 15.0f;
		spawnInterval = 40;
		break;
	case 2:
		enemySpawnRate = 19.0f;
		spawnInterval = 30;
		break;
	case 3:
		enemySpawnRate = 23.0f;
		spawnInterval = 38;
		break;
	case 4:
		enemySpawnRate = 26.0f;
		spawnInterval = 30;
		break;
	case 5:
		enemySpawnRate = 28.0f;
		spawnInterval = 25;
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
		BreakEffect newEffect{};
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
		reverseSpeed = 360.0f / 250.0f;

		hourHand.radian -= reverseSpeed;
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
			enemys[i].Update(hourHand);
		}
	if (nowTime == openingTime) {
		isOpening = false;
	}
}

