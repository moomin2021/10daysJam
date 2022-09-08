#include "GameScene.h"
#include "SceneManager.h"
#include "Score.h"
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
	vecAtoB.x = cB.pos.x - cA.pos.x;
	vecAtoB.y = cB.pos.y - cA.pos.y;
	radius = cA.radius + cB.radius;

	if (vecAtoB.length() <= radius) {
		flag = true;
	}
	else {
		flag = false;
	}

	return flag;
}

bool GameScene::CollisionCtoL(Circle c, Line l, float lineSpd)
{
	//�K�v�ϐ��錾
	Vector2 vecLine, vecCircle, vecCircle2, vecN, vecNtoC;
	float len;
	float rad = l.radian - 90;

	for (int i = 0; i < (int)lineSpd; i++) {
		//���̏I�_���W��ύX

		l.end.x = (l.length * cosf((rad) / 180 * PI)) + l.start.x;
		l.end.y = (l.length * sinf((rad) / 180 * PI)) + l.start.y;

		vecLine = l.end - l.start;
		vecLine = vecLine.normalize();
		vecCircle = c.pos - l.start;
		vecCircle2 = c.pos - l.end;
		len = vecLine.dot(vecCircle);
		vecN = vecLine * len;
		vecNtoC = vecCircle - vecN;

		if (vecNtoC.length() < c.radius) {
			if (vecLine.dot(vecCircle) * vecLine.dot(vecCircle2) <= 0.0f) {
				return true;
			}
			else if (vecCircle.length() < c.radius || vecCircle2.length() < c.radius) {

				return true;
			}
		}
		else rad--;
	}
	return false;
}

// --�R���X�g���N�^-- //
GameScene::GameScene() : clock{ {640, 480}, 416 },
longHand{ {640, 480}, {640, 0}, clock.radius, 0, 0xFF0000 },
hourHand{ {640, 480}, {640, 32}, clock.radius - 32, 0, 0xFF }, levelCircle{ {640, 480}, 8 },
longHandSpeed(0.5f)
{
	// --���̓N���X�C���X�^���X�擾-- //
	input = Input::GetInstance();

	// --�v���C���[�N���X�C���X�^���X�擾-- //
	player = Player::GetInstance();

	// --�R���g���[���[�N���X�C���X�^���X�擾-- //
	pad = JoyPadInput::GetInstance();
}

// --�f�X�g���N�^-- //
GameScene::~GameScene() {
	delete player;
}

// --����������-- //
void GameScene::Initialize() {
	delayMax = 20; 
	spawnInterval = 20;
	spawnDelay = delayMax;
	spawnTimer = spawnInterval;
	level = 1;
	point = 0;
	hourHandSpeed = 1.0f;
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
		hourHand.radian += hourHandSpeed;

		//�C�ӂ̃L�[�ŒZ�j�𓮂���(�f�o�b�O�p)
		//hourHand.radian += ((pad->GetButton(PAD_INPUT_1)) - (pad->GetButton(PAD_INPUT_2))) * 2.0f;
	}//�X�e�[�g�����]���Ă���Ȃ�Z�j���t��������
	else if (hourHand.state == State::Reverse) {
		hourHand.radian -= reverseSpd;
		//�Z�j�����j�ɒǂ������璷�j�̃X�e�[�g���u���]�v��
		if (hourHand.radian < longHand.radian + reverseSpd && hourHand.radian > longHand.radian - reverseSpd) {
			longHand.state = State::Reverse;
			//�Z�j�̃X�e�[�g���Ƃ߂�
			hourHand.state = State::Stop;
		}
	}

	//�X�e�[�g���ʏ�Ȃ璷�j�͎�����]
	if (longHand.state == State::Normal) {
		longHand.radian += longHandSpeed;
	}//�X�e�[�g���u���]�v�Ȃ�t��
	else if (longHand.state == State::Reverse) {
		//���x�͒Z�j�Ɠ���
		longHand.radian -= reverseSpd;

		//���j�̊p�x��0�ɂȂ����璷�j�ƒZ�j�̃X�e�[�g��߂��A�p�x��������
		if (longHand.radian < reverseSpd) {
			longHand.state = State::Normal;
			hourHand.state = State::Normal;
			longHand.radian = 0;
			//	hourHand.radian = 0;
			enemys.clear();
			LevelReset();
			// --�X�R�A���Z-- //
			Score::AddScore(1000);

			//�V�F�C�N
			camera.SetShakeCount(10);

			//�G�̃X�|�[���^�C�}�[�����Z�b�g
			spawnDelay = delayMax;
			spawnTimer = spawnInterval;
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
	float radH = hourHand.radian - 90;

	//�j�̊p�x�ŏI�_���W���v�Z
	longHand.end.x = (longHand.length * cosf(radL / 180 * PI)) + clock.pos.x;
	longHand.end.y = (longHand.length * sinf(radL / 180 * PI)) + clock.pos.y;
	//�j�̊p�x�ŏI�_���W���v�Z
	hourHand.end.x = (hourHand.length * cosf(radH / 180 * PI)) + clock.pos.x;
	hourHand.end.y = (hourHand.length * sinf(radH / 180 * PI)) + clock.pos.y;


#pragma endregion

	// --�v���C���[�N���X�X�V����-- //
	player->Update(hourHand, clock, levelCircle.radius);

	// --�G�l�~�[�̃X�|�[������-- //
	//�Z�j���ʏ��ԂȂ�s��
	if (hourHand.state == State::Normal) {
		EnemySpawn();
	}


	// --�G�l�~�[�N���X�X�V����-- //
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Update(hourHand);

		//�Z�j�����]���[�h�Ȃ画����Ƃ�
		if (hourHand.state == State::Reverse) {
			//�Z�j�ƓG�̓����蔻��
			if (CollisionCtoL(enemys[i].GetCircle(), hourHand, reverseSpd)) {
				enemys[i].OnCollison();
			}
		}
	}

	//�J�����X�V
	//�X�y�[�X�L�[�ŃV�F�C�N
	if (input->IsTrigger(KEY_INPUT_SPACE)) {
		camera.SetShakeCount(5);
	}

	camera.CameraShake();
	
	// --�v���C���[�ƃG�l�~�[�̓����蔻��-- //
	PlayerAndEnemyCol();

	// --���x���̍X�V����-- //
	LevelUpdate();

	// --�f�o�b�N�p����-- //
	levelCircle.radius += input->IsPress(KEY_INPUT_A) - input->IsPress(KEY_INPUT_D);
	levelCircle.radius = Clamp(levelCircle.radius, 300.0f, 8.0f);
	hourHandSpeed += (input->IsTrigger(KEY_INPUT_Z) - input->IsTrigger(KEY_INPUT_C)) * 0.1f;
	longHandSpeed += (input->IsTrigger(KEY_INPUT_I) - input->IsTrigger(KEY_INPUT_P)) * 0.1f;
}

// --�`�揈��-- //
void GameScene::Draw() {
	// --�v���C���[�̕`�揈��-- //
	player->Draw(camera);

	// --�G�l�~�[�̕`�揈��-- //
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].Draw(camera);
	}
	
	//�`��p���W�錾
	Circle posC;
	Line posL;
	posC = { clock.pos + camera.GetPos(),clock.radius };
	DrawCircle(posC, 0xffffff, false);
	posL.start = {longHand.start + camera.GetPos()};
	posL.end = {longHand.end + camera.GetPos()};
	posL.color = longHand.color;
	DrawLine(posL, 4);
	posL.start = { hourHand.start + camera.GetPos() };
	posL.end = { hourHand.end + camera.GetPos() };
	posL.color = hourHand.color;
	DrawLine(posL);
	posC = { levelCircle.pos + camera.GetPos() };
	DrawCircle(posC, 0xFFFFFF, false);

	//�ڈ�p�O���̐j
	posL.start = { clock.pos + camera.GetPos() };
	posL.end = { clock.pos.x + camera.GetPos().x,clock.pos.y - clock.radius + 16 + camera.GetPos().y };
	posL.color = 0x60ffbf;
	DrawLine(posL, 6);

	// --�f�o�b�N�p����-- //
	DrawFormatString(0, 80, 0xFFFFFF, "AD�L�[:���x���T�[�N���̔��a�ύX");
	DrawFormatString(0, 100, 0xFFFFFF, "���x���T�[�N���̔��a:%f", levelCircle.radius);
	DrawFormatString(0, 120, 0xFFFFFF, "ZC�L�[:�Z�j�̑��x�ύX");
	DrawFormatString(0, 140, 0xFFFFFF, "�Z�j�̑��x:%f", hourHandSpeed);
	DrawFormatString(0, 160, longHand.color, "longHand(���j)�̏�� x:%f,y:%f,radian:%f", longHand.end.x, longHand.end.y, longHand.radian);
	DrawFormatString(0, 180, hourHand.color, "hourHand(�Z�j)�̏�� x:%f,y:%f,radian:%f", hourHand.end.x, hourHand.end.y, hourHand.radian);
	DrawFormatString(0, 280, 0xFFFFFF, "IP�L�[�Œ��j�̑��x��ύX");
	DrawFormatString(0, 300, 0xFFFFFF, "���j�̑��x:%f", longHandSpeed);
	DrawFormatString(0,320, 0xFFFFFF, "�J�����V�F�C�N:�X�y�[�X�L�[(�U���ʂ̒����͖�����)");
	DrawFormatString(0,340, 0xFFFFFF, "�G�l�~�[�̃X�|�[���܂ł̎c�莞��:%d",spawnTimer);
	DrawFormatString(0,360, 0xFFFFFF, "�G�l�~�[�̃X�|�[���x������:%d",spawnDelay);
}

// --�G�̃X�|�[������-- //
void GameScene::EnemySpawn() {
	//�X�|�[���^�C�}�[�����炷
	if (spawnTimer > 0) {
		spawnTimer--;
		//�^�C�}�[��0�ɂȂ�����X�|�[���ʒu�����߂�
	}
	else if (spawnTimer == 0) {


		//�X�|�[���^�C�}�[��0�ɂȂ����u�Ԃ݈̂ʒu�����߂�(�Z�j�̈ʒu���Q�Ƃ��邽��
		if (spawnDelay == delayMax) {
			enemyLength = Random(levelCircle.radius, hourHand.length);
			float rad = hourHand.radian - 90;
			enemyPos.x = (enemyLength * cosf(rad / 180 * PI)) + clock.pos.x;
			enemyPos.y = (enemyLength * sinf(rad / 180 * PI)) + clock.pos.y;
			//�f�B���C�^�C�}�[�����炷
			spawnDelay--;
		}//�f�B���C�^�C�}�[��0�o�Ȃ��Ȃ�
		else if (spawnDelay > 0) {
			//�f�B���C�^�C�}�[�����炷
			spawnDelay--;
		}//�f�B���C�^�C�}�[��0�ɂȂ�������W���m��
		else if (spawnDelay == 0) {
			for (int i = 0; i < 10; i++) {
				enemys.push_back({ enemyPos, 8.0f });
				//�^�C�}�[�����Z�b�g
				spawnTimer = spawnInterval;
				spawnDelay = delayMax;
				break;
			}
		}
	}
}

// --���@�ƓG�̓����蔻�菈��-- //
void GameScene::PlayerAndEnemyCol() {
	// --���@�ƓG�̓����蔻����s��-- //
	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionCtoC(player->player, enemys[i].enemy)) {
			enemys.erase(enemys.begin() + i);
			point++;
			Score::AddScore(100);
		}
	}

	// --���x���T�[�N���ƃG�l�~�[�̓����蔻��-- //
	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionCtoC(levelCircle, enemys[i].enemy)) {
			enemys.erase(enemys.begin() + i);
		}
	}
}

// --���x��-- //
void GameScene::LevelUpdate() {
	level = (point / 5) + 1;

	//hourHandSpeed = (0.5f * level) + 1.0f;

	//newCircleRadius = level * 8;

	//if (newCircleRadius > levelCircle.radius) levelCircle.radius++;
	//if (newCircleRadius < levelCircle.radius) levelCircle.radius--;
}

// --���x�����Z�b�g-- //
void GameScene::LevelReset() {
	level = 1;
	point = 0;
}
