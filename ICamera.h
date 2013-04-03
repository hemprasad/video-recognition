#pragma once
#include <cv.h>

class ICamera
{
public:
	ICamera(void);
	ICamera(int deviceNum);
	virtual ~ICamera(void);

	//”становить рекомендуемое разрешение дл€ камеры
	virtual void SetRecognition(int x, int y);

	//¬озвращает текущее разрешение
	virtual int GetX(void);
	virtual int GetY(void);

	//¬озвращает текущий активный кадр с камеры
	virtual IplImage* GetFrame(void);

	virtual bool isFrameNew(void);
};

