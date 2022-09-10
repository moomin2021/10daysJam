#pragma once
#include"Util.h"
#include"Camera.h"

enum class ParticleState {
	Normal,
	Endress
};

class Particle {

private: //�����o�ϐ�
	Circle obj;

	float radian;
	float Spd;
	ParticleState state;
	bool isAcive = false;
	int color;

	Vector2 parent;	//�������Ɏg���e���W

public:	//�����o�֐�
	
	//�X�V
	void Update();

	//�`��
	void Draw(Camera camera_,int color_ = Util::Random(0, 0xffffff));

	//������
	void Initialize(bool stateReset = false);

	//�e���W�̃Z�b�^�[
	void SetParent(Vector2 pos);

	void SetState(ParticleState state_);

	bool GetActive()const { return isAcive; }

	void SetSpeed(float s);

	void SetColor(int color_);

	int GetColor()const { return color; }

	ParticleState GetState()const { return state; }

};