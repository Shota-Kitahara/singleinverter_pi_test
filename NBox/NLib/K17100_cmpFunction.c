//###########################################################################
//
// FILE:   K17100_cmpFunction.c
//
// TITLE: Analog comparator function to use k17100 board
//
//###########################################################################
// $TI Release: NPE Library ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/

#include "K17100_cmpFunction.h"

#define TRIP4MUXENABLE          0x20

#define COMPLINV        1       // Logic invert
#define SELREF          1       // VDAC is the voltage reference for the DAC
#define CTRIPHSEL       2       // Output of digital filter drives
#define CTRIPLSEL       2       // Output of digital filter drives
#define THRESH          5       // High side Digital filter value
#define FILINIT         1       // Initialize the sample values in the digital FIFO
#define COMPDACE        1       // Comparator and DAC enable


void N_ConfigCmpss(u4 u4_CT_Num, f4 f4_period)
{
    Uint16 CLKPRESCALE;
    Uint16 cmpssBaseAddr, epwmXbarBaseAddr;
    u4  u4_cmpNum;
    Uint16 cast;

    cast = ((f4)DEVICE_SYSCLK_FREQ * f4_period) / (f4)THRESH;
    CLKPRESCALE = (Uint16)cast;
    //CLKPRESCALE = (Uint16)(((f4)DEVICE_SYSCLK_FREQ * f4_period) / (f4)THRESH);

    switch(u4_CT_Num){
         case 1:
             u4_cmpNum = 1;
             break;
         case 2:
             u4_cmpNum = 6;
             break;
         case 3:
             u4_cmpNum = 7;
             break;
         case 4:
             u4_cmpNum = 2;
             break;
         case 5:
             u4_cmpNum = 5;
             break;
         case 6:
             u4_cmpNum = 8;
             break;
         default:
             break;
     }

    cmpssBaseAddr = (Uint16)&Cmpss1Regs + 32*(u4_cmpNum-1);
    epwmXbarBaseAddr = (Uint16)&EPwmXbarRegs;
    EALLOW;
    HWREGH(cmpssBaseAddr + CMPSS_O_COMPCTL) |= (Uint16)CMPSS_COMPCTL_COMPLINV;           // Logic invert
    HWREGH(cmpssBaseAddr + CMPSS_O_COMPCTL) |= (Uint16)CMPSS_COMPCTL_COMPDACE;
    HWREGH(cmpssBaseAddr + CMPSS_O_COMPDACCTL)   |= (Uint16)CMPSS_COMPDACCTL_SELREF;
    HWREGH(cmpssBaseAddr + CMPSS_O_COMPCTL) |= (Uint16)((CTRIPLSEL << CMPSS_COMPCTL_CTRIPLSEL_S) & CMPSS_COMPCTL_CTRIPLSEL_M);
    HWREGH(cmpssBaseAddr + CMPSS_O_COMPCTL) |= (Uint16)((CTRIPHSEL << CMPSS_COMPCTL_CTRIPHSEL_S) & CMPSS_COMPCTL_CTRIPHSEL_M);

    HWREGH(cmpssBaseAddr + CMPSS_O_CTRIPLFILCTL) |= (Uint16)(((THRESH-2) << CMPSS_CTRIPLFILCTL_SAMPWIN_S) & CMPSS_CTRIPLFILCTL_SAMPWIN_M);
    HWREGH(cmpssBaseAddr + CMPSS_O_CTRIPLFILCLKCTL) |= (Uint16)((CLKPRESCALE<< CMPSS_CTRIPLFILCLKCTL_CLKPRESCALE_S) & CMPSS_CTRIPLFILCLKCTL_CLKPRESCALE_M);
    HWREGH(cmpssBaseAddr + CMPSS_O_CTRIPLFILCTL) |= (Uint16)(((THRESH-2) << CMPSS_CTRIPLFILCTL_THRESH_S) & CMPSS_CTRIPLFILCTL_THRESH_M);

    HWREGH(cmpssBaseAddr + CMPSS_O_CTRIPHFILCTL) |= (Uint16)(((THRESH-2) << CMPSS_CTRIPHFILCTL_SAMPWIN_S) & CMPSS_CTRIPHFILCTL_SAMPWIN_M);
    HWREGH(cmpssBaseAddr + CMPSS_O_CTRIPHFILCLKCTL) |= (Uint16)((CLKPRESCALE<< CMPSS_CTRIPHFILCLKCTL_CLKPRESCALE_S) & CMPSS_CTRIPHFILCLKCTL_CLKPRESCALE_M);
    HWREGH(cmpssBaseAddr + CMPSS_O_CTRIPHFILCTL) |= (Uint16)(((THRESH-2) << CMPSS_CTRIPHFILCTL_THRESH_S) & CMPSS_CTRIPHFILCTL_THRESH_M);

    HWREGH(cmpssBaseAddr + CMPSS_O_CTRIPLFILCTL) |= (Uint16)CMPSS_CTRIPLFILCTL_FILINIT;
    HWREGH(cmpssBaseAddr + CMPSS_O_CTRIPHFILCTL) |= (Uint16)CMPSS_CTRIPHFILCTL_FILINIT;

    HWREG(epwmXbarBaseAddr + TRIP4MUXENABLE) |= (Uint32)(0x3 << (2*(u4_cmpNum-1)));
    EDIS;
}


void N_HardCmpHigh(u4 u4_CT_Num,f4 f4g_gain, f4 f4_protect_current)
{
    Uint16 cmpssBaseAddr;
    f4  f4_gain;
    u4  u4_cmpNum;
    s2  s2_plusVal;
    s2  s2_IH;
    f4  f4_cast;

    switch(u4_CT_Num){
         case 1:
             u4_cmpNum = 1;
             break;
         case 2:
             u4_cmpNum = 6;
             break;
         case 3:
             u4_cmpNum = 7;
             break;
         case 4:
             u4_cmpNum = 2;
             break;
         case 5:
             u4_cmpNum = 5;
             break;
         case 6:
             u4_cmpNum = 8;
             break;
         default:
             break;
     }

    f4_gain  = f4g_gain;

    f4_cast = f4_protect_current /f4_gain;
    s2_plusVal = (s2)f4_cast;
    //s2_plusVal = (s2)(f4_protect_current /f4_gain);
    s2_plusVal = LIMIT(s2_plusVal,0,2047);
    s2_IH = 2048 + s2_plusVal;
    s2_IH = LIMIT(s2_IH,2048,4095);

    cmpssBaseAddr = (Uint16)&Cmpss1Regs + 32*(u4_cmpNum-1);
    HWREGH(cmpssBaseAddr + CMPSS_O_DACHVALS) = (Uint16)((((u2)s2_IH) << CMPSS_DACHVALS_DACVAL_S) & CMPSS_DACHVALS_DACVAL_M);
}
void N_HardCmpLow(u4 u4_CT_Num, f4 f4g_gain, f4 f4_protect_current)
{
    Uint16 cmpssBaseAddr;
    f4  f4_gain;
    u4  u4_cmpNum;
    s2  s2_minusVal;
    s2  s2_IL;
    f4  f4_cast;

    switch(u4_CT_Num){
         case 1:
             u4_cmpNum = 1;
             break;
         case 2:
             u4_cmpNum = 6;
             break;
         case 3:
             u4_cmpNum = 7;
             break;
         case 4:
             u4_cmpNum = 2;
             break;
         case 5:
             u4_cmpNum = 5;
             break;
         case 6:
             u4_cmpNum = 8;
             break;
         default:
             break;
     }

    f4_gain  = f4g_gain;
    f4_cast = f4_protect_current /f4_gain;
    s2_minusVal = (s2)f4_cast;
    //s2_minusVal = (s2)( f4_protect_current /f4_gain);
    s2_minusVal = LIMIT(s2_minusVal,-2048,0);
    s2_IL = 2048 + s2_minusVal;
    s2_IL = LIMIT(s2_IL,0,2048);

    cmpssBaseAddr = (Uint16)&Cmpss1Regs + 32*(u4_cmpNum-1);
    HWREGH(cmpssBaseAddr + CMPSS_O_DACLVALS) = (Uint16)((((u2)s2_IL) << CMPSS_DACLVALS_DACVAL_S) & CMPSS_DACLVALS_DACVAL_M);
}


