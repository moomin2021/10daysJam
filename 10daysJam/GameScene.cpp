#include "GameScene.h"
#include "SceneManager.h"
using namespace Util;

// --�C���X�^���X��NULL����-- //
GameScene* GameScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
GameScene* GameScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new GameScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

bool GameScene::CollisionCtoC(Circle cA, Circle cB)
{
	bool flag;
	Vector2 vecAtoB;
	float radius;
	vecAtoB.x = cB.pos.x - cA.pos.x;
	vecAtoB.y = cB.pos.y - cA.pos.y;
	radius = cA.radius + cB.radius;

	if (vecAtoB.length() <= radius) {
		flag = true;
	}
	else {
		flag = false;
	}

	return flag;
}

// --�R���X�g���N�^-- //
GameScene::GameScene() : clock{ {640, 480}, 416 },
longHand{ {640, 480}, {640, 0}, clock.radius, 0, 0xFF0000},
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 0, 0xFF }
{
	// --���̓N���X�C���X�^���X�擾-- //
	input = Input::GetInstance();

	// --�v���C���[�N���X�C���X�^���X�擾-- //
	player = Player::GetInstance();

	pad = JoyPadInput::GetInstance();
}

// --�f�X�g���N�^-- //
GameScene::~GameScene() {
	delete player;
}

// --����������-- //
void GameScene::Initialize() {
	delayMax = 1;
	spawnDelay = delayMax;
	spawnInterval = 20;
	spawnTimer = spawnInterval;
}

// --�X�V����-- //
void GameScene::Update() {



#pragma region �j�̍��W�v�Z

	//L�{�^���ŒZ�j�̃X�e�[�g���u���]�v��
	if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::normal) {
		hourHand.state = State::reverse;
	}

	//�X�e�[�g���ʏ�Ȃ�Z�j�͎�����]
	if (hourHand.state == State::normal) {
		hourHand.radian += 2.0f;

		//�C�ӂ̃L�[�ŒZ�j�𓮂���(�f�o�b�O�p)
		hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
	}//�X�e�[�g�����]���Ă���Ȃ�Z�j���t��������
	else if (hourHand.state == State::reverse) {
		hourHand.radian -= reverseSpd;
		//�Z�j�����j�ɒǂ������璷�j�̃X�e�[�g���u���]�v��
		if (hourHand.radian < longHand.radian + reverseSpd && hourHand.radian > longHand.radian - reverseSpd){
			longHand.state = State::reverse;
		}
	}

	//�X�e�[�g���ʏ�Ȃ璷�j�͎�����]
	if (longHand.state == State::normal) {
		longHand.radian += 0.5f;
	}//�X�e�[�g���u���]�v�Ȃ�t��
	else if (longHand.state == State::reverse) {
		//���x�͒Z�j�Ɠ���
		longHand.radian -= reverseSpd;
		
		//���j�̊p�x��0�ɂȂ����璷�j�ƒZ�j�̃X�e�[�g��߂��A�p�x��������
		if (longHand.radian < reverseSpd) {
			longHand.state = State::normal;
			hourHand.state = State::normal;
			longHand.radian = 0;
			hourHand.radian = 0;
			enemys.clear();
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
	float radH = hourHand.radian -90;

	//�j�̊p�x�ŏI�_���W���v�Z
	longHand.end.x = (longHand.length * cosf(radL / 180 * PI)) + clock.pos.x;
	longHand.end.y = (longHand.length * sinf(radL / 180 * PI)) + clock.pos.y;
	//�j�̊p�x�ŏI�_���W���v�Z
	hourHand.end.x = (hourHand.length * cosf(radH  / 180 * PI)) + clock.pos.x;
	hourHand.end.y = (hourHand.length * sinf(radH  / 180 * PI)) + clock.pos.y;


#pragma endregion

	// --�v���C���[�N���X�X�V����-- //
	player->Update(hourHand, clock);

	// --�G�l�~�[�N���X�X�V����-- //
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Update();
	}

	// --�G�l�~�[�̃X�|�[������-- //
	EnemySpawn();
}

// --�`�揈��-- //
void GameScene::Draw() {
	// --�v���C���[�̕`�揈��-- //
	player->Draw();
	
	// --�G�l�~�[�̕`�揈��-- //
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Draw();
	}

	DrawCircle(clock, 0xffffff, false);
	DrawLine(longHand, 4);
	DrawLine(hourHand);
	DrawFormatString(0, 20, 0x00ffff, "R�L�[:���x���Z�b�g");
	DrawFormatString(0, 40, longHand.color, "longHand(���j)�̏�� x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 60, hourHand.color, "hourHand(�Z�j)�̏�� x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);

	//�ڈ�p�O���̐j
	DrawLine(clock.pos.x, clock.pos.y, clock.pos.x, clock.pos.y - clock.radius + 16, 0x60ffbf, 6);
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
			enemyLength = Random(0.0f, hourHand.length);
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
			for (int i = 0; i < 10; i++) {
				enemys.push_back({ enemyPos, 8.0f });
				//�^�C�}�[�����Z�b�g
				spawnTimer = spawnInterval;
				spawnDelay = delayMax;
				break;
			}
		}
	}
}

// --���@�ƓG�̓����蔻�菈��-- //
//void GameScene::PlayerAndEnemyCol() {
//	// --���@�ƓG�̓����蔻����s��-- //
//	for (int i = 0; i < enemy->enemys.size();i++) {
//		if (CollisionCtoC(player->player, enemy->enemys[i])) {
//			enemy->enemys.erase(enemy->enemys.begin() + i);
//		}
//	}
//}