#include "GameScene.h"
#include "SceneManager.h"
using namespace Util;

void DrawCircle(Circle c, int color, bool fillFlag);

void DrawLine(Line l, int thickness = 1);

// --�C���X�^���X��NULL����-- //
GameScene* GameScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
GameScene* GameScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new GameScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�R���X�g���N�^-- //
GameScene::GameScene() : clock{ 640, 480, 416 }, player{ 0, 0, 16 }, playerSpd(2.0f),
longHand{ {640, 480}, {640, 0}, clock.radius, 180, 0xFF0000},
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 180, 0xFF }
{
	// --���̓N���X�C���X�^���X�擾-- //
	input = Input::GetInstance();
}

// --�f�X�g���N�^-- //
GameScene::~GameScene() {

}

// --����������-- //
void GameScene::Initialize() {

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
	hourHand.radian -= 2.0f;
	//-360�x��������0�ɖ߂�
	hourHand.radian = fmodf(hourHand.radian, 360.0f);
	//�j�̊p�x�ŏI�_���W���v�Z
	hourHand.end.x = (hourHand.length * sinf(hourHand.radian / 180 * PI)) + clock.x;
	hourHand.end.y = (hourHand.length * cosf(hourHand.radian / 180 * PI)) + clock.y;


#pragma endregion

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
void GameScene::Draw() {
	DrawCircle(player, 0xffffff, true);
	DrawCircle(clock, 0xffffff, false);
	DrawLine(longHand, 4);
	DrawLine(hourHand);
	DrawFormatString(0, 0, 0x00ffff, "playerSpeed:%f", playerSpd);
	DrawFormatString(0, 20, 0x00ffff, "R�L�[:���x���Z�b�g");
	DrawFormatString(0, 40, longHand.color, "longHand(���j)�̏�� x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 60, hourHand.color, "hourHand(�Z�j)�̏�� x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
}

void DrawCircle(Circle c, int color, bool fillFlag)
{

	DrawCircle(c.x, c.y, c.radius, color, fillFlag);
}

void DrawLine(Line l, int thickness)
{
	DrawLine(l.start.x, l.start.y, l.end.x, l.end.y, l.color, thickness);
}
