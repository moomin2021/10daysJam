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

	Vector2 parent;	//�������Ɏg���e���W

public:	//�����o�֐�
	
	//�X�V
	void Update();

	//�`��
	void Draw(Camera camera_);

	//������
	void Initialize(bool stateReset = false);

	//�e���W�̃Z�b�^�[
	void SetParent(Vector2 pos);

	void SetState(ParticleState state_);

	ParticleState GetState()const { return state; }

};