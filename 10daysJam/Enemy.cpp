#include "Enemy.h"
#include"DxLib.h"
using namespace Util;

// --�R���X�g���N�^-- //

Enemy::Enemy() {
	
}

Enemy::Enemy(Vector2 pos, float radius) : obj{ pos, radius } {

}

// --�f�X�g���N�^-- //
Enemy::~Enemy() {

}

// --����������-- //
void Enemy::Initialize() {
	
	//�X�|�[���G�t�F�N�g�̃p�[�e�B�N����
	int particleNum = Random(28, 36);
	//�X�|�[���G�t�F�N�g���o��
	SpawnEffect(particleNum);
	spawnAddRadius = 8.0f;
	obj.radius += spawnAddRadius;
}

// --�X�V����-- //
void Enemy::Update(Line hourLine_) {

	//�X�|�[���G�t�F�N�g�̍X�V
	for (int i = spawnEffect.size()-1; i >=0 ; i--) {
	//	spawnEffect[i].SetSpeed(0.5f);
		spawnEffect[i].Update();
		//if(spawnEffect[i].GetActive())DrawFormatString(0 + 40 * i, 440, 0xffffff, "active");
		//�X�|�[���G�t�F�N�g�̊����t���O�������Ă��Ȃ���Ώ���
		if (!spawnEffect[i].GetActive()) {
			spawnEffect.erase(spawnEffect.begin() + i);
		}
	}

	if (obj.radius > 8.0f) {
		obj.radius -= (spawnAddRadius / 5);
	}

	switch (state)
	{
	case State::Normal:
		UpdateNormal();
		break;
	case State::Reverse:
		UpdateReverse(hourLine_);
		break;
	case State::Stop:
		break;
	case State::Item :
		//�F�����F�ɕύX
		color = 0xffff00;
		break;
	case State::Enemy:
		//�F��ԂɕύX
		color = 0xff0000;
		break;
	case State::Death:
		UpdateDeath(hourLine_.start,hourLine_.length);
	default:
		break;
	}

}

void Enemy::UpdateNormal()
{
}

void Enemy::UpdateReverse(Line hourLine_)
{
	//�Z�j�ɍ��W��Ǐ]������
	//�Z�j�̎n�_�Ǝ����W���璷�����擾
	Vector2 lenVec = hourLine_.start - obj.pos;
	float rad = hourLine_.radian - 90;

	float len = lenVec.length();
	//�����ƒZ�j�̊p�x���玩���W���Čv�Z���đ��
	obj.pos.x = (len * cosf((rad) / 180 * PI)) + (obj.radius * cosf((rad-90) / 180 * PI))+ hourLine_.start.x;
	obj.pos.y = (len * sinf((rad) / 180 * PI)) + (obj.radius * sinf((rad-90) / 180 * PI))+ hourLine_.start.y;

	//�F�𖾂�߂̃I�����W��
	color = 0xff7c17;
}

void Enemy::UpdateDeath(Vector2 afterPos, float randParam) {
	//�n�܂�Ȃ�
	bezire.divisionNum = 32;
	if (effectTime == 0) {
		//�x�W�G�Ȑ��̍��W������
		//float len = obj.radius;
		for (int i = 0; i < 4; i++) {
			Vector2 pos;
			int rad = Random(0.0f, 360.0f);
			if (i == 0) {
				pos = obj.pos;
			}
			else if (i == 3) {
				pos = afterPos;
			}
			else {
				Vector2 a = obj.pos - afterPos;
				pos.x = Random(-randParam, randParam)+ afterPos.x;
				pos.y = Random(-randParam, randParam)+ afterPos.y;
			}
			bezire.SetControllPoint(pos, i);
		}
		
		//�x�W�G�Ȑ��̍X�V
		bezire.Update();
	}



	if (effectTime < bezire.divisionNum) {
		obj.pos = bezire.pos[effectTime];
		effectTime++;
	}
	else if (effectTime >= bezire.divisionNum) {
		state = State::Delete;
	}

	//���a�����������ĐF�𐅐F��
	obj.radius = 6.0f;
	color = 0x45efff;

}


void Enemy::OnCollison()
{
	//�X�e�[�g�𔽓]��
	state = State::Reverse;
		//color = 0x7fff7f;
}

// --�`�揈��-- //
void Enemy::Draw(Camera camera_) {

	//�X�|�[���G�t�F�N�g�`��
	//SetDrawBlendMode(DX_BLENDMODE_ADD, 256);
	for (int i = 0; i < spawnEffect.size(); i++) {

		spawnEffect[i].Draw(camera_,spawnEffect[i].GetColor());
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);

	Circle pos ={
		obj.pos + camera_.GetPos(),
		obj.radius
	};
	DrawCircle(pos, color, true);

	
}

void Enemy::SetState(State state_)
{
	state = state_;

}

void Enemy::SpawnEffect(int effectNum_)
{
	//�����̐������p�[�e�B�N����z��Ɋi�[
	for (int i = 0; i < effectNum_; i++) {
		Particle newParticle;
		newParticle.SetParent(obj.pos);
		Color c;
		int color;
		c.red = Random(128, 200);
		c.green = Random(128, 200);
		c.blue = Random(224, 255);
		color = c.red * pow(16, 4) + c.green * pow(16, 2) + c.blue;
		newParticle.SetColor(color);
		newParticle.Initialize(true);
		spawnEffect.push_back(newParticle);
	}

}

void Enemy::SetObj(Circle obj_)
{
	obj = obj_;
}

void Enemy::StateChange()
{
	isChange = true;
}


//void Enemy::AllEnemyDeath()
//{
//	enemys.clear();
//}
