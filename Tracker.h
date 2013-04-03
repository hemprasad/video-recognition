#pragma once
class Tracker
{
private:
	// Parameters
	int   nHistBins;                 // number of histogram bins
	float rangesArr[2];          // histogram range
	int vmin, vmax, smin; // limits for calculating hue


	// File-level variables
	IplImage * pHSVImg; // the input image converted to HSV color mode
	IplImage * pHueImg; // the Hue channel of the HSV image
	IplImage * pMask; // this image is used for masking pixels
	IplImage * pProbImg; // the face probability estimates for each pixel
	CvHistogram * pHist; // histogram of hue in the original face image

	CvRect prevFaceRect;  // location of face in previous frame
	CvBox2D faceBox;      // current face-location estimate


	int nFrames;

	void updateHueImage(const IplImage * pImg);

public:
	Tracker(const IplImage * pImg);
	~Tracker(void);
	void startTracking(IplImage * pImg, CvRect * pFaceRect);
	CvBox2D track(IplImage * pImg);
	void setVmin(int _vmin);
	void setSmin(int _smin);
};

