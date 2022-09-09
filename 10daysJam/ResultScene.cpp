#include "ResultScene.h"

// --�R���g���[���[�N���X-- //
#include "JoyPadInput.h"

// --�V�[���}�l�[�W���[�N���X-- //
#include "SceneManager.h"

// --�C���X�^���X��NULL����-- //
ResultScene* ResultScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
ResultScene* ResultScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new ResultScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�C���X�^���X���-- //
void ResultScene::Relese() {
	// --�C���X�^���X�����������牽�������ɏI������-- //
	if (myInstance == nullptr) return;

	// --�C���X�^���X���-- //
	delete myInstance;
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
ResultScene::ResultScene() {
#pragma region �C���X�^���X�ǂݍ���
	// --�R���g���[���[�N���X-- //
	pad = JoyPadInput::GetInstance();
#pragma endregion
}

// --�f�X�g���N�^-- //
ResultScene::~ResultScene() {

}

// --����������-- //
void ResultScene::Initialize() {

}

// --�X�V����-- //
void ResultScene::Update() {

}

// --�`�揈��-- //
void ResultScene::Draw() {

}