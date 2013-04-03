#pragma once
#include "icamera.h"
#include <videoInput.h>

#ifdef _MSC_VER
// ����������� ��������� ��� MS VC
//# pragma comment(lib, "cxcore200.lib")
//# pragma comment(lib, "cv200.lib")
//# pragma comment(lib, "highgui200.lib")
# pragma comment(lib, "videoInput.lib")
#endif //#ifdef _MSC_VER

class videoInputCam :
	virtual public ICamera
{
private:
	//������ ������ ������
	videoInput VI;
	//����� ������, � ������� ��������
	int device;
	//���������� ������
	int resx, resy;
	IplImage *image;
public:
	videoInputCam(void);
	videoInputCam(int deviceNum);
	void _videoInputCam(int deviceNum);
	~videoInputCam(void);
	void SetRecognition(int x, int y);
	int GetX(void);
	int GetY(void);
	IplImage *GetFrame(void);
	bool isFrameNew(void);
};

