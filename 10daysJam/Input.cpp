#include "Input.h"
#include"DxLib.h"

void Input::KeyUpdate()
{
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}

	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

bool Input::IsTrigger(char key)
{
	bool flag;
	flag = (keys[key] && !oldkeys[key]);
	return flag;
}

bool Input::IsPress(char key)
{
	bool flag;
	flag = keys[key];
	return flag;
}

bool Input::IsRelease(char key)
{
	bool flag;
	flag = (!keys[key] && oldkeys[key]);
	return flag;
}
