#include "DxLib.h"
#include"Input.h"
#include"Vector2.h"
#include"JoyPadInput.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2A_14_�^����_�t�~��: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 960;

struct  Circle
{
	float x;
	float y;
	float radius;
};

void DrawCircle(Circle c, int color, bool fillFlag);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	int iguigu;
	int iguiug8;
	int fumiya;
	int moomin;
	int test01;
	int test072;
	int gitTest;

	int superrrrrrrrrrrrrrrr;

	Circle clock{
		WIN_WIDTH / 2,
		WIN_HEIGHT / 2,
		WIN_HEIGHT / 2
	};

	Circle player{
		0,
		0,
		16
	};

	float playerSpd = 2.0f;

	//�C���v�b�g�n�N���X�錾
	Input key{};



	// �Q�[�����[�v
	while (true) {

		//�L�[�{�[�h�X�V
		key.KeyUpdate();


		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//---------  �X�V����  -----------------------//

		//���@�ړ�
		if (key.IsPress(KEY_INPUT_A) || key.IsPress(KEY_INPUT_S) || key.IsPress(KEY_INPUT_W) || key.IsPress(KEY_INPUT_D)) {
		
			player.x += ((key.IsPress(KEY_INPUT_D) - key.IsPress(KEY_INPUT_A)) * playerSpd);
			player.y += ((key.IsPress(KEY_INPUT_S) - key.IsPress(KEY_INPUT_W)) * playerSpd);
		}

		//�A���[�L�[�Ŏ��@���x�ύX
		playerSpd += ( (key.IsPress(KEY_INPUT_E) - key.IsPress(KEY_INPUT_Q)) * 0.2f);

		//---------  �`�揈��  -----------------------//

		DrawCircle(player, 0xffffff, true);
		DrawCircle(clock, 0xffffff, false);
		DrawFormatString(0, 0, 0x00ffff, "playerSpeed:%f", playerSpd);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

void DrawCircle(Circle c, int color, bool fillFlag)
{
	
	DrawCircle(c.x, c.y, c.radius, color, fillFlag);
}
