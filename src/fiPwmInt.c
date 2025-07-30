//###########################################################################
//
// FILE:  fiPwmInt.c
//
// TITLE: PWM Interrupt
//
//###########################################################################
// $TI Release: K17100 Base program ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/


#include "fiPwmInt.h"

#include "adDetection.h"
#include "pwmProtection.h"
#include "vRefCmdCal.h"
#include "sequenceCtl.h"
#include "fiIPCInt.h"


f4 test = 0.0f;



void fiPwmInt(){

    adDet();
    pwmProtection();
    if (s4g_IndError != 0){
        N_ALL_PWM_OFF();
    }

    vRefCmdCal();
    EPWM_setCounterCompareValue(EPWM1_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vuRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM2_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vvRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM3_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vwRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM4_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vuRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM5_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vvRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM6_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vwRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM7_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vuRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM8_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vvRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM9_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vwRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM10_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vuRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM11_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vvRef0 * 0.5f + 0.5f)));
    EPWM_setCounterCompareValue(EPWM12_BASE,EPWM_COUNTER_COMPARE_A ,(DSP_CAPK * (f4g_vwRef0 * 0.5f + 0.5f)));

    N_DACABCf4(DACA_BASE,test);

}

void fiPwmIntInit(){
	adDetInit();
	pwmProtectionInit();
	vRefCmdCalInit();

    N_ConfigDACABC(DACA_BASE);

}
