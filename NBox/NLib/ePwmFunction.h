//###########################################################################
//
// FILE:   ePwmFunction.h
//
// TITLE: Enhanced PWM function to use standard inverter
//
//###########################################################################
// $TI Release: NPE Library ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/


#ifndef EPWMFUNCTION_H_
#define EPWMFUNCTION_H_

#include "NLibrary.h"

#define N_ALL_PWM_ON()\
{\
EALLOW;\
    EPWM_clearTripZoneFlag(EPWM1_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM2_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM3_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM4_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM5_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM6_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM7_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM8_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM9_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM10_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM11_BASE,EPWM_TZ_FLAG_OST);\
    EPWM_clearTripZoneFlag(EPWM12_BASE,EPWM_TZ_FLAG_OST);\
EDIS;\
}


#define N_ALL_PWM_OFF() {EALLOW; \
                    EPWM_forceTripZoneEvent(EPWM1_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM2_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM3_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM4_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM5_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM6_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM7_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM8_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM9_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM10_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM11_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                    EPWM_forceTripZoneEvent(EPWM12_BASE,EPWM_TZ_FORCE_EVENT_OST);\
                        EDIS;}


#define     N_ConfigSTDInverterEPWM1(){\
                             EPwm1Regs.  TBPRD                       =   DSP_CAPK    ;       PWM周期をセットする\
                             EPwm1Regs.  TBCTR                       =   0x0000      ;       読み込み時と現在のカウント値を出力し，書き込みした場合PWMカウント値をセットできる\
                             EPwm1Regs.  TBPHS.  bit.    TBPHS       =   0x0000      ;       位相シフト量\
                             EPwm1Regs.  CMPA.   bit.    CMPA        =   DSP_CAPK>>1 ;       PWM比較するレジスタA\
                             EPwm1Regs.  DBRED.  bit.    DBRED       =   DSP_DEADT;          デットタイム時間\
                             EPwm1Regs.  DBFED.  bit.    DBFED       =   DSP_DEADT;          デットタイム時間\
                             EPwm1Regs.  TBCTL.  bit.    CTRMODE     =   TB_COUNT_UPDOWN ;   カウントモード\
                             EPwm1Regs.  TBCTL.  bit.    PHSEN       =   TB_DISABLE  ;       TBPHSから値を読み込むかどうか\
                             EPwm1Regs.  TBCTL.  bit.    PRDLD       =   TB_SHADOW   ;       シャドウレジスタを使用するかどうか\
                             EPwm1Regs.  TBCTL.  bit.    SYNCOSEL    =   TB_CTR_ZERO ;       同期信号をどうするか\
                             EPwm1Regs.  TBCTL.  bit.    HSPCLKDIV   =   TB_DIV1 ;           クロック分周するかどうか\
                             EPwm1Regs.  TBCTL.  bit.    CLKDIV      =   TB_DIV1 ;           クロック分周するかどうか\
                             EPwm1Regs.  TBCTL.  bit.    PHSDIR      =   TB_DOWN ;           フェーズシフト方向\
                             EPwm1Regs.  CMPCTL. bit.    LOADAMODE   =   CC_CTR_ZERO ;       指令値の更新タイミングを設定\
                             EPwm1Regs.  CMPCTL. bit.    SHDWAMODE   =   CC_SHADOW   ;       指令値の更新がシャドウモードか即時モードか\
                             EPwm1Regs.  AQCTLA. bit.    CAU         =   AQ_CLEAR;           三角波がアップ時に指令値と一致した時のPWMの動作\
                             EPwm1Regs.  AQCTLA. bit.    CAD         =   AQ_SET  ;           三角波がダウン時に指令値と一致した時のPWMの動作\
                             EPwm1Regs.  DBCTL.  bit.    OUT_MODE    =   DB_FULL_ENABLE  ;   デットタイムブロックを使うかどうか\
                             EPwm1Regs.  DBCTL.  bit.    POLSEL      =   DB_ACTV_HIC ;       出力極性を決定\
                             EPwm1Regs.  DBCTL.  bit.    IN_MODE     =   DBA_ALL ;           デットタイム入力信号について\
                             EPwm1Regs.  DBCTL.  bit.    HALFCYCLE   =   1   ;               デットタイムの分解能CLKの2倍にするかどうか\
                             EPwm1Regs.  DCTRIPSEL.bit.  DCAHCOMPSEL =   DC_TRIPIN4   ;      DCAH信号を選択。TRIPIN4でアナログコンパレータエラー \
                             EPwm1Regs.  TZDCSEL.bit.    DCAEVT1     =   TZ_DCAH_HI   ;      DCAEVT1信号を選択。DCAHがhighした時にオン\
                             EPwm1Regs.  TZSEL.  bit.    DCAEVT1     =   TZ_ENABLE    ;      OSTのトリップ信号を選択\
                             EPwm1Regs.  TZEINT. bit.    OST         =   TZ_ENABLE    ;      OSTトリップを許可するかどうか\
                             EPwm1Regs.  TZCTL.  bit.    TZA         =   TZ_FORCE_LO  ;      トリップ時のEPWMAの信号をどうするか\
                             EPwm1Regs.  TZCTL.  bit.    TZB         =   TZ_FORCE_LO  ;      トリップ時のEPWMBの信号をどうするか\
                             }


extern void N_ConfigSTDInverterEPWMs(u4 base, u4 u4_capk, u4 u4_deadTime);



#endif /* EPWMFUNCTION_H_ */
