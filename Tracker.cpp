#include "cv.h"
#include <stdio.h>

#include "Tracker.h"


Tracker::Tracker(const IplImage * pImg)
{
	// Parameters
	nHistBins = 30;                 // number of histogram bins
	rangesArr[0]= 0;          // histogram range
	rangesArr[1] = 180;
	vmin = 65;
	vmax = 256;
	smin = 55; // limits for calculating hue


	// File-level variables
	pHSVImg  = 0; // the input image converted to HSV color mode
	pHueImg  = 0; // the Hue channel of the HSV image
	pMask    = 0; // this image is used for masking pixels
	pProbImg = 0; // the face probability estimates for each pixel
	pHist = 0; // histogram of hue in the original face image


	nFrames = 0;
	// Allocate the main data structures ahead of time
	float * pRanges = rangesArr;
	pHSVImg  = cvCreateImage( cvGetSize(pImg), 8, 3 );
	pHueImg  = cvCreateImage( cvGetSize(pImg), 8, 1 );
	pMask    = cvCreateImage( cvGetSize(pImg), 8, 1 );
	pProbImg = cvCreateImage( cvGetSize(pImg), 8, 1 );

	pHist = cvCreateHist( 1, &nHistBins, CV_HIST_ARRAY, &pRanges, 1 );
}


Tracker::~Tracker(void)
{
	// Release all tracker resources
	cvReleaseImage( &pHSVImg );
	cvReleaseImage( &pHueImg );
	cvReleaseImage( &pMask );
	cvReleaseImage( &pProbImg );

	cvReleaseHist( &pHist );
}

void Tracker::startTracking(IplImage * pImg, CvRect * pFaceRect)
{
	float maxVal = 0.f;

	// Make sure internal data structures have been allocated
	//if( !pHist ) createTracker(pImg);

	// Create a new hue image
	updateHueImage(pImg);

	// Create a histogram representation for the face
    cvSetImageROI( pHueImg, *pFaceRect );
    cvSetImageROI( pMask,   *pFaceRect );
    cvCalcHist( &pHueImg, pHist, 0, pMask );
    cvGetMinMaxHistValue( pHist, 0, &maxVal, 0, 0 );
    cvConvertScale( pHist->bins, pHist->bins, maxVal? 255.0/maxVal : 0, 0 );
    cvResetImageROI( pHueImg );
    cvResetImageROI( pMask );

	// Store the previous face location
	prevFaceRect = *pFaceRect;
}

CvBox2D Tracker::track(IplImage * pImg)
{
	CvConnectedComp components;

	// Create a new hue image
	updateHueImage(pImg);

	// Create a probability image based on the face histogram
	cvCalcBackProject( &pHueImg, pProbImg, pHist );
    cvAnd( pProbImg, pMask, pProbImg, 0 );

	// Use CamShift to find the center of the new face probability
    cvCamShift( pProbImg, prevFaceRect,
                cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ),
                &components, &faceBox );

	// Update face location and angle
    prevFaceRect = components.rect;
	faceBox.angle = -faceBox.angle;

	return faceBox;
}

void Tracker::updateHueImage(const IplImage * pImg)
{
	// Convert to HSV color model
	cvCvtColor( pImg, pHSVImg, CV_BGR2HSV );

	// Mask out-of-range values
	cvInRangeS( pHSVImg, cvScalar(0, smin, MIN(vmin,vmax), 0),
	            cvScalar(180, 256, MAX(vmin,vmax) ,0), pMask );

	// Extract the hue channel
	cvSplit( pHSVImg, pHueImg, 0, 0, 0 );
}

void Tracker::setVmin(int _vmin)
{ vmin = _vmin; }

void Tracker::setSmin(int _smin)
{ smin = _smin; }