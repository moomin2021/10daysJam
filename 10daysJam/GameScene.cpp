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

// --�R���X�g���N�^-- //
GameScene::GameScene() : clock{ 640, 480, 416 },
longHand{ {640, 480}, {640, 0}, clock.radius, 180, 0xFF0000},
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 180, 0xFF }
{
	// --���̓N���X�C���X�^���X�擾-- //
	input = Input::GetInstance();

	// --�v���C���[�N���X�C���X�^���X�擾-- //
	player = Player::GetInstance();
}

// --�f�X�g���N�^-- //
GameScene::~GameScene() {
	delete player;
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

	// --�v���C���[�N���X�X�V����-- //
	player->Update(hourHand, clock);
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
}