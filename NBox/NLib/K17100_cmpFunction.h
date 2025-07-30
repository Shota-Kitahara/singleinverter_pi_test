//###########################################################################
//
// FILE:   K17100_cmpFunction.h
//
// TITLE: Analog comparator function to use k17100 board
//
//###########################################################################
// $TI Release: NPE Library ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/

#ifndef K17100_CMPFUNCTION_H_
#define K17100_CMPFUNCTION_H_

#include "NLibrary.h"

#define N_CMP_CT1_LATCH     CMPSS_getStatus(CMPSS1_BASE) //CMP_LATCH_CT1
#define N_CMP_CT2_LATCH     CMPSS_getStatus(CMPSS6_BASE) //CMP_LATCH_CT2
#define N_CMP_CT3_LATCH     CMPSS_getStatus(CMPSS7_BASE) //CMP_LATCH_CT3
#define N_CMP_CT4_LATCH     CMPSS_getStatus(CMPSS2_BASE) //CMP_LATCH_CT4
#define N_CMP_CT5_LATCH     CMPSS_getStatus(CMPSS5_BASE) //CMP_LATCH_CT5
#define N_CMP_CT6_LATCH     CMPSS_getStatus(CMPSS8_BASE) //CMP_LATCH_CT6

static inline void N_CMP_CLEAR(u4 u4_CT_Num)
{
    u4 base;
    switch(u4_CT_Num){
         case 1:
             base = CMPSS1_BASE;
             break;
         case 2:
             base = CMPSS6_BASE;
             break;
         case 3:
             base = CMPSS7_BASE;
             break;
         case 4:
             base = CMPSS2_BASE;
             break;
         case 5:
             base = CMPSS5_BASE;
             break;
         case 6:
             base = CMPSS8_BASE;
             break;
         default:
             break;
    }
    EALLOW;
    CMPSS_clearFilterLatchHigh(base);
    CMPSS_clearFilterLatchLow(base);
    EDIS;
}


extern void N_ConfigCmpss(u4 u4_CT_Num, f4 f4_period);
extern void N_HardCmpHigh(u4 u4_CT_Num,f4 f4g_gain, f4 f4_protect_current);
extern void N_HardCmpLow(u4 u4_CT_Num, f4 f4g_gain, f4 f4_protect_current);




#endif /* K17100_CMPFUNCTION_H_ */
