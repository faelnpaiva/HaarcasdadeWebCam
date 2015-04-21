/*g++ -Wall -g -lm -DDEBUG `pkg-config --cflags opencv` Camera.cpp `pkg-config --libs opencv` -o Camera
 *
 */
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
void detectAndDisplay( Mat ); //IMPROTANTE
char key;
/** Global variables */ //IMPROTANTE
	String  face_cascade_name = "haarcascade_frontalface_alt.xml";
	String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	string window_name = "Capture - Face detection";
	RNG rng(12345);

void detectAndDisplay( Mat frame ) //IMPROTANTE
	{
		std::vector<Rect> faces;
		Mat frame_gray;

		cvtColor( frame, frame_gray, CV_BGR2GRAY );
		equalizeHist( frame_gray, frame_gray );

		//-- Detect faces
		face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

		for( size_t i = 0; i < faces.size(); i++ )
		{
			Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
			ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

			Mat faceROI = frame_gray( faces[i] );
			std::vector<Rect> eyes;

			//-- In each face, detect eyes
			eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

			for( size_t j = 0; j < eyes.size(); j++ )
			{
				Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
				int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
				circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
			}
		}
		//-- Show what you got
		imshow( window_name, frame );

	}

int main()
{
	cvNamedWindow("Camera_Output", 1); //Create window
	CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY); //Capture using any camera connected to your system

	//-- 1. Load the cascades
			if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };//IMPROTANTE
			if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };//IMPROTANTE


		while(1){ //Create infinte loop for live streaming
			IplImage* frame = cvQueryFrame(capture); //Create image frames from capture


			Mat img=cvarrToMat(frame);  //IMPROTANTE

			//-- 3. Apply the classifier to the frame
					 detectAndDisplay( img );//IMPROTANTE

			//cvShowImage("Camera_Output", frame); //Show image frames on created window
			key = cvWaitKey(0); //Capture Keyboard stroke //colocar o sensor por aqui ?!!?!?
			if (char(key) == 27){
				break; //If you hit ESC key loop will break.
			}
				}
		cvReleaseCapture(&capture); //Release capture.
		cvDestroyWindow("Camera_Output"); //Destroy Window
return 0;
}
