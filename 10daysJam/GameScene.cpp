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
	vecAtoB.x = cB.x - cA.x;
	vecAtoB.y = cB.y - cA.y;
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
GameScene::GameScene() : clock{ 640, 480, 416 },
longHand{ {640, 480}, {640, 0}, clock.radius, 180, 0xFF0000},
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 180, 0xFF }
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

	for (int i = 0; i < 10; i++) {
		enemy[i].radius = 8;
	}
}

// --�X�V����-- //
void GameScene::Update() {



#pragma region �j�̍��W�v�Z

	//���j���펞��]
	longHand.radian -= 0.5f;
	//-360�x��������0�ɖ߂�
	longHand.radian = fmodf(longHand.radian, 360.0f);
	//�j�̊p�x�ŏI�_���W���v�Z
	longHand.end.x = (longHand.length * sinf(longHand.radian / 180 * PI)) + clock.x;
	longHand.end.y = (longHand.length * cosf(longHand.radian / 180 * PI)) + clock.y;

	//���j���펞��]
	//hourHand.radian -= 2.0f;
	hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;

	//-360�x��������0�ɖ߂�
	hourHand.radian = fmodf(hourHand.radian, 360.0f);
	//�j�̊p�x�ŏI�_���W���v�Z
	hourHand.end.x = (hourHand.length * sinf(hourHand.radian / 180 * PI)) + clock.x;
	hourHand.end.y = (hourHand.length * cosf(hourHand.radian / 180 * PI)) + clock.y;


#pragma endregion

	// --�v���C���[�N���X�X�V����-- //
	player->Update(hourHand, clock);

#pragma region �G�̔�������

	//�X�|�[���^�C�}�[�����炷
	if (spawnTimer > 0) {
		spawnTimer--;
		//�^�C�}�[��0�ɂȂ�����X�|�[���ʒu�����߂�
	}
	else if (spawnTimer == 0) {


		//�X�|�[���^�C�}�[��0�ɂȂ����u�Ԃ݈̂ʒu�����߂�(�Z�j�̈ʒu���Q�Ƃ��邽��
		if (spawnDelay == delayMax) {
			enemyLength = Random(0.0f, hourHand.length);
			enemyPos.x = (enemyLength * sinf(hourHand.radian / 180 * PI)) + clock.x;
			enemyPos.y = (enemyLength * cosf(hourHand.radian / 180 * PI)) + clock.y;
			//�f�B���C�^�C�}�[�����炷
			spawnDelay--;
		}//�f�B���C�^�C�}�[��0�o�Ȃ��Ȃ�
		else if (spawnDelay > 0) {
			//�f�B���C�^�C�}�[�����炷
			spawnDelay--;
		}//�f�B���C�^�C�}�[��0�ɂȂ�������W���m��
		else if (spawnDelay == 0) {
			for (int i = 0; i < 10; i++) {
				enemy[i].x = enemyPos.x;
				enemy[i].y = enemyPos.y;
				//�^�C�}�[�����Z�b�g
				spawnTimer = spawnInterval;
				//spawnDelay = delayMax;
				break;
			}
		}
	}
#pragma endregion

#pragma region ���@�ƓG�̓����蔻��(���̂Ƃ���~�Ɖ~�̔���)
	if (CollisionCtoC(player->GetPlayer(), enemy[0])) {
		DrawFormatString(500, 500, 0xff00ff, "�Փ�");
	}
#pragma endregion
}

// --�`�揈��-- //
void GameScene::Draw() {
	// --�v���C���[�̕`�揈��-- //
	player->Draw();
	DrawCircle(clock, 0xffffff, false);
	DrawLine(longHand, 4);
	DrawLine(hourHand);
	DrawFormatString(0, 20, 0x00ffff, "R�L�[:���x���Z�b�g");
	DrawFormatString(0, 40, longHand.color, "longHand(���j)�̏�� x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 60, hourHand.color, "hourHand(�Z�j)�̏�� x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
	for (int i = 0; i < 10; i++) {
		DrawCircle(enemy[i], 0xffff00, true);
	}
}