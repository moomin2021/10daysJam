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
public:
	// --�v���C���[-- //
	Circle player;

private:
	// --�C���X�^���X-- //
	static Player* myInstance;

	/// --�N���X�錾-- ///
#pragma region
	// --���̓N���X-- //
	Input* input;

	// --�R���g���[���[�N���X-- //
	JoyPadInput* pad;
#pragma endregion

	/// --�v���C���[�֌W�ϐ��̐錾-- ///
#pragma region

	// --���S����̃v���C���[�̋���-- //
	float playerLength;

	// --�v���C���[�̑��x-- //
	float playerSpeed;

	// --�X�e�B�b�N�͈̔�-- //
	float stickRange;

	// --�⏕��-- //
	Circle auxiliaryCircle;

	//�F
	int color = 0xffffff;

	// --���샂�[�h-- //
	int controlMode;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Player* GetInstance();

	// --�f�X�g���N�^-- //
	~Player();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update(Line hourHand, Circle clock, float radius);

	// --�`�揈��-- //
	void Draw(Camera camera_);

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