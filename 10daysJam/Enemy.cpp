#include "Enemy.h"

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

}

// --�X�V����-- //
void Enemy::Update() {

}

// --�`�揈��-- //
void Enemy::Draw() {

}