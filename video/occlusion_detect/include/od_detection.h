#ifndef _OCCLUSION_DETECTION_H
#define _OCCLUSION_DETECTION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned short flag;           // 1 有效， 0无效
	unsigned short up_left[2];     // 下采样前左上角坐标，0是y坐标，1是x坐标
	unsigned short down_right[2];  // 下采样前右下角坐标，0是y坐标，1是x坐标
	unsigned short occlusion;      // 1 遮挡， 0没遮挡
} OD_ROI_INFO;

typedef void* od_ctx;

od_ctx od_detection_init(int width, int height);
int od_detection_deinit(od_ctx ctx);
int od_detection(od_ctx ctx, void *downscale_frame_y, OD_ROI_INFO *p_roi_in, int roi_cnt);

#ifdef __cplusplus
} //extern "C"
#endif

#endif // _OCCLUSION_DETECTION_H
