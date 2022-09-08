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
	// --�G�̃X�|�[���ʒu���m�肵�Ă���X�|�[��������܂ł̎���-- //
	delayMax = 20;

	// --���ɓG����������܂ł̊Ԋu-- //
	spawnInterval = 20;

	// --�G�̃X�|�[���x���̎c�莞��-- //
	spawnDelay = delayMax;

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
	level = 1;

	// --�o���l-- //
	point = 0;

	// --���x���ɂ���ĕK�v�Ȍo���l-- //
	int needPointCopy[10] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
	for (int i = 0; i < 10; i++) { needPoint[i] = needPointCopy[i]; }
#pragma endregion

#pragma region �G�t�F�N�g�֌W�ϐ��̏�����
	// --�G�̔��������Ƃ��̉~�̑傫���p-- //
	burstCircle = { {0.0f, 0.0f}, 0.0f };
#pragma endregion

#pragma region �摜�ǂݍ���
	// --���v��j�̕`��p�摜-- //
	whiteCircleGraph = LoadGraph("Resouces/whiteCircle.png");
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

}

// --�X�V����-- //
void GameScene::Update() {
#pragma region �j�̍��W�v�Z

	//L�{�^���ŒZ�j�̃X�e�[�g���u���]�v��
	if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::Normal) {
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
		}
	}

	//�X�e�[�g���ʏ�Ȃ璷�j�͎�����]
	if (longHand.state == State::Normal) {
		longHand.radian += longHandSpeed;
	}//�X�e�[�g���u���]�v�Ȃ�t��
	else if (longHand.state == State::Reverse) {
		//���x�͒Z�j�Ɠ���
		longHand.radian -= reverseSpeed;

		//���j�̊p�x��0�ɂȂ����璷�j�ƒZ�j�̃X�e�[�g��߂��A�p�x��������
		if (longHand.radian < reverseSpeed) {
			longHand.state = State::Normal;
			hourHand.state = State::Normal;
			longHand.radian = 0;
			//	hourHand.radian = 0;
			enemys.clear();
			LevelReset();
			// --�X�R�A���Z-- //
			Score::AddScore(1000);

			//�V�F�C�N
			camera.SetShakeCount(10);

			//�G�̃X�|�[���^�C�}�[�����Z�b�g
			spawnDelay = delayMax;
			spawnTimer = spawnInterval;

			//�Ռ��G�t�F�N�g���쐬
			CreateBreakEffect(clock.pos, 128);
		}
	}

	//360�x��������0�ɖ߂��A0�����������360���Z����
	longHand.radian = fmodf(longHand.radian, 360.0f);
	if (longHand.radian <= 0)longHand.radian += 360.0f;
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


#pragma endregion

#pragma region �v���C���[�X�V����
	player->Update(hourHand, clock, levelCircle.radius);
#pragma endregion

#pragma region �G�l�~�[�֌W�̏���
	// --�G�l�~�[�̃X�|�[������-- //
	//�Z�j���ʏ��ԂȂ�s��
	if (hourHand.state == State::Normal) {
		EnemySpawn();
	}

	// --�G�l�~�[�N���X�X�V����-- //
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Update(hourHand);

		//�Z�j�����]���[�h�Ȃ画����Ƃ�
		if (hourHand.state == State::Reverse) {
			//�Z�j�ƓG�̓����蔻��
			if (CollisionCtoL(enemys[i].GetCircle(), hourHand, reverseSpeed)) {
				enemys[i].OnCollison();
			}
		}

		//�����~�Ƃ̓����蔻��
		if (CollisionCtoC(enemys[i].GetCircle(), burstCircle)) {
			//���������A�C�e��������
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
#pragma endregion
}

// --�`�揈��-- //
void GameScene::Draw() {
#pragma region �v���C���[�`��
	player->Draw(camera);
#pragma endregion

#pragma region �G�l�~�[�`��
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Draw(camera);
	}
	
	//�`��p���W�錾
	Circle posC;
	Line posL;
	posC = { clock.pos + camera.GetPos(),clock.radius };
	//DrawCircle(posC, 0xffffff, false);
	posL.start = {longHand.start + camera.GetPos()};
	posL.end = {longHand.end + camera.GetPos()};
	posL.color = longHand.color;
	DrawLine(posL, 4);
	posL.start = { hourHand.start + camera.GetPos() };
	posL.end = { hourHand.end + camera.GetPos() };
	posL.color = hourHand.color;
	DrawLine(posL);
	posC = { levelCircle.pos + camera.GetPos(), levelCircle.radius };
	DrawCircle(posC, 0xFFFFFF, false);

	posC = { burstCircle.pos + camera.GetPos(),burstCircle.radius };
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawCircle(posC, 0xff0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Draw(camera);
	}
#pragma endregion

#pragma region ���v�̊O�g�̕`��
	// --���v�̊O�g�̍��W�ƃJ�����V�F�C�N�̍��W������Circle�ϐ�-- //
	Circle clockCircle = { clock.pos + camera.GetPos(), clock.radius };

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(119, 28, 28);

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

	// --���j�̕`��-- //
	DrawLine(longHandLine, 4);
#pragma endregion

#pragma region �Z�j�̕`��
	// --�Z�j�̍��W�ƃJ�����V�F�C�N�̍��W������Line�ϐ�-- //
	Line hourHandLine;
	hourHandLine.start = { hourHand.start + camera.GetPos() };
	hourHandLine.end = { hourHand.end + camera.GetPos() };
	hourHandLine.color = hourHand.color;

	// --�Z�j�̕`��-- //
	DrawLine(hourHandLine);
#pragma endregion

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
	DrawLine(line, 6);
#pragma endregion

#pragma region �G�t�F�N�g�`��
	for (int i = 0; i < breakEffects.size(); i++) {
		breakEffects[i].Draw(camera);
	}
#pragma endregion

#pragma region �f�o�b�O�`��
	DrawFormatString(0, 80, 0xFFFFFF, "AD�L�[:���x���T�[�N���̔��a�ύX");
	DrawFormatString(0, 100, 0xFFFFFF, "���x���T�[�N���̔��a:%f", levelCircle.radius);
	DrawFormatString(0, 120, 0xFFFFFF, "ZC�L�[:�Z�j�̑��x�ύX");
	DrawFormatString(0, 140, 0xFFFFFF, "�Z�j�̑��x:%f", hourHandSpeed);
	DrawFormatString(0, 160, longHand.color, "longHand(���j)�̏�� x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 180, hourHand.color, "hourHand(�Z�j)�̏�� x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
	DrawFormatString(0, 280, 0xFFFFFF, "IP�L�[�Œ��j�̑��x��ύX");
	DrawFormatString(0, 300, 0xFFFFFF, "���j�̑��x:%f", longHandSpeed);
	DrawFormatString(0, 320, 0xFFFFFF, "�J�����V�F�C�N:�X�y�[�X�L�[(�U���ʂ̒����͖�����)");
	DrawFormatString(0, 340, 0xFFFFFF, "�G�l�~�[�̃X�|�[���܂ł̎c�莞��:%d", spawnTimer);
	DrawFormatString(0, 360, 0xFFFFFF, "�G�l�~�[�̃X�|�[���x������:%d", spawnDelay);
	/*SetFontSize(80);*/
	DrawFormatString(1280 / 2 - 20, 960 / 2 - 40, 0xFFFFFF, "%d", level);
	/*SetFontSize(16);*/
#pragma endregion
}

// --�G�̃X�|�[������-- //
void GameScene::EnemySpawn() {
	//�X�|�[���^�C�}�[�����炷
	if (spawnTimer > 0) {
		spawnTimer--;
		//�^�C�}�[��0�ɂȂ�����X�|�[���ʒu�����߂�
	}
	else if (spawnTimer == 0) {


		//�X�|�[���^�C�}�[��0�ɂȂ����u�Ԃ݈̂ʒu�����߂�(�Z�j�̈ʒu���Q�Ƃ��邽��
		if (spawnDelay == delayMax) {
			enemyLength = Random(levelCircle.radius, hourHand.length);
			float rad = hourHand.radian - 90;
			enemyPos.x = (enemyLength * cosf(rad / 180 * PI)) + clock.pos.x;
			enemyPos.y = (enemyLength * sinf(rad / 180 * PI)) + clock.pos.y;
			//�f�B���C�^�C�}�[�����炷
			spawnDelay--;
		}//�f�B���C�^�C�}�[��0�o�Ȃ��Ȃ�
		else if (spawnDelay > 0) {
			//�f�B���C�^�C�}�[�����炷
			spawnDelay--;
		}//�f�B���C�^�C�}�[��0�ɂȂ�������W���m��
		else if (spawnDelay == 0) {
				enemys.push_back({ enemyPos, 8.0f });
				if (Random(0, 100) <= enemySpawnRate) {
					//5%�̊m���œG�Ƃ��ăX�|�[��
					enemys.back().SetState(State::Enemy);
				}
				else {//����ȊO��95%�ŃA�C�e���Ƃ��ăX�|�[��
					enemys.back().SetState(State::Item);
				}
				//�^�C�}�[�����Z�b�g
				spawnTimer = spawnInterval;
				spawnDelay = delayMax;
				
			
		}
	}
}

// --���@�ƓG�̓����蔻�菈��-- //
void GameScene::Collision() {
	// --���@�ƓG�̓����蔻����s��-- //
	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionCtoC(player->player, enemys[i].enemy)) {
			//�G�̃X�e�[�g��Item�Ȃ����
			if (enemys[i].GetState() == State::Item) {
			enemys.erase(enemys.begin() + i);
			point++;
			Score::AddScore(100);
			}//�G�̃X�e�[�g��enemy�Ȃ烌�x�������炵�ď��ł�����
			else if (enemys[i].GetState() == State::Enemy) {
				//���x���������āA�����T�[�N�����o��
				if (level > 1) {
					level--;
				}
				burstCircle.pos = enemys[i].GetCircle().pos;
				burstCircle.radius = 96.0f;

				enemys.erase(enemys.begin() + i);
			}
		}
	}

	// --���x���T�[�N���ƃG�l�~�[�̓����蔻��-- //
	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionCtoC(levelCircle, enemys[i].enemy)) {
	
				enemys.erase(enemys.begin() + i);
			
			
		}
	}
}

// --���x��-- //
void GameScene::LevelUpdate() {
#pragma region �o���l�ɂ���ă��x����ς��鏈��
	// --���݂̃��x���̕K�v�o���l����ɓ������烌�x�����グ��-- //
	if (needPoint[level - 1] == point) {
		level++;
		point = 0;
	}
#pragma endregion
}

// --���x�����Z�b�g-- //
void GameScene::LevelReset() {
	level = 1;
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