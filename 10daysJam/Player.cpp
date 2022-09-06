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
	pad = JoyPadInput::GetInstance();
}

void Player::SetState(State state_)
{
	state = state_;
}

// --�f�X�g���N�^-- //
Player::~Player() {

}

// --����������-- //
void Player::Initialize() {
	//��Ԃ͒ʏ��
	state = State::normal;
}

// --�X�V����-- //
void Player::Update(Line hourHand, Circle clock) {

	float range = 60.0f;

#pragma region ���@�ړ��֌W
	// --�Z�j�̊p�x�����߂�-- //
	Vector2 lStickVec = {(float)pad->GetLeftStickX(), -(float)pad->GetLeftStickY()};
	float stickAngle = lStickVec.dot(Vector2(0, 1)) / (lStickVec.length() * Vector2(0, 1).length());
	stickAngle = acos(stickAngle);
	stickAngle = Util::Radian2Degree(stickAngle);
	if (pad->GetLeftStickX() < 0) {
		stickAngle = 180 + (180 - stickAngle);
	}

	Vector2 hourHandVec = { hourHand.end.x - hourHand.start.x, -(hourHand.end.y - hourHand.start.y) };
	float hourHandAngle = hourHandVec.dot(Vector2(0, 1)) / (hourHandVec.length() * Vector2(0, 1).length());
	hourHandAngle = acos(hourHandAngle);
	hourHandAngle = Util::Radian2Degree(hourHandAngle);
	if (hourHandVec.x < 0) {
		hourHandAngle = 180 + (180 - hourHandAngle);
	}

	int playerMoveAdd = 0;

	if (((hourHandAngle + range) > stickAngle) && ((hourHandAngle - range) < stickAngle)) {
		playerMoveAdd = 1;
	}

	if (hourHandAngle + range > 360.0f) {
		if ((hourHandAngle + range) - 360.0f > stickAngle) playerMoveAdd = 1;
	}

	if (hourHandAngle - range < 0) {
		if (360 - (hourHandAngle - range) < stickAngle) playerMoveAdd = 1;
	}

	hourHandAngle = fmodf(hourHandAngle + 180.0f, 360.0f);

	if (((hourHandAngle + range) > stickAngle) && ((hourHandAngle - range) < stickAngle)) {
		playerMoveAdd = -1;
	}

	if (hourHandAngle + range > 360.0f) {
		if ((hourHandAngle + range) - 360.0f > stickAngle) playerMoveAdd = -1;
	}

	if (hourHandAngle - range < 0) {
		if (360 - (hourHandAngle - range) < stickAngle) playerMoveAdd = -1;
	}

	//DrawFormatString(100, 100, 0xFFFFFF, "%f, %f", (float)pad->GetLeftStickX(), (float)pad->GetLeftStickY());
	//DrawFormatString(0, 100, 0xFFFFFF, "%f", stickAngle);
	//DrawFormatString(100, 120, 0xFFFFFF, "%f, %f", hourHand.end.x, hourHand.end.y);
	//DrawFormatString(0, 120, 0xFFFFFF, "%f", hourHandAngle);
	//DrawFormatString(0, 140, 0xFFFFFF, "%d", playerMoveAdd);

	//AD�L�[�ŒZ�j��ł̈ʒu��ύX
	playerPos += playerMoveAdd * playerSpd;
	
	// --�v���C���[���ړ��ł���̂𐧌�-- //
	playerPos = Clamp(playerPos, hourHand.length, 0.0f);

	//���@�ړ�
	if (input->IsPress(KEY_INPUT_A) || input->IsPress(KEY_INPUT_S) || input->IsPress(KEY_INPUT_W) || input->IsPress(KEY_INPUT_D)) {

	}

	//�Z�j��ł̎��@�̈ʒu���Q�Ƃ��Ď��@���W�v�Z
	//���@�͒Z�j��Ɉʒu����̂ŁA�p�x�͒Z�j�̂��̂��g��
	player.x = (playerPos * sinf(hourHand.radian / 180 * PI)) + clock.x;
	player.y = (playerPos * cosf(hourHand.radian / 180 * PI)) + clock.y;


	//�A���[�L�[�Ŏ��@���x�ύX
	playerSpd += ((input->IsPress(KEY_INPUT_E) - input->IsPress(KEY_INPUT_Q)) * 0.2f);
	if (input->IsPress(KEY_INPUT_R)) playerSpd = 2.0f;

	if (pad->GetButtonTrigger(PAD_INPUT_5)) {
		SetState(State::reverse);
	}

	if (state == State::normal) {
		color = 0xffffff;
	}
	else if (state == State::reverse) {
		color = 0xff00ff;
	}

#pragma endregion
}

// --�`�揈��-- //
void Player::Draw() {
	DrawCircle(player, color, true);
}