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

// --�C���X�^���X���-- //
void Player::Relese() {
	// --�C���X�^���X�����������牽�������ɏI������-- //
	if (myInstance == nullptr) return;

	// --�C���X�^���X���-- //
	delete myInstance;
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
Player::Player()
{
#pragma region �C���X�^���X�ǂݍ���
	// --�L�[�{�[�h�N���X-- //
	input = Input::GetInstance();

	// --�R���g���[���[�N���X-- //
	pad = JoyPadInput::GetInstance();
#pragma endregion

#pragma region �v���C���[�֌W�ϐ��̏�����
	// --�v���C���[-- //
	player = { {0, 0}, 16 };

	// --�v���C���[�̑��x-- //
	playerSpeed = 5.7f;

	// --���S����̃v���C���[�̋���-- //
	playerLength = player.radius;

	// --�v���C���[�̉摜�ǂݍ���-- //
	LoadDivGraph("Resources/Player.png", 2, 2, 1, 48, 48, playerGraph);
#pragma endregion

#pragma region ���̑��̏�����
	// --�X�e�B�b�N�͈̔�-- //
	stickRange = 90.0f;

	// --���샂�[�h-- //
	controlMode = MODE2;

	// --�⏕��-- //
	auxiliaryCircle = { {640, 480}, 8 };
#pragma endregion
}

// --�f�X�g���N�^-- //
Player::~Player() {

}

// --����������-- //
void Player::Initialize() {
	
}

// --�X�V����-- //
void Player::Update(Line hourHand, Circle clock, float radius) {
#pragma region ���@�ړ��֌W

	// --�v���C���[���O�������ǂ���ɐi�ނ��i1 = �O��, -1 = �����j-- //
	int playerMoveAdd = 0;

#pragma region ���샂�[�h1�̏���
	if (controlMode == MODE1) {
		// --���X�e�B�b�N���|��Ă���p�x�����߂�-- //
		float stickAngle;
		{
			// --�X�e�B�b�N�̃x�N�g��-- //
			Vector2 lStickVec = { (float)pad->GetLeftStickX(), (float)pad->GetLeftStickY() };

			// --2�̃x�N�g���̂Ȃ��p�����߂�-- //
			stickAngle = lStickVec.dot(Vector2(0, -1)) / (lStickVec.length() * Vector2(0, -1).length());
			stickAngle = acos(stickAngle);
			stickAngle = Util::Radian2Degree(stickAngle);

			if (pad->GetLeftStickX() < 0) stickAngle = 180 + (180 - stickAngle);
		}

		// --�Z�j�̊p�x�����߂�-- //
		float hourHandAngle;
		{
			// --�Z�j�̃x�N�g��-- //
			Vector2 hourHandVec = { hourHand.end.x - hourHand.start.x, hourHand.end.y - hourHand.start.y };

			// --2�̃x�N�g���̂Ȃ��p�����߂�-- //
			hourHandAngle = hourHandVec.dot(Vector2(0, -1)) / (hourHandVec.length() * Vector2(0, -1).length());
			hourHandAngle = acos(hourHandAngle);
			hourHandAngle = Util::Radian2Degree(hourHandAngle);

			if (hourHandVec.x < 0) hourHandAngle = 180 + (180 - hourHandAngle);
		}

		// --����-- //
		{
			if (((hourHandAngle + stickRange) > stickAngle) && ((hourHandAngle - stickRange) < stickAngle)) {
				playerMoveAdd = 1;
			}

			if (hourHandAngle + stickRange > 360.0f) {
				if ((hourHandAngle + stickRange) - 360.0f > stickAngle) playerMoveAdd = 1;
			}

			if (hourHandAngle - stickRange < 0) {
				if (360 - (hourHandAngle - stickRange) < stickAngle) playerMoveAdd = 1;
			}

			hourHandAngle = fmodf(hourHandAngle + 180.0f, 360.0f);

			if (((hourHandAngle + stickRange) > stickAngle) && ((hourHandAngle - stickRange) < stickAngle)) {
				playerMoveAdd = -1;
			}

			if (hourHandAngle + stickRange > 360.0f) {
				if ((hourHandAngle + stickRange) - 360.0f > stickAngle) playerMoveAdd = -1;
			}

			if (hourHandAngle - stickRange < 0) {
				if (360 - (hourHandAngle - stickRange) < stickAngle) playerMoveAdd = -1;
			}
		}
	}
#pragma endregion

#pragma region ���샂�[�h2�̏���
	else if (controlMode == MODE2) {
		playerMoveAdd += pad->GetButton(PAD_INPUT_1) - pad->GetButton(PAD_INPUT_2);
	}
#pragma endregion

#pragma region ���샂�[�h3�̏���
	else if (controlMode == MODE3) {
		if (pad->GetLeftStickHorizontal() == 1 && pad->GetRightStickHorizontal() == -1) playerMoveAdd = -1;
		else if (pad->GetLeftStickHorizontal() == -1 && pad->GetRightStickHorizontal() == 1) playerMoveAdd = 1;
	}
#pragma endregion

#pragma region �v���C���[���W�̍Čv�Z
	// --���S����̃v���C���[�̋���-- //
	playerLength += playerMoveAdd * playerSpeed;
	
	// --�v���C���[���ړ��ł���̂𐧌�-- //
	playerLength = Clamp(playerLength, hourHand.length, radius + player.radius);

	//�Z�j��ł̎��@�̈ʒu���Q�Ƃ��Ď��@���W�v�Z
	//���@�͒Z�j��Ɉʒu����̂ŁA�p�x�͒Z�j�̂��̂��g��
	float rad = hourHand.radian- 90;

	player.pos.x = (playerLength * cosf((rad) / 180 * PI)) +(player.radius * cosf((rad + 90)/180*PI)) + clock.pos.x;
	player.pos.y = (playerLength * sinf((rad) / 180 * PI)) + (player.radius * sinf((rad + 90) / 180 * PI)) + clock.pos.y;
#pragma endregion

	// --�⏕���Čv�Z-- //
	auxiliaryCircle.radius = playerLength;
#pragma endregion

#pragma region �f�o�b�O�p����
	// --�v���C���[���x�̕ύX-- //
	playerSpeed += ((input->IsPress(KEY_INPUT_E) - input->IsPress(KEY_INPUT_Q)) * 0.2f);

	// --�v���C���[���x�̃��Z�b�g-- //
	if (input->IsPress(KEY_INPUT_R)) playerSpeed = 2.0f;

	// --�v���C���[���x����-- //
	playerSpeed = Clamp(playerSpeed, 100.0f, 0.1f);

	// --����̃��[�h�`�F���W-- //
	if (input->IsTrigger(KEY_INPUT_1)) controlMode = MODE1;
	if (input->IsTrigger(KEY_INPUT_2)) controlMode = MODE2;
	if (input->IsTrigger(KEY_INPUT_3)) controlMode = MODE3;
#pragma endregion
}

// --�`�揈��-- //
void Player::Draw(Camera camera_) {
#pragma region �v���C���[�`�揈��
	// --�J�����V�F�C�N�p�ɍ��W���Čv�Z-- //
	Circle pos = {
		player.pos + camera_.GetPos(),
		player.radius
	};

	// --�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	Color color = GetColor16("1a7971");
	SetDrawBright(color.red, color.green, color.blue);

	for (int i = 0; i < 5; i++) {
		DrawGraph(pos.pos.x - 24, pos.pos.y - 24, playerGraph[0], true);
	}

	//SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawGraph(pos.pos.x - 24, pos.pos.y - 24, playerGraph[1], true);
	//DrawCircle(pos, 0xffffff, true);

#pragma endregion

#pragma region �⏕���`�揈��
	// --�J�����V�F�C�N�p�ɍ��W���Čv�Z-- //
	Circle pos2 = {
		auxiliaryCircle.pos + camera_.GetPos(),
		auxiliaryCircle.radius
	};

	// --�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawCircle(pos2, 0xFFFFFF, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 125);
#pragma endregion

#pragma region �f�o�b�O�p����
	DrawFormatString(0, 20, 0xFFFFFF, "QE�L�[:�v���C���[�̑��x�ύX");
	DrawFormatString(0, 40, 0xffffff, "R�L�[:�v���C���[�̑��x���Z�b�g");
	DrawFormatString(0, 60, 0xffffff, "�v���C���[���x:%f", playerSpeed);
	DrawFormatString(0, 240, 0xFFFFFF, "123�L�[�ő���̃��[�h��ς���");
	DrawFormatString(0, 260, 0xFFFFFF, "���샂�[�h:���[�h%d", controlMode + 1);
#pragma endregion
}