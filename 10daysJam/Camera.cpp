#include "Camera.h"
#include"Util.h"
using namespace Util;

void Camera::SetShakeCount(int shakeCount_)
{
	shakeCount = shakeCount_;
}

Camera::Camera() :pos{0,0}
{
}

void Camera::CameraShake()
{
	if (shakeCount <= 0) {
		CameraReset();
		return;
	};
	int randNumX = Random(-20, 20);
	int randNumY = Random(-20, 20);
	pos.x += randNumX;
	pos.y += randNumY;

	shakeCount--;
	
}

void Camera::CameraReset()
{
	pos = { 0,0 };
}
