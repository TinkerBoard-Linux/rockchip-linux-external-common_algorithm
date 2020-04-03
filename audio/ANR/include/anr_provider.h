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
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ANR_INTERFACE_H
#define ANR_INTERFACE_H


#ifdef __cplusplus
extern "C" {
#endif

/* Set preprocessor denoiser state */
#define RK_DENOISE_PREPROCESS_SET 0
/* Get preprocessor denoiser state */
#define RK_DENOISE_PREPROCESS_GET 1
/* Set proprocessor denoiser rate */
#define RK_DENOISE_PREPROCESS_RATE 2
/* Set proprocessor denoiser frame length */
#define RK_DENOISE_PREPROCESS_FRMLEN 3

typedef void *APHandleType;

typedef struct ANRProcessState_
{
    int anr_enabled;

    /* Basic info */
    /* 8k~48k */
    int sampling_rate;
    /* frame time 10ms 16ms 20ms */
    int frame_size; // only 10ms|16ms|20ms
} ANRProcessState;

extern APHandleType ANR_Init(ANRProcessState *st);
extern void ANR_Destroy(APHandleType pstAnr);
extern void ANR_Process(APHandleType pstAnr, short  *pfSigIn, short *pfSigOut);
extern int ANR_Process_ctl(ANRProcessState *st, int request, void *ptr);

#ifdef __cplusplus
}
#endif
#endif