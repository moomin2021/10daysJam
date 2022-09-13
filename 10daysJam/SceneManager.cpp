#include "SceneManager.h"

// --�֗��n�N���X-- //
#include "Util.h"

using namespace Util;

// --�C���X�^���X��NULL����-- //
SceneManager* SceneManager::myInstance = nullptr;

// --�ύX����V�[���̏�����-- //
int SceneManager::changeScene = 0;

// --�V�[���ύX�t���O�̏�����-- //
bool SceneManager::isChangeScene = false;

bool SceneManager::isDebugMode = false;

// --�C���X�^���X�ǂݍ���-- //
SceneManager* SceneManager::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new SceneManager();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�C���X�^���X���-- //
void SceneManager::Relese() {
	// --�C���X�^���X�����������牽�������ɏI������-- //
	if (myInstance == nullptr) return;

	// --�C���X�^���X���-- //
	delete myInstance;
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
SceneManager::SceneManager() {
	// --�C���X�^���X�ǂݍ���-- //
#pragma region �C���X�^���X�ǂݍ���
	// --�^�C�g���V�[��-- //
	titleScene = TitleScene::GetInstance();

	// --�Q�[���V�[��-- //
	gameScene = GameScene::GetInstance();

	// --���U���g�V�[��-- //
	resultScene = ResultScene::GetInstance();

	// --�X�R�A-- //
	score = Score::GetInstance();

	// --�T�E���h-- //
	sound = Sound::GetInstance();

	// --����-- //
	input = Input::GetInstance();
#pragma endregion

	// --�V�[��-- //
	scene = TITLESCENE;

	// --�V�[�����ړ�����ۂ̎���-- //
	sceneInterval = 100;

	// --�^�C�}�[-- //
	timer = 0;

	// --�~�̃T�C�Y-- //
	circleSize = 800;

	// --�~�̊g�k�̑��x-- //
	sizeChangeSpeed = 20;

	// --�X�N���[���n���h��-- //
	screenHandle = MakeScreen(1280, 960, true);

	// --�t�F�[�h�A�E�g���邩-- //
	isFadeOut = true;

	// --�t�F�[�h�C��
	isFadeIn = false;

	circleGraph = LoadGraph("Resources/SceneChangeCircle.png");
}

// --�f�X�g���N�^-- //
SceneManager::~SceneManager() {
	titleScene->Relese();
	gameScene->Relese();
	resultScene->Relese();
	score->Relese();
}

// --����������-- //
void SceneManager::Initialize() {
	// --�Q�[���V�[������������-- //
#pragma region �N���X������
	// --�^�C�g���V�[��-- //
	titleScene->Initialize();

	// --�Q�[���V�[��-- //
	gameScene->Initialize();

	// --���U���g�V�[��-- //
	resultScene->Initialize();
#pragma endregion

	// --�ŏ��Ƀ^�C�g���V�[����BGM���Đ�-- //
	sound->PlayBGM(TITLESCENEBGM);
}

// --�X�V����-- //
void SceneManager::Update() {
	// --�f�o�b�O���[�h�ؑւ�-- //
	if (input->IsTrigger(KEY_INPUT_F1)) {
		isDebugMode = !isDebugMode;
	}

	if (isChangeScene == false) {
		// --�^�C�g���V�[���X�V����-- //
		if (scene == TITLESCENE) {
			titleScene->Update();
		}

		// --�Q�[���V�[���X�V����-- //
		else if (scene == GAMESCENE) {
			// --�Q�[���V�[���X�V����-- //
			gameScene->Update();

			// --�X�R�A�X�V����-- //
			score->Update();
		}

		// --���U���g�V�[���X�V����-- //
		else if (scene == RESULTSCENE) {
			// --���U���g�V�[���X�V����-- //
			resultScene->Update();
		}
	}

	// --�V�[���ύX�X�V����-- //
	UpdateChangeScene();
}

// --�`�揈��-- //
void SceneManager::Draw() {
	// --�^�C�g���V�[���`�揈��-- //
	if (scene == TITLESCENE) {
		titleScene->Draw();
	}

	// --�Q�[���V�[���`�揈��-- //
	else if (scene == GAMESCENE) {
		// --�Q�[���V�[���`��-- //
		gameScene->Draw();

		// --�X�R�A�`��-- //
		if (gameScene->GetIsMainGame()) {
			score->Draw();
		}
	}

	// --���U���g�V�[���`�揈��-- //
	else if (scene == RESULTSCENE) {
		// --���U���g�V�[���`�揈��-- //
		resultScene->Draw();
	}

	// --�V�[���ύX�`�揈��-- //
	DrawChangeScene();
}

// --�V�[���؂�ւ�-- //
void SceneManager::SetScene(int sceneNum) {
	changeScene = sceneNum;
	isChangeScene = true;
}

// --�V�[���ύX����-- //
void SceneManager::UpdateChangeScene() {
	// --�V�[���ύX�t���O--true�������� //
	if (isChangeScene == true) {
		// --�t�F�[�h�A�E�g-- //
		if (isFadeOut == true) {
			if (circleSize > 0) {
				circleSize -= sizeChangeSpeed;
			}

			else if (circleSize <= 0) {
				timer++;
				if (timer >= sceneInterval) {
					sound->StopBGM(scene);
					isFadeOut = false;
					isFadeIn = true;
					scene = changeScene;
					timer = 0;
					sound->PlayBGM(scene);
				}
			}
		}

		// --�t�F�[�h�C��-- //
		else if (isFadeIn == true) {
			circleSize += sizeChangeSpeed;

			if (circleSize >= 800) {
				isFadeOut = true;
				isFadeIn = false;
				isChangeScene = false;
				circleSize = 800;
			}
		}
	}
}

// --�V�[���ύX�`�揈��-- //
void SceneManager::DrawChangeScene() {
	// --�V�[���ύX�t���O��true��������-- //
	if (isChangeScene) {
		SetDrawScreen(screenHandle);

		DrawBox(0, 0, 1280, 960, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

		// --�F-- //
		Color color = GetColor16("2720e1");

		SetDrawBright(color.red, color.green, color.blue);

		// --����-- //
		for (int i = 0; i < 1280; i++) {
			DrawRotaGraph(i, 480, 0.20f, 0.0f, circleGraph, true);
		}

		// --����-- //
		for (int i = 0; i < 960; i++) {
			DrawRotaGraph(640, i, 0.20f, 0.0f, circleGraph, true);
		}

		// --�����ȉ~�̊O���̑���-- //
		for (int i = 0; i < circleSize * 2.1f; i++) {
			DrawRotaGraphF(
				640.0f + cosf(Degree2Radian((360.0f / (circleSize * 2.1f)) * i)) * (circleSize + 13),
				480.0f + sinf(Degree2Radian((360.0f / (circleSize * 2.1f)) * i)) * (circleSize + 13),
				0.375f, 0.0f,
				circleGraph, true
			);
		}

		SetDrawBright(255, 255, 255);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		SetDrawBlendMode(DX_BLENDMODE_SRCCOLOR, 0);

		if (circleSize > 0) {
			DrawCircle(640, 480, circleSize, 0x000000, true);
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawScreen(DX_SCREEN_BACK);

		DrawGraph(0, 0, screenHandle, true);
	}

	// --�f�o�b�O���[�h-- //
	if (isDebugMode == true) {

	}
}

// --�f�o�b�O���[�h���擾-- //
bool SceneManager::GetDebugMode() {
	return isDebugMode;
}