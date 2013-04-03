#pragma once
#include <cv.h>

class ICamera
{
public:
	ICamera(void);
	ICamera(int deviceNum);
	virtual ~ICamera(void);

	//���������� ������������� ���������� ��� ������
	virtual void SetRecognition(int x, int y);

	//���������� ������� ����������
	virtual int GetX(void);
	virtual int GetY(void);

	//���������� ������� �������� ���� � ������
	virtual IplImage* GetFrame(void);

	virtual bool isFrameNew(void);
};

