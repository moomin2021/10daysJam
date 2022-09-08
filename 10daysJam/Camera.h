#pragma once
#include"Util.h"

class Camera
{
private:
	//�����o�ϐ�
	Vector2 pos;

	int shakeCount;

public:
//�����o�֐�
	Vector2 GetPos()const { return pos; }

	void SetShakeCount(int shakeCount_);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns></returns>
	Camera();

	void CameraShake();

	void CameraReset();
};

