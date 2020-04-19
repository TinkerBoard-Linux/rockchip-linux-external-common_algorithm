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

#include "AP_AEC.h"

int main(int argc, char **argv)
{
    RKAP_Handle *ap_aec;
    RKAP_State state;
    FILE *fp_near = NULL, *fp_far = NULL, *fp_out = NULL;
    short *swBufferIn, *swBufferRef, *swBufferOut;
    int swFs = 8000;
    int swFrameLen = swFs / 50;
    int dataLen = 0;

    if (argc != 4)
    {
        fprintf(stderr, "%s is not 4\n", argv[0]);
        exit(1);
    }
    fp_near = fopen(argv[1], "rb");
    if (fp_near == NULL)
    {
        fprintf(stderr, "%s fp_near fopen failed\n", argv[0]);
        exit(1);
    }
    fp_far = fopen(argv[2], "rb");
    if (fp_far == NULL)
    {
        fprintf(stderr, "%s fp_far fopen failed\n", argv[0]);
        exit(1);
    }
    fp_out = fopen(argv[3], "wb");
    if (fp_near == NULL)
    {
        fprintf(stderr, "%s fp_out fopen failed\n", argv[0]);
        exit(1);
    }

    swBufferIn = (short *)malloc(sizeof(short) * swFrameLen);
    swBufferRef = (short *)malloc(sizeof(short) * swFrameLen);
    swBufferOut = (short *)malloc(sizeof(short) * swFrameLen);

    state.isEnabled = 1;
    state.swSampleRate = swFs;
    state.swFrameLen = swFrameLen;

    ap_aec = AEC_Init(&state);
    if (ap_aec == NULL)
    {
        fprintf(stderr, "ap_aec_Init failed\n");
        exit(1);
    }

    while (!feof(fp_near) && !feof(fp_far))
    {
        dataLen = fread(swBufferIn, sizeof(short), swFrameLen, fp_near);
        dataLen = fread(swBufferRef, sizeof(short), swFrameLen, fp_far);
        AEC_Process(ap_aec, swBufferIn, swBufferRef, swBufferOut);
        fwrite(swBufferOut, sizeof(short), swFrameLen, fp_out);
    }

    AEC_Destroy(ap_aec);
    free(swBufferRef);
    free(swBufferIn);
    free(swBufferOut);

    if (fp_far)
        fclose(fp_far);
    if (fp_near)
        fclose(fp_near);
    if (fp_out)
        fclose(fp_out);

    printf("done...\n");

    return 0;
}
