#pragma once
#include "Vector2.h"
#include "Input.h"

struct  Circle
{
	float x;
	float y;
	float radius;
};

struct Line {
	Vector2 start;
	Vector2 end;
	float length;
	float radian;
	int color;
};

class GameScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static GameScene* myInstance;

	// --���̓N���X-- //
	Input* input;

	// --���v-- //
	Circle clock;

	// --�v���C���[-- //
	Circle player;

	// --���j-- //
	Line longHand;

	// --�Z�j-- //
	Line hourHand;

	// --�v���C���[�̑��x-- //
	float playerSpd = 2.0f;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static GameScene* GetInstance();

	// --�f�X�g���N�^-- //
	~GameScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	GameScene();

	/// --�����o�֐�END-- ///
};