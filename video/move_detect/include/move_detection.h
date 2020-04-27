#ifndef _MOVE_DETECTION_H
#define _MOVE_DETECTION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned short flag;      // 1 有效， 0无效
	unsigned short up_left[2];     // 左上角坐标，下采样前，0是y坐标，1是x坐标
	unsigned short down_right[2];   // 右下角坐标，下采样前，0是y坐标，1是x坐标
} INFO_LIST;

typedef struct {
	unsigned short flag;      // 1 有效， 0无效
	unsigned short is_move;   // 运动标志
	unsigned short up_left[2];     // 下采样前左上角坐标，0是y坐标，1是x坐标
	unsigned short down_right[2];   // 下采样前右下角坐标，0是y坐标，1是x坐标
} ROI_INFO;

struct md_ctx;

typedef struct {
	int still_threshold0;
	int still_threshold1;
	int pix_threshold;
	int reserved[32];
} MD_PARAMS;

struct md_ctx *move_detection_init(int width, int height, int width_ds, int height_ds, int is_single_ref);
int move_detection_set_params(struct md_ctx *ctx, MD_PARAMS param);
void move_detection_deinit(struct md_ctx *ctx);
void move_detection(struct md_ctx *ctx, void *downscale_frame_y, ROI_INFO * p_roi_in, INFO_LIST *info_list);

#ifdef __cplusplus
} //extern "C"
#endif

#endif
