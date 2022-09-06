#include "Enemy.h"
using namespace Util;

// --�C���X�^���X��NULL����-- //
Enemy* Enemy::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Enemy* Enemy::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new Enemy();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�R���X�g���N�^-- //
Enemy::Enemy() {

}

// --�f�X�g���N�^-- //
Enemy::~Enemy() {

}

// --����������-- //
void Enemy::Initialize() {
	delayMax = 1;
	spawnDelay = delayMax;
	spawnInterval = 20;
	spawnTimer = spawnInterval;
}

// --�X�V����-- //
void Enemy::Update(Line hourHand, Circle clock) {
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
			enemyPos.x = (enemyLength * cosf(rad / 180 * PI)) + clock.x;
			enemyPos.y = (enemyLength * sinf(rad / 180 * PI)) + clock.y;
			//�f�B���C�^�C�}�[�����炷
			spawnDelay--;
		}//�f�B���C�^�C�}�[��0�o�Ȃ��Ȃ�
		else if (spawnDelay > 0) {
			//�f�B���C�^�C�}�[�����炷
			spawnDelay--;
		}//�f�B���C�^�C�}�[��0�ɂȂ�������W���m��
		else if (spawnDelay == 0) {
			for (int i = 0; i < 10; i++) {
				enemys.push_back({enemyPos.x, enemyPos.y, 8});
				//�^�C�}�[�����Z�b�g
				spawnTimer = spawnInterval;
				spawnDelay = delayMax;
				break;
			}
		}
	}
}

// --�`�揈��-- //
void Enemy::Draw() {
	for (int i = 0; i < enemys.size(); i++) {
		DrawCircle(enemys[i], 0xffff00, true);
	}
}

void Enemy::AllEnemyDeath()
{
	enemys.clear();
}
