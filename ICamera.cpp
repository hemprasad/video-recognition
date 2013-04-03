//#include "cv.h"
#include "ICamera.h"


ICamera::ICamera(void)
{
}

ICamera::ICamera(int deviceNum)
{
}

ICamera::~ICamera(void)
{
}

IplImage* ICamera::GetFrame(void)
{
	return new IplImage;
}

void ICamera::SetRecognition(int x, int y)
{
}

int ICamera::GetX(void)
{
	return 0;
}

int ICamera::GetY(void)
{
	return 0;
}

bool ICamera::isFrameNew(void)
{
	return false;
}