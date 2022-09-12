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

	Vector2 parent ={0,0};	//�������Ɏg���e���W

	

public:	//�����o�֐�
	
	//�X�V
	void Update();

	//�`��
	void Draw(Camera camera_,int color_,int graph_);

	//������
	void Initialize(bool stateReset = false);

	//�e���W�̃Z�b�^�[
	void SetParent(Vector2 pos);

	void SetState(ParticleState state_);

	bool GetActive()const { return isAcive; }

	void SetSpeed(float s);

	void SetColor(int color_);
	void SetRadian(int radian_);

	int GetColor()const { return color; }

	ParticleState GetState()const { return state; }

};