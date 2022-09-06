#include "Input.h"
#include"DxLib.h"

// --�C���X�^���X��NULL����-- //
Input* Input::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Input* Input::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new Input();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�R���X�g���N�^-- //
Input::Input() {

}

// --�X�V����-- //
void Input::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}

	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

// --�L�[�������ꂽ�u�Ԃ�-- //
bool Input::IsTrigger(char key) { return (keys[key] && !oldkeys[key]); }

// --�L�[��������Ă��邩-- //
bool Input::IsPress(char key) { return keys[key]; }

// --�L�[�������ꂽ�u�Ԃ�-- //
bool Input::IsRelease(char key) { return (!keys[key] && oldkeys[key]); }
