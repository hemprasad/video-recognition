#include "videoInputCam.h"


videoInputCam::videoInputCam(void)
{
	//���� �� ����� ����� ������, � ������� ����� ����������� ������, �� �������� ������ � ������
	_videoInputCam(0);
}

videoInputCam::videoInputCam(int deviceNum)
{
	_videoInputCam(deviceNum);
}

void videoInputCam::_videoInputCam(int deviceNum)
{
	device = deviceNum;
	VI.setIdealFramerate(device, 15);
	SetRecognition(640, 480);
	// ������ �������� ������� �������
    image = cvCreateImage(cvSize(VI.getWidth(device),VI.getHeight(device)), IPL_DEPTH_8U, 3);
}

videoInputCam::~videoInputCam(void)
{
	VI.stopDevice(device);
}

void videoInputCam::SetRecognition(int x, int y)
{
	VI.setupDevice(device, x, y, VI_COMPOSITE);
}

int videoInputCam::GetX(void)
{
	return VI.getWidth(device);
}

int videoInputCam::GetY(void)
{
	return VI.getHeight(device);
}

IplImage* videoInputCam::GetFrame(void)
{
	// ������ �������� - ������ ��������������
    // ������ - ��������� �� ����� ��� ���������� ������
    // ������ - ����, ������������ ������ �� ������� B � R -������������
    // �������� - ����, ������������ ������������ �������� ��� ���
    VI.getPixels(device, (unsigned char *)image->imageData, false, true); // ��������� �������� � BGR
	return image;
}

bool videoInputCam::isFrameNew(void)
{
	return VI.isFrameNew(device);
}