#include "Player.h"

// --�C���X�^���X��NULL����-- //
Player* Player::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Player* Player::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new Player();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�R���X�g���N�^-- //
Player::Player() {

}

// --�f�X�g���N�^-- //
Player::~Player() {

}

// --����������-- //
void Player::Initialize() {

}

// --�X�V����-- //
void Player::Update() {

}

// --�`�揈��-- //
void Player::Draw() {

}