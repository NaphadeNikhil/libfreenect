#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"

IplImage *GlViewColor(IplImage *depth)
{
	static IplImage *image = 0;
	if (!image) image = cvCreateImage(cvSize(640,480), 8, 3);
	unsigned char *depth_mid = (unsigned char*)(image->imageData);
	int i;
	for (i = 0; i < 640*480; i++) {
		int lb = ((short *)depth->imageData)[i] % 256;
		int ub = ((short *)depth->imageData)[i] / 256;
		switch (ub) {
			case 0:
				depth_mid[3*i+2] = 255;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+0] = 255-lb;
				break;
			case 1:
				depth_mid[3*i+2] = 255;
				depth_mid[3*i+1] = lb;
				depth_mid[3*i+0] = 0;
				break;
			case 2:
				depth_mid[3*i+2] = 255-lb;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+0] = 0;
				break;
			case 3:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+0] = lb;
				break;
			case 4:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+0] = 255;
				break;
			case 5:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+0] = 255-lb;
				break;
			default:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+0] = 0;
				break;
		}
	}
	return image;
}

int main(int argc, char **argv)
{
	int res=0;
	int counter=0;
	uint32_t timestampvideo,timestampdepth;
	if(argc==2)res=atoi(argv[1]);
	if(res>=-1 && res<=1);
	else{
		printf("Error: Resolution must be -1/0/1\n");
		return -1;
	}
	while (cvWaitKey(10) < 0) {
/*		IplImage *image = freenect_sync_get_rgb_cv(0,res,&timestampvideo);*/
/*		cvCvtColor(image, image, CV_RGB2BGR);*/
		IplImage *image = freenect_sync_get_ir_cv(0,res,&timestampvideo);
		if (!image) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}
		IplImage *depth = freenect_sync_get_depth_cv(0,&timestampdepth);
		if (!depth) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}
		cvShowImage("RGB/IR", image);
		cvShowImage("Depth", GlViewColor(depth));
	}
	return 0;
}
