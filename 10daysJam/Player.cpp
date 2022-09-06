#include "Player.h"
#include "DxLib.h"
using namespace Util;
#include "GameScene.h"

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
Player::Player() : player{ 0, 0, 16 }, playerSpd(2.0f), playerPos(0){
	input = Input::GetInstance();
}

// --�f�X�g���N�^-- //
Player::~Player() {

}

// --����������-- //
void Player::Initialize() {

}

// --�X�V����-- //
void Player::Update(Line hourHand, Circle clock) {
#pragma region ���@�ړ��֌W
	//���@�ړ�
	if (input->IsPress(KEY_INPUT_A) || input->IsPress(KEY_INPUT_S) || input->IsPress(KEY_INPUT_W) || input->IsPress(KEY_INPUT_D)) {

		//AD�L�[�ŒZ�j��ł̈ʒu��ύX
		playerPos += ((input->IsPress(KEY_INPUT_D) - input->IsPress(KEY_INPUT_A)) * playerSpd);
		//�ő�l�͒Z�j�̒���
		if (playerPos > hourHand.length)playerPos = hourHand.length;

	}

	//�Z�j��ł̎��@�̈ʒu���Q�Ƃ��Ď��@���W�v�Z
	//���@�͒Z�j��Ɉʒu����̂ŁA�p�x�͒Z�j�̂��̂��g��
	player.x = (playerPos * sinf(hourHand.radian / 180 * PI)) + clock.x;
	player.y = (playerPos * cosf(hourHand.radian / 180 * PI)) + clock.y;


	//�A���[�L�[�Ŏ��@���x�ύX
	playerSpd += ((input->IsPress(KEY_INPUT_E) - input->IsPress(KEY_INPUT_Q)) * 0.2f);
	if (input->IsPress(KEY_INPUT_R)) playerSpd = 2.0f;

#pragma endregion
}

// --�`�揈��-- //
void Player::Draw() {
	DrawCircle(player, 0xffffff, true);
}