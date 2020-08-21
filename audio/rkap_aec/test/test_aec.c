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
#include <string.h>

#include "AP_AEC.h"

int main(int argc, char **argv)
{
    RKAP_Handle *ap_aec_tx = NULL, * ap_aec_rx = NULL;
    RKAP_AEC_State state;
    FILE *fp_near = NULL, *fp_far = NULL, *fp_out_tx = NULL, *fp_out_rx = NULL;
    int swFs;
    int swFrameLen;
    void *vParaData;
    short *swBufferIn, *swBufferRef, *swBufferOut;
    int dataLen = 0;
    char *out_rx_file = NULL;

#ifdef FOR_VS_DEBUG
    /* For Debug  */
    argc = 6;
    argv[1] = (char *)"../../../test_file/txin_noise.pcm";
    argv[2] = (char *)"../../../test_file/rxin.pcm";
    argv[3] = (char *)"../../../test_file/out_1.pcm";
    argv[4] = (char *)"../../../para/para_ser_8k.bin";
    argv[5] = (char *)"8000";
#endif
    if (argc != 6)
    {
        AEC_DumpVersion();
        fprintf(stderr, "Usage: ./test_aec <near.pcm> <far.pcm> <out.pcm> <para.bin> <rate 8000 or 16000>\n");
        fprintf(stderr, "For example:\n");
        fprintf(stderr, "  ./test_aec rec.pcm ref.pcm out_aec.pcm RKAP_AecPara.bin 8000\n");
        exit(1);
    }
    fp_near = fopen(argv[1], "rb");
    if (fp_near == NULL)
    {
        fprintf(stderr, "%s fp_near fopen failed\n", argv[1]);
        exit(1);
    }
    fp_far = fopen(argv[2], "rb");
    if (fp_far == NULL)
    {
        fprintf(stderr, "%s fp_far fopen failed\n", argv[2]);
        exit(1);
    }
    fp_out_tx = fopen(argv[3], "wb");
    if (fp_out_tx == NULL)
    {
        fprintf(stderr, "%s fp_out_tx fopen failed\n", argv[3]);
        exit(1);
    }
    out_rx_file = (char *)calloc(1, strlen(argv[3]) + 4);
    sprintf(out_rx_file, "%s_rx", argv[3]);
    fp_out_rx = fopen(out_rx_file, "wb");
    if (fp_out_rx == NULL)
    {
        fprintf(stderr, "%s fp_out_rx fopen failed\n", out_rx_file);
        exit(1);
    }

    state.pathPara = argv[4];

    swFs = atoi(argv[5]);
    if (swFs != 8000 && swFs != 16000)
    {
        fprintf(stderr, "Not supported sample rate: %d\n", swFs);
        exit(1);
    }
    swFrameLen  = swFs / 50;

    state.swSampleRate = swFs;
    state.swFrameLen = swFrameLen;

    /* tx init */
    ap_aec_tx = AEC_Init(&state, AEC_TX_TYPE);
    if (ap_aec_tx == NULL)
    {
        fprintf(stderr, "ap_aec_tx_Init failed\n");
        exit(1);
    }
    /* rx init */
    ap_aec_rx = AEC_Init(&state, AEC_RX_TYPE);
    if (ap_aec_rx == NULL)
    {
        fprintf(stderr, "ap_aec_rx_Init failed\n");
        exit(1);
    }

    swBufferIn = (short *)malloc(sizeof(short) * swFrameLen);
    swBufferRef = (short *)malloc(sizeof(short) * swFrameLen);
    swBufferOut = (short *)malloc(sizeof(short) * swFrameLen);

    while (!feof(fp_near) && !feof(fp_far))
    {
        dataLen = fread(swBufferIn, sizeof(short), swFrameLen, fp_near);
        dataLen = fread(swBufferRef, sizeof(short), swFrameLen, fp_far);
        AEC_Process(ap_aec_rx, swBufferIn, NULL, swBufferOut);
        fwrite(swBufferOut, sizeof(short), swFrameLen, fp_out_rx);
        AEC_Process(ap_aec_tx, swBufferIn, swBufferRef, swBufferOut);
        fwrite(swBufferOut, sizeof(short), swFrameLen, fp_out_tx);
    }

    AEC_Destroy(ap_aec_tx);
    AEC_Destroy(ap_aec_rx);
    free(swBufferRef);
    free(swBufferIn);
    free(swBufferOut);

    if (fp_far)
        fclose(fp_far);
    if (fp_near)
        fclose(fp_near);
    if (fp_out_tx)
        fclose(fp_out_tx);
    if (fp_out_rx)
        fclose(fp_out_rx);
    if (out_rx_file)
        free(out_rx_file);
    printf("done...\n");

    return 0;
}
