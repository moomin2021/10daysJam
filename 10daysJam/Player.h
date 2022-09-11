#pragma once
#include "Input.h"
#include "JoyPadInput.h"
#include "Util.h"
#include"Camera.h"

class Player {
	// --�R���g���[���[���[�h�̗񋓌^-- //
	enum ControlMode {
		MODE1,
		MODE2,
		MODE3
	};

	/// --�����o�ϐ�-- ///
private:
	// --�C���X�^���X-- //
	static Player* myInstance;

#pragma region �N���X�̐錾
	// --���̓N���X-- //
	Input* input;

	// --�R���g���[���[�N���X-- //
	JoyPadInput* pad;
#pragma endregion

#pragma region �v���C���[�֌W�ϐ��̐錾
public:
	// --�v���C���[-- //
	Circle player;

private:
	// --���S����̃v���C���[�̋���-- //
	float playerLength;

	// --�v���C���[�̑��x-- //
	float playerSpeed;

	// --�v���C���[�̉摜�n���h��-- //
	int playerGraph[2];
#pragma endregion

	// --�Z�j�̊p�x-- //
	float hourHandAngle;

#pragma region ���̑��ϐ��錾
	// --�X�e�B�b�N�͈̔�-- //
	float stickRange;

	// --�⏕��-- //
	Circle auxiliaryCircle;

	// --�F-- //
	int color = 0xffffff;

	// --���샂�[�h-- //
	int controlMode;
#pragma endregion

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Player* GetInstance();

	// --�C���X�^���X���-- //
	void Relese();

	// --�f�X�g���N�^-- //
	~Player();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update(Line hourHand, Circle clock, float radius);

	// --�`�揈��-- //
	void Draw(Camera camera_ ,int bright);

	/// <summary>
	/// �v���C���[�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	Circle GetPlayer()const { return player; }

private:
	// --�R���X�g���N�^-- //
	Player();

	/// --�����o�֐�END-- ///
};