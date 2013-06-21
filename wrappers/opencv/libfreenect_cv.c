#include "libfreenect.h"
#include "libfreenect_sync.h"
#include "libfreenect_cv.h"

IplImage *freenect_sync_get_depth_cv(int index,uint32_t* ts)
{
	static IplImage *image = 0;
	static char *data = 0;
	if (!image) image = cvCreateImageHeader(cvSize(640,480), 16, 1);
	uint32_t timestamp;
	if (freenect_sync_get_depth((void**)&data, &timestamp, index, FREENECT_DEPTH_11BIT))
	    return NULL;
	cvSetData(image, data, 640*2);
	*ts=timestamp;
	return image;
}

IplImage *freenect_sync_get_rgb_cv(int index, int res,uint32_t *ts)
{
	static IplImage *image = 0;
	static char *data = 0;
	uint32_t timestamp;
	if (freenect_sync_get_video((void**)&data, &timestamp, index, FREENECT_VIDEO_RGB,res))
	    return NULL;
	if(!res) {if (!image) image = cvCreateImageHeader(cvSize(640,480), 8, 3);
	cvSetData(image, data, 640*3);
	}
	else if (res==1){ if(!image) image = cvCreateImageHeader(cvSize(1280,1024), 8, 3);
	cvSetData(image, data, 1280*3);
	}
	
	else if(res==-1){ if(!image) image = cvCreateImageHeader(cvSize(320,240), 8, 3);
	cvSetData(image, data, 320*3);
	}
	else return NULL;
	
	*ts=timestamp;
	return image;
}

IplImage *freenect_sync_get_ir_cv(int index,int res,uint32_t *ts)
{
	static IplImage *image = 0;
	static char *data = 0;
	uint32_t timestamp=0;
	if (freenect_sync_get_video((void**)&data, &timestamp, index, FREENECT_VIDEO_IR_8BIT,res))
	    return NULL;
	
	if(!res) {if (!image) image = cvCreateImageHeader(cvSize(640,480), 8, 1);
	cvSetData(image, data, 640*1);
	}
	else if (res==1){ if(!image) image = cvCreateImageHeader(cvSize(1280,1024), 8, 1);
	cvSetData(image, data, 1280*1);
	}
	else if (res==-1){ if(!image) image = cvCreateImageHeader(cvSize(320,240), 8, 1);
	cvSetData(image, data, 320*1);
	}
	else return NULL;
	//printf("%u\n",timestamp);
	*ts=timestamp;
	return image;
}
