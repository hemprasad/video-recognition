#include "videoInputCam.h"


videoInputCam::videoInputCam(void)
{
	//Если не задан номер камеры, с которой нужно производить захват, то получаем первую в списке
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
	// создаём картинку нужного размера
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
	// первый параметр - индекс видеоустройсва
    // второй - указатель на буфер для сохранения данных
    // третий - флаг, определяющий менять ли местами B и R -составляющий
    // четвёртый - флаг, определяющий поворачивать картинку или нет
    VI.getPixels(device, (unsigned char *)image->imageData, false, true); // получение пикселей в BGR
	return image;
}

bool videoInputCam::isFrameNew(void)
{
	return VI.isFrameNew(device);
}