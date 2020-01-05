
#include <string.h>
#include <stdio.h>

#define VOICE_PROCESS_PARA_NUM_TOTAL                (500)                               /* 配置参数个数 */

#define AEC_BAND_NLP_PARA_GROUPS_8K                 (6)                                 /* AEC NLP 子带配置组数 8k */
#define AEC_BAND_NLP_PARA_GROUPS_16K                (8)                                 /* AEC NLP 子带配置组数 16k */

#define AEC_BAND_NLP_PARA_NUM                       (2)                                 /* AEC NLP      子带每组配置参数个数 */
#define AEC_BAND_NLP_PLUS_PARA_NUM                  (7)                                 /* AEC NLP PLUS 子带每组配置参数个数 */

short int g_ashwAecBandNlpPara_8k[AEC_BAND_NLP_PARA_GROUPS_8K][AEC_BAND_NLP_PARA_NUM] =
{
	/* BandPassThd      SuperEstFactor*/
	{      10,                 6      },                                                  /* Hz: 0    - 300  */
	{      10,                 6      },                                                  /* Hz: 300  - 650  */
	{      5,                  6      },                                                  /* Hz: 650  - 1075 */
	{      5,                  6      },                                                  /* Hz: 1075 - 1700 */
	{      0,                  6      },                                                  /* Hz: 1700 - 2700 */
	{      0,                  6      }                                                   /* Hz: 2700 - 4000 */
};

short int g_ashwAecBandNlpPara_16k[AEC_BAND_NLP_PARA_GROUPS_16K][AEC_BAND_NLP_PARA_NUM] =
{
	/* BandPassThd      SuperEstFactor*/
	{      10,                 6      },                                                  /* Hz: 0    - 300  */
	{      10,                 6      },                                                  /* Hz: 300  - 575  */
	{      10,                 6      },                                                  /* Hz: 575  - 950  */
	{      5,                  6      },                                                  /* Hz: 950  - 1425 */
	{      5,                  6      },                                                  /* Hz: 1425 - 2150 */
	{      5,                  6      },                                                  /* Hz: 2150 - 3350 */
	{      0,                  6      },                                                  /* Hz: 3350 - 5450 */
	{      0,                  6      },                                                  /* Hz: 5450 - 8000 */
};

short int g_ashwAecBandNlpPlusPara_8k[AEC_BAND_NLP_PARA_GROUPS_8K][AEC_BAND_NLP_PLUS_PARA_NUM] =
{
	/*  使能     FarThd   ErrEchoThd_L     ErrEchoThd_H     ErrRatioThd_L    ErrRatioThd_H    NlineDegree */
	{    0,        0,         0,              1,             3000,            6000,            1      },   /* Hz: 0    - 300  */
	{    0,        0,         0,              1,             3000,            6000,            1      },   /* Hz: 300  - 650  */
	{    0,        0,         0,              1,             3000,            6000,            1      },   /* Hz: 650  - 1075 */
	{    1,        0,         0,              1,             3000,            9000,            1      },   /* Hz: 1075 - 1700 */
	{    1,        0,         0,              1,             5000,            12000,           1      },   /* Hz: 1700 - 2700 */
	{    1,        0,         100,            400,           6000,            16000,           1      }    /* Hz: 2700 - 4000 */
};

short int g_ashwAecBandNlpPlusPara_16k[AEC_BAND_NLP_PARA_GROUPS_16K][AEC_BAND_NLP_PLUS_PARA_NUM] =
{
	/* 使能     FarThd   ErrEchoThd_L     ErrEchoThd_H     ErrRatioThd_L    ErrRatioThd_H    NlineDegree */
	{   0,        0,         0,              10,             9830,             16383,            1        },   /* Hz: 0    - 300  */
	{   0,        0,         0,              10,             9830,             16383,            1        },   /* Hz: 300  - 575  */
	{   0,        0,         0,              10,             9830,             16383,            1        },   /* Hz: 575  - 950  */
	{   0,        0,         0,              10,             9830,             16383,            1        },   /* Hz: 950  - 1425 */
	{   0,        0,         5,              20,             9830,             16383,            1        },   /* Hz: 1425 - 2150 */
	{   0,        0,         5,              30,             9830,             16383,            1        },   /* Hz: 2150 - 3350 */
	{   0,        0,         10,             50,             9830,             16383,            1        },   /* Hz: 3350 - 5450 */
	{   0,        0,         50,             300,            9830,             16383,            1        }    /* Hz: 5450 - 8000 */
};

/************************************************************************************
函数名称：
函数功能：
函数输入：
函数输出：
修改日期：
*************************************************************************************/
void RK_VOICE_SetPara(short int* pshwPara, short int  shwLen)
{
	int       swCnt, swCntI, swCntJ;
	int       swIndex;
	int       swNbFlag, swBandParaNum;

	short int* pshwBandParaTable;

	/* 参数空间初始化为0 */
	for (swCnt = 0; swCnt < shwLen; swCnt++)
	{
		pshwPara[swCnt] = 0;
	}

	/* -------- 总模块参数设置 -------- 参数序号：pshwPara[0]至pshwPara[9] */
	swIndex = 0;
	pshwPara[swIndex + 0] = 16000;                                                               /* INT16 Q0  采样率设置；当前仅支持8000,16000 */
	if (8000 == pshwPara[swIndex + 0])
	{
		swNbFlag = 1;
		swBandParaNum = AEC_BAND_NLP_PARA_GROUPS_8K;
	}
	else
	{
		swNbFlag = 0;
		swBandParaNum = AEC_BAND_NLP_PARA_GROUPS_16K;
	}
	pshwPara[swIndex + 9] = 1111;                                                                /* INT16 Q0  参数方案设置；固定值1111 */



	/* -------- AEC 参数设置 -------- 参数序号：pshwPara[10]至pshwPara[99] */
	swIndex = 10;
	pshwPara[swIndex + 0] = 1;                                                                   /* 使能标志：回声消除使能 */

	swIndex = swIndex + 1;
	pshwPara[swIndex + 0] = 0;                                                                   /* 使能标志：延时估计使能 */
	pshwPara[swIndex + 1] = 2;                                                                   /* INT16 Q0  默认的最大delay值 关闭时延估计模块时 */

	swIndex = swIndex + 2;
	pshwPara[swIndex + 0] = 1;                                                                   /* 使能标志: 非线性回声消除SER方法 */
	pshwPara[swIndex + 1] = 0;                                                                   /* 使能标志: 非线性回声消除COH方法 */
	pshwPara[swIndex + 2] = 1;                                                                   /* INT16 Q0  人工回声增益次方施加 */

	swIndex = swIndex + 3;
	if (AEC_BAND_NLP_PARA_GROUPS_8K == swBandParaNum)
	{
		for (swCntI = 0; swCntI < swBandParaNum; swCntI++)
		{
			for (swCntJ = 0; swCntJ < AEC_BAND_NLP_PARA_NUM; swCntJ++)
			{
				/* INT16 Q0  NLP BandPssThd；  INT16 Q0  回声过估计因子 */
				pshwPara[swIndex + swCntI * AEC_BAND_NLP_PARA_NUM + swCntJ] = g_ashwAecBandNlpPara_8k[swCntI][swCntJ];
			}
		}
	}
	else
	{
		for (swCntI = 0; swCntI < swBandParaNum; swCntI++)
		{
			for (swCntJ = 0; swCntJ < AEC_BAND_NLP_PARA_NUM; swCntJ++)
			{
				/* INT16 Q0  NLP BandPssThd；  INT16 Q0  回声过估计因子 */
				pshwPara[swIndex + swCntI * AEC_BAND_NLP_PARA_NUM + swCntJ] = g_ashwAecBandNlpPara_16k[swCntI][swCntJ];
			}
		}
	}

	/* AEC NLP PLUS 子带参数配置 */
	swIndex = swIndex + swBandParaNum * AEC_BAND_NLP_PARA_NUM;
	if (AEC_BAND_NLP_PARA_GROUPS_8K == swBandParaNum)
	{
		for (swCntI = 0; swCntI < swBandParaNum; swCntI++)
		{
			for (swCntJ = 0; swCntJ < AEC_BAND_NLP_PLUS_PARA_NUM; swCntJ++)
			{
				pshwPara[swIndex + swCntI * AEC_BAND_NLP_PLUS_PARA_NUM + swCntJ] = g_ashwAecBandNlpPlusPara_8k[swCntI][swCntJ];
			}
		}
	}
	else
	{
		for (swCntI = 0; swCntI < swBandParaNum; swCntI++)
		{
			for (swCntJ = 0; swCntJ < AEC_BAND_NLP_PLUS_PARA_NUM; swCntJ++)
			{
				pshwPara[swIndex + swCntI * AEC_BAND_NLP_PLUS_PARA_NUM + swCntJ] = g_ashwAecBandNlpPlusPara_16k[swCntI][swCntJ];
			}
		}
	}

	/* 整帧ST/DT判断 */
	swIndex = swIndex + swBandParaNum * AEC_BAND_NLP_PLUS_PARA_NUM;
	pshwPara[swIndex + 0] = 1;                                                                   /* INT16 Q0  DTD整帧判决:使用子带起始索引 1-24 */
	pshwPara[swIndex + 1] = 10;                                                                  /* INT16 Q0  DTD整帧判决:使用子带终止索引 1-24 */
	pshwPara[swIndex + 2] = 1;                                                                   /* INT16 Q0  DTD整帧判决:高于Gain阈值子带数高于该值判DT */
	pshwPara[swIndex + 4] = (short int)(0.25f * (1 << 15));                                          /* INT16 Q15 DTD整帧判决:Gain阈值初始值 */
	pshwPara[swIndex + 5] = (short int)(0.05f * (1 << 15));                                          /* INT16 Q15 DTD整帧判决:Gain阈值调整步长 */
	pshwPara[swIndex + 6] = (short int)(0.30f * (1 << 15));                                          /* INT16 Q15 DTD整帧判决:Gain阈值最大值 */
	pshwPara[swIndex + 7] = (short int)(0.20f * (1 << 15));                                          /* INT16 Q15 DTD整帧判决:Gain阈值最小值 */
	pshwPara[swIndex + 8] = 200;                                                                 /* INT16 Q0  参考信号电路噪声幅度 */

	/* -------- TX ANR 参数设置 -------- 参数序号：pshwPara[100]至pshwPara[109] */
	swIndex = 100;
	pshwPara[swIndex + 0] = 1;                                                                   /* 使能标志：噪声抑制使能 */
	pshwPara[swIndex + 1] = (short int)(0.98f * (1 << 15));                                          /* INT16 Q15 噪声抑制程度使能；注意不要配置为1.0 */

	/* -------- RX ANR 参数设置 -------- 参数序号：pshwPara[110]至pshwPara[119] */
	swIndex = 110;
	pshwPara[swIndex + 0] = 1;                                                                   /* 使能标志：噪声抑制使能 */
	pshwPara[swIndex + 1] = (short int)(0.98f * (1 << 15));                                          /* INT16 Q15 噪声抑制程度使能；注意不要配置为1.0 */

	/* -------- TX AGC 参数设置 -------- 参数序号：pshwPara[120]至pshwPara[139] */
	swIndex = 120;
	pshwPara[swIndex + 0] = 0;                                                                    /*           使能标志：上行AGC消除使能 */
	pshwPara[swIndex + 1] = (short int)(6.0f * (1 << 5));                                             /* INT16 Q5  线性段提升dB数 */
	pshwPara[swIndex + 2] = (short int)(-55.0f * (1 << 5));                                           /* INT16 Q5  扩张段起始能量dB阈值 */
	pshwPara[swIndex + 3] = (short int)(-40.0f * (1 << 5));                                           /* INT16 Q5  线性段起始能量dB阈值 */
	pshwPara[swIndex + 4] = (short int)(-16.0f * (1 << 5));                                           /* INT16 Q5  压缩段起始能量dB阈值 */
	pshwPara[swIndex + 5] = (short int)(1.5f * (1 << 12));                                            /* INT16 Q12 扩张段斜率 */
	pshwPara[swIndex + 6] = (short int)(0.8f * (1 << 12));                                            /* INT16 Q12 线性段斜率 */
	pshwPara[swIndex + 7] = (short int)(0.4f * (1 << 12));                                            /* INT16 Q12 压缩段斜率 */
	pshwPara[swIndex + 8] = 40;                                                                   /* INT16 Q0  扩张段时域平滑点数 */
	pshwPara[swIndex + 9] = 80;                                                                   /* INT16 Q0  线性段时域平滑点数 */
	pshwPara[swIndex + 10] = 80;                                                                   /* INT16 Q0  压缩段时域平滑点数 */

	/* -------- RX AGC 参数设置 -------- 参数序号：pshwPara[140]至pshwPara[159] */
	swIndex = 140;
	pshwPara[swIndex + 0] = 1;                                                                    /*           使能标志：下行AGC消除使能 */
	pshwPara[swIndex + 1] = (short int)(6.0f * (1 << 5));                                             /* INT16 Q5  线性段提升dB数 */
	pshwPara[swIndex + 2] = (short int)(-55.0f * (1 << 5));                                           /* INT16 Q5  扩张段起始能量dB阈值 */
	pshwPara[swIndex + 3] = (short int)(-40.0f * (1 << 5));                                           /* INT16 Q5  线性段起始能量dB阈值 */
	pshwPara[swIndex + 4] = (short int)(-16.0f * (1 << 5));                                           /* INT16 Q5  压缩段起始能量dB阈值 */
	pshwPara[swIndex + 5] = (short int)(1.2f * (1 << 12));                                            /* INT16 Q12 扩张段斜率 */
	pshwPara[swIndex + 6] = (short int)(0.8f * (1 << 12));                                            /* INT16 Q12 线性段斜率 */
	pshwPara[swIndex + 7] = (short int)(0.4f * (1 << 12));                                            /* INT16 Q12 压缩段斜率 */
	pshwPara[swIndex + 8] = 40;                                                                   /* INT16 Q0  扩张段时域平滑点数 */
	pshwPara[swIndex + 9] = 80;                                                                   /* INT16 Q0  线性段时域平滑点数 */
	pshwPara[swIndex + 10] = 80;                                                                   /* INT16 Q0  压缩段时域平滑点数 */


	/* -------- TX EQ 参数设置 -------- 参数序号：pshwPara[160]至pshwPara[299] */
	swIndex = 160;
	pshwPara[swIndex + 0] = 0;                                                                     /*           使能标志：上行EQ使能标志 */
	pshwPara[swIndex + 1] = 1;                                                                     /* INT16 Q0  EQ滤波器长度 */
	pshwPara[swIndex + 2] = (short int)(1.0f * (1 << 15));                                             /* INT16 Q15 EQ滤波器系数数组 */

	/* -------- RX EQ 参数设置 -------- 参数序号：pshwPara[300]至pshwPara[439] */
	swIndex = 300;
	pshwPara[swIndex + 0] = 0;                                                                     /*           使能标志：下行EQ使能标志 */
	pshwPara[swIndex + 1] = 1;                                                                     /* INT16 Q0  EQ滤波器长度 */
	pshwPara[swIndex + 2] = (short int)(1.0f * (1 << 15));                                             /* INT16 Q15 EQ滤波器系数数组 */


	/* -------- TX CNG 参数设置 -------- 参数序号：pshwPara[440]至pshwPara[449] */
	swIndex = 440;
	pshwPara[swIndex + 0] = 1;                                                                     /* 使能标志：CNG使能标志 */
	pshwPara[swIndex + 1] = 2;                                                                     /* INT16 Q0 施加舒适噪声幅度比例 */
	pshwPara[swIndex + 2] = 5;                                                                     /* INT16 Q0 白噪随机数生成幅度 */
}

int main()
{
	short int ashwPara[VOICE_PROCESS_PARA_NUM_TOTAL];

	FILE* fpin = fopen("RK_VoicePara_SER_plusoff_dealyoff.bin", "wb");

	RK_VOICE_SetPara(ashwPara, VOICE_PROCESS_PARA_NUM_TOTAL);

	fwrite(ashwPara, sizeof(short int), VOICE_PROCESS_PARA_NUM_TOTAL, fpin);
}