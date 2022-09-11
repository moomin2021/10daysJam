#include "SceneManager.h"

// --�C���X�^���X��NULL����-- //
SceneManager* SceneManager::myInstance = nullptr;

// --�ύX����V�[���̏�����-- //
int SceneManager::changeScene = 0;

// --�V�[���ύX�t���O�̏�����-- //
bool SceneManager::isChangeScene = false;

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
#pragma endregion

	// --�V�[��-- //
	scene = RESULTSCENE;

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
}

// --�X�V����-- //
void SceneManager::Update() {
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
		score->Draw();
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
					isFadeOut = false;
					isFadeIn = true;
					scene = changeScene;
					timer = 0;
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

		SetDrawBlendMode(DX_BLENDMODE_SRCCOLOR, 0);

		DrawCircle(640, 480, circleSize, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawScreen(DX_SCREEN_BACK);

		DrawGraph(0, 0, screenHandle, true);
	}

	DrawFormatString(0, 0, 0xFFFFFF, "isChangeScene:%d", isChangeScene);
	DrawFormatString(0, 40, 0xFFFFFF, "isFadeOut:%d", isFadeOut);
	DrawFormatString(0, 60, 0xFFFFFF, "isFadeIn:%d", isFadeIn);
	DrawFormatString(0, 80, 0xFFFFFF, "circleSize:%d", circleSize);
	DrawFormatString(0, 100, 0xFFFFFF, "timer:%d", timer);
}