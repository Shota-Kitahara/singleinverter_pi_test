//###########################################################################
//
// FILE:   ePwmFunction.c
//
// TITLE: Enhanced PWM function to use standard inverter
//
//###########################################################################
// $TI Release: NPE Library ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/

#include "ePwmFunction.h"

void N_ConfigSTDInverterEPWMs(u4 base, u4 u4_capk, u4 u4_deadTime)
{
    EPWM_setTimeBasePeriod(base, u4_capk);  // PWM周期をセットする
    EPWM_setTimeBaseCounter(base, 0U);      // 読み込み時と現在のカウント値を出力し，書き込みした場合PWMカウント値をセットできる
    EPWM_setPhaseShift(base, 0U);           // 位相シフト量
    EPWM_setCounterCompareValue(base,EPWM_COUNTER_COMPARE_A,u4_capk>>1);    // PWM比較するレジスタA
    EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_UP_DOWN);   // カウントモード
    EPWM_disablePhaseShiftLoad(base);   // TBPHSから値を読み込むかどうか
    if(base == EPWM1_BASE){
        EPWM_setSyncOutPulseMode(base, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO); // 同期信号をどうするか
    }
    else{
        EPWM_setSyncOutPulseMode(base, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN); // 同期信号をどうするか
    }
    EPWM_setPeriodLoadMode(base, EPWM_PERIOD_SHADOW_LOAD);  // TBPRDのシャドウレジスタを使用するかどうか
    EPWM_setSyncOutPulseMode(base, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO); // 同期信号をどうするか
    EPWM_setClockPrescaler(base,EPWM_CLOCK_DIVIDER_1,EPWM_HSCLOCK_DIVIDER_1);   // クロック分周するかどうか
    EPWM_setCountModeAfterSync(base, EPWM_COUNT_MODE_DOWN_AFTER_SYNC);  // フェーズシフト方向
    EPWM_setCounterCompareShadowLoadMode(base,EPWM_COUNTER_COMPARE_A,EPWM_COMP_LOAD_ON_CNTR_ZERO);   //指令値の更新タイミング(シャドウレジスタ)を設定
    EPWM_setActionQualifierAction(base,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_HIGH,EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);  // 三角波がダウン時に指令値と一致した時のPWMの動作
    EPWM_setActionQualifierAction(base,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_LOW,EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);     // 三角波がアップ時に指令値と一致した時のPWMの動作
    // DeadBand setting
    EPWM_setRisingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);        // DBRising入力信号
    EPWM_setFallingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);       // DBFalling入力
    EPWM_setRisingEdgeDelayCount(base,u4_deadTime);                           // Risingデットタイム時間
    EPWM_setFallingEdgeDelayCount(base,u4_deadTime);                          // Fallingデットタイム時間
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_HIGH); // 通常のデットタイム
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);  // 反転
    EPWM_setDeadBandDelayMode(base, EPWM_DB_RED, true);                     // 出力ON
    EPWM_setDeadBandDelayMode(base, EPWM_DB_FED, true);                     // 出力ON
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_A, false);          // スワップOFF
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_B, false);          // スワップOFF
    EPWM_setDeadBandCounterClock(base,EPWM_DB_COUNTER_CLOCK_HALF_CYCLE);    // デットタイムの分解能CLKの2倍にする
    // DC and TZ setting
    EPWM_selectDigitalCompareTripInput(base,EPWM_DC_TRIP_TRIPIN4,EPWM_DC_TYPE_DCAH); // DCAH信号を選択。TRIPIN4でアナログコンパレータエラー
    EPWM_setTripZoneDigitalCompareEventCondition(base,EPWM_TZ_DC_OUTPUT_A1,EPWM_TZ_EVENT_DCXH_HIGH); // DCAEVT1信号を選択。DCAHがhighした時にオン
    EPWM_enableTripZoneSignals(base,EPWM_TZ_SIGNAL_DCAEVT1);
    EPWM_enableTripZoneInterrupt(base,EPWM_TZ_INTERRUPT_OST);
    EPWM_setTripZoneAction(base,EPWM_TZ_ACTION_EVENT_TZA,EPWM_TZ_ACTION_LOW);
    EPWM_setTripZoneAction(base,EPWM_TZ_ACTION_EVENT_TZB,EPWM_TZ_ACTION_LOW);
}

