//###########################################################################
//
// FILE:   K17100_dacFunction.h
//
// TITLE: DAC function to use k17100 board
//
//###########################################################################
// $TI Release: NPE Library ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/

#ifndef K17100_DACFUNCTION_H_
#define K17100_DACFUNCTION_H_

#include "NLibrary.h"

#define DA0 0x3000
#define DA1 0x3100
#define DA2 0x3200
#define DA3 0x3300

static inline void
N_DACABCf4(u4 base, f4 f4_dadata)
{
    f4  f4_daVal;
    f4_daVal = (f4)(f4_dadata * 2048.0f + 2048.0f);
    f4  f4_cast;

    f4_cast = LIMIT_f4(f4_daVal,0.0f,4095.0f);
    DAC_setShadowValue(base, (u2)f4_cast);
    //DAC_setShadowValue(base, (u2)(LIMIT(f4_daVal,0.0,4095.0)));
}

static inline void
N_DaSPIf4 (u4 addres, f4 f4_dadata)
{
    f4  f4_daVal;
    u2  u2_transcode;
    u2  u2_Data1,u2_Data2;
    f4  f4_cast;

    f4_daVal = (f4)(f4_dadata * 2048.0f + 2048.0f);
    f4_cast = LIMIT(f4_daVal,0.0f,4095.0f);
    u2_transcode = (u2)f4_cast;
    //u2_transcode = (u2)(LIMIT(f4_daVal,0.0,4095.0));
    // o出力レンジ設定
    u2_Data1 = (u2_transcode<<4);
    u2_Data2 = (u2_transcode<<8)<<4;

    SPI_writeDataBlockingFIFO(SPIA_BASE,addres);
    SPI_writeDataBlockingFIFO(SPIA_BASE,u2_Data1);
    SPI_writeDataBlockingFIFO(SPIA_BASE,u2_Data2);
}

extern void N_ConfigDACABC(u4 base);

extern void N_ConfigDACSPI (void);


#endif /* K17100_DACFUNCTION_H_ */
