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
longHand{ {640, 480}, {640, 0}, clock.radius, 0, 0xFF0000},
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 0, 0xFF }
{
	// --���̓N���X�C���X�^���X�擾-- //
	input = Input::GetInstance();

	// --�v���C���[�N���X�C���X�^���X�擾-- //
	player = Player::GetInstance();

	// --�G�l�~�[�N���X�C���X�^���X�擾-- //
	enemy = Enemy::GetInstance();

	pad = JoyPadInput::GetInstance();
}

// --�f�X�g���N�^-- //
GameScene::~GameScene() {
	delete player;
	delete enemy;
}

// --����������-- //
void GameScene::Initialize() {
	// --�G�l�~�[������-- //
	enemy->Initialize();
}

// --�X�V����-- //
void GameScene::Update() {



#pragma region �j�̍��W�v�Z

	//L�{�^���ŒZ�j�̃X�e�[�g���u���]�v��
	if (pad->GetButton(PAD_INPUT_5) && hourHand.state == State::Normal) {
		hourHand.state = State::Reverse;
	}

	//�X�e�[�g���ʏ�Ȃ�Z�j�͎�����]
	if (hourHand.state == State::Normal) {
		hourHand.radian += 2.0f;

		hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
	}//�X�e�[�g�����]���Ă���Ȃ�Z�j���t��������
	else if (hourHand.state == State::Reverse) {
		hourHand.radian -= reverseSpd;
		//�Z�j�����j�ɒǂ������璷�j�̃X�e�[�g���u���]�v�ɁA�Z�j�͎~�܂�
		if (hourHand.radian < longHand.radian + reverseSpd && hourHand.radian > longHand.radian - reverseSpd){
			longHand.state = State::Reverse;
			hourHand.state = State::Stop;
		}
	}

	//�X�e�[�g���ʏ�Ȃ璷�j�͎�����]
	if (longHand.state == State::Normal) {
		longHand.radian += 0.5f;
	}//�X�e�[�g���u���]�v�Ȃ�t��
	else if (longHand.state == State::Reverse) {
		//���x�͒Z�j�Ɠ���
		longHand.radian -= reverseSpd * 2;
		
		//���j�̊p�x��0�ɂȂ����璷�j�ƒZ�j�̃X�e�[�g��߂��A�p�x��������
		if (longHand.radian < reverseSpd) {
			longHand.state = State::Normal;
			hourHand.state = State::Normal;
			longHand.radian = 0;
			//hourHand.radian = 0;
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
	longHand.end.x = (longHand.length * cosf(radL / 180 * PI)) + clock.x;
	longHand.end.y = (longHand.length * sinf(radL / 180 * PI)) + clock.y;
	//�j�̊p�x�ŏI�_���W���v�Z
	hourHand.end.x = (hourHand.length * cosf(radH  / 180 * PI)) + clock.x;
	hourHand.end.y = (hourHand.length * sinf(radH  / 180 * PI)) + clock.y;


#pragma endregion

	// --�v���C���[�N���X�X�V����-- //
	player->Update(hourHand, clock);

	// --�G�l�~�[�N���X�X�V����-- //
	enemy->Update(hourHand, clock);
}

// --�`�揈��-- //
void GameScene::Draw() {
	// --�v���C���[�̕`�揈��-- //
	player->Draw();
	enemy->Draw();
	DrawCircle(clock, 0xffffff, false);
	DrawLine(longHand, 4);
	DrawLine(hourHand);
	DrawFormatString(0, 20, 0x00ffff, "R�L�[:���x���Z�b�g");
	DrawFormatString(0, 40, longHand.color, "longHand(���j)�̏�� x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 60, hourHand.color, "hourHand(�Z�j)�̏�� x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);

	//�ڈ�p�O���̐j
	DrawLine(clock.x, clock.y, clock.x, clock.y - clock.radius + 16, 0x60ffbf, 6);
}