/*
 *  Copyright (C) 2020, Fuzhou Rockchip Electronics Co., Ltd.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of Fuzhou Rockchip Electronics Co., Ltd. nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "AP_ANR.h"

int main(int argc, char **argv)
{
    FILE *fp_in = NULL, *fp_out = NULL;
    short *swBufferIn, *swBufferOut;

    int swFs = 16000;
    int swChannel = 1;
    int swFrameLen = swFs / 50;
    int dataLen = 0;
    struct ANR_MAIN_STRUCT *pstAnr = NULL;
    RKAP_ANR_State state;

    if (argc != 3)
    {
        fprintf(stderr, "%s is not 3\n", argv[0]);
        exit(1);
    }
    fp_in = fopen(argv[1], "rb");
    if (fp_in == NULL)
    {
        fprintf(stderr, "%s fp_in fopen failed\n", argv[0]);
        exit(1);
    }
    fp_out = fopen(argv[2], "wb");
    if (fp_out == NULL)
    {
        fprintf(stderr, "%s fp_out fopen failed\n", argv[0]);
        exit(1);
    }

    swBufferIn = (short *)malloc(sizeof(short) * swFrameLen);
    swBufferOut = (short *)malloc(sizeof(short) * swFrameLen);

    /* set parameter */
    state.pfAnrBasicInfo.isEnabled = 1;
    state.pfAnrBasicInfo.swSampleRate = swFs;
    state.pfAnrBasicInfo.swFrameLen = swFrameLen;
    state.fGmin = -30;
    state.fPostAddGain = 0;
    state.fNoiseFactor = 0.98f;

    pstAnr = ANR_Init(&state);
    if (pstAnr == NULL)
    {
        fprintf(stderr, "ANR Init failed\n");
        exit(1);
    }

    do
    {
        dataLen = fread(swBufferIn, sizeof(short), swFrameLen, fp_in);
        ANR_Process(pstAnr, swBufferIn, swBufferOut);
        fwrite(swBufferOut, sizeof(short), swFrameLen, fp_out);
    }
    while (!feof(fp_in));

    ANR_Destroy(pstAnr);
    free(swBufferIn);
    free(swBufferOut);

    printf("done...\n");

    return 0;
}
