#ifndef FREENECT_CV_H
#define FREENECT_CV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <opencv/cv.h>
#include <inttypes.h>

	typedef enum {
		LOW    = -1, /**< QVGA - 320x240 */
		MEDIUM = 0, /**< VGA  - 640x480 */
		HIGH   = 1, /**< SXGA - 1280x1024 */
	
	} my_resolution;
	IplImage *freenect_sync_get_depth_cv(int index,unsigned int *ts);
	IplImage *freenect_sync_get_rgb_cv(int index,int res,unsigned int *ts);
	IplImage *freenect_sync_get_ir_cv(int index,int res,unsigned int *ts);

#ifdef __cplusplus
}
#endif

#endif
