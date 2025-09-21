/*
 * Protection.c
 *
 *  Created on: 2015/10/07
 *      Author: ohnuma
 */


#include "pwmProtection.h"

#include "sequenceCtl.h"
#include "adDetection.h"
#include "iock.h"
#include "thermistor.h"


#define ERR_1   ((u4)(0x00000001))  //VT1
#define ERR_2   ((u4)(0x00000002))  //VT2
#define ERR_3   ((u4)(0x00000004))  //VT3
#define ERR_4   ((u4)(0x00000008))  //VT4
#define ERR_5   ((u4)(0x00000010))  //VT5
#define ERR_6   ((u4)(0x00000020))  //VT6
#define ERR_7   ((u4)(0x00000040))  //CT1
#define ERR_8   ((u4)(0x00000080))  //CT2
#define ERR_9   ((u4)(0x00000100))  //CT3
#define ERR_10  ((u4)(0x00000200))  //CT4
#define ERR_11  ((u4)(0x00000400))  //CT5
#define ERR_12  ((u4)(0x00000800))  //CT6
#define ERR_13  ((u4)(0x00001000))  //CompError(HardError)
#define ERR_14  ((u4)(0x00002000))  //TemperatureError
#define ERR_15  ((u4)(0x00004000))
#define ERR_16  ((u4)(0x00008000))
#define ERR_17  ((u4)(0x00010000))
#define ERR_18  ((u4)(0x00020000))
#define ERR_19  ((u4)(0x00040000))
#define ERR_20  ((u4)(0x00080000))
#define ERR_21  ((u4)(0x00100000))
#define ERR_22  ((u4)(0x00200000))
#define ERR_23  ((u4)(0x00400000))
#define ERR_24  ((u4)(0x00800000))
#define ERR_25  ((u4)(0x01000000))
#define ERR_26  ((u4)(0x02000000))
#define ERR_27  ((u4)(0x04000000))
#define ERR_28  ((u4)(0x08000000))
#define ERR_29  ((u4)(0x10000000))
#define ERR_30  ((u4)(0x20000000))

static void pwmErrckCount(f4 f4_adc, f4 f4_Hlevel, f4 f4_Llevel, s4 *s4_cnt, s4 s4_cnt_max, u4 u4_err_code);

s4  s4g_IndError;
s4  s4_hardError,s4_TempError;

f4  f4_H_1,f4_H_2,f4_H_3,f4_H_4,f4_H_5,f4_H_6,f4_H_7,f4_H_8,f4_H_9,f4_H_10,f4_H_11,f4_H_12;
f4  f4_L_1,f4_L_2,f4_L_3,f4_L_4,f4_L_5,f4_L_6,f4_L_7,f4_L_8,f4_L_9,f4_L_10,f4_L_11,f4_L_12;
s4  s4_cnt_1,s4_cnt_2,s4_cnt_3,s4_cnt_4,s4_cnt_5,s4_cnt_6,s4_cnt_7,s4_cnt_8,s4_cnt_9,s4_cnt_10,s4_cnt_11,s4_cnt_12;
s4  s4_cnt_max_1,s4_cnt_max_2,s4_cnt_max_3,s4_cnt_max_4,s4_cnt_max_5,s4_cnt_max_6,s4_cnt_max_7,s4_cnt_max_8,s4_cnt_max_9,s4_cnt_max_10,s4_cnt_max_11,s4_cnt_max_12;

f4  f4_Temperature_1,f4_Temperature_2,f4_Temperature_3,f4_Temperature_4,f4_Temperature_i;



void pwmProtection() {

    // Soft trip
    pwmErrckCount(f4g_v1Det, f4_H_1, f4_L_1, &s4_cnt_1, s4_cnt_max_1, ERR_1);
    pwmErrckCount(f4g_v2Det, f4_H_2, f4_L_2, &s4_cnt_2, s4_cnt_max_2, ERR_2);
    pwmErrckCount(f4g_v3Det, f4_H_3, f4_L_3, &s4_cnt_3, s4_cnt_max_3, ERR_3);
    pwmErrckCount(f4g_v4Det, f4_H_4, f4_L_4, &s4_cnt_4, s4_cnt_max_4, ERR_4);
    pwmErrckCount(f4g_v5Det, f4_H_5, f4_L_5, &s4_cnt_5, s4_cnt_max_5, ERR_5);
    pwmErrckCount(f4g_v6Det, f4_H_6, f4_L_6, &s4_cnt_6, s4_cnt_max_6, ERR_6);
    pwmErrckCount(f4g_i1Det, f4_H_7, f4_L_7, &s4_cnt_7, s4_cnt_max_7, ERR_7);
    pwmErrckCount(f4g_i2Det, f4_H_8, f4_L_8, &s4_cnt_8, s4_cnt_max_8, ERR_8);
    pwmErrckCount(f4g_i3Det, f4_H_9, f4_L_9, &s4_cnt_9, s4_cnt_max_9, ERR_9);
    pwmErrckCount(f4g_i4Det, f4_H_10, f4_L_10, &s4_cnt_10, s4_cnt_max_10, ERR_10);
    pwmErrckCount(f4g_i5Det, f4_H_11, f4_L_11, &s4_cnt_11, s4_cnt_max_11, ERR_11);
    pwmErrckCount(f4g_i6Det, f4_H_12, f4_L_12, &s4_cnt_12, s4_cnt_max_12, ERR_12);

    // CT1
    if (N_CMP_CT1_LATCH || N_CMP_CT2_LATCH || N_CMP_CT3_LATCH || N_CMP_CT4_LATCH || N_CMP_CT5_LATCH || N_CMP_CT6_LATCH){
        s4g_IndError |= ERR_13;
        if(N_CMP_CT1_LATCH){
            if(N_CMP_CT1_LATCH & CMPSS_STS_HI_LATCHFILTOUT) s4_hardError |= ERR_1;
            if(N_CMP_CT1_LATCH & CMPSS_STS_LO_LATCHFILTOUT) s4_hardError |= ERR_2;
            N_CMP_CLEAR(1);
        }
        if(N_CMP_CT2_LATCH){
            if(N_CMP_CT2_LATCH & CMPSS_STS_HI_LATCHFILTOUT) s4_hardError |= ERR_3;
            if(N_CMP_CT2_LATCH & CMPSS_STS_LO_LATCHFILTOUT) s4_hardError |= ERR_4;
            N_CMP_CLEAR(2);
        }
        if(N_CMP_CT3_LATCH){
            if(N_CMP_CT3_LATCH & CMPSS_STS_HI_LATCHFILTOUT) s4_hardError |= ERR_5;
            if(N_CMP_CT3_LATCH & CMPSS_STS_LO_LATCHFILTOUT) s4_hardError |= ERR_6;
            N_CMP_CLEAR(3);
        }
        if(N_CMP_CT4_LATCH){
            if(N_CMP_CT4_LATCH & CMPSS_STS_HI_LATCHFILTOUT) s4_hardError |= ERR_7;
            if(N_CMP_CT4_LATCH & CMPSS_STS_LO_LATCHFILTOUT) s4_hardError |= ERR_8;
            N_CMP_CLEAR(4);
        }
        if(N_CMP_CT5_LATCH){
            if(N_CMP_CT5_LATCH & CMPSS_STS_HI_LATCHFILTOUT) s4_hardError |= ERR_9;
            if(N_CMP_CT5_LATCH & CMPSS_STS_LO_LATCHFILTOUT) s4_hardError |= ERR_10;
            N_CMP_CLEAR(5);
        }
        if(N_CMP_CT6_LATCH){
            if(N_CMP_CT6_LATCH & CMPSS_STS_HI_LATCHFILTOUT) s4_hardError |= ERR_11;
            if(N_CMP_CT6_LATCH & CMPSS_STS_LO_LATCHFILTOUT) s4_hardError |= ERR_12;
            N_CMP_CLEAR(6);
        }
    }
/*
    //Temp1
    if (f4g_temp1 >= f4_Temperature_1){
        s4g_IndError |= ERR_14;
        s4_TempError |= ERR_1;
    }
    //Temp2
    if (f4g_temp2 >= f4_Temperature_2){
        s4g_IndError |= ERR_14;
        s4_TempError |= ERR_2;
    }
    //Temp3
    if (f4g_temp3 >= f4_Temperature_3){
        s4g_IndError |= ERR_14;
        s4_TempError |= ERR_3;
    }
    //Temp4
    if (f4g_temp4 >= f4_Temperature_4){
        s4g_IndError |= ERR_14;
        s4_TempError |= ERR_4;
    }
    //TempInternal
    if (f4g_tempInternal >= f4_Temperature_i){
        s4g_IndError |= ERR_14;
        s4_TempError |= ERR_5;
    }*/

    if(s4g_IndError == 0){
        s4_hardError = 0;
        s4_TempError = 0;
    }
}

static void pwmErrckCount(f4 f4_adc, f4 f4_Hlevel, f4 f4_Llevel, s4 *s4_cnt, s4 s4_cnt_max, u4 u4_err_code){
    s4 s4_flg_ERROR;

    s4_flg_ERROR = ((f4_adc > f4_Hlevel) || (f4_adc < f4_Llevel));
    if (s4_flg_ERROR) {
        (*s4_cnt)++;
        if ((*s4_cnt) >= s4_cnt_max) {
            s4g_IndError |= u4_err_code;
            *s4_cnt = s4_cnt_max;
        }
    }
    else {
        *s4_cnt = 0;
    }
}

void pwmProtectionInit(){

    s4g_IndError  = 0;
    s4_hardError  = 0;

    f4_H_1 = 45.f;
    f4_L_1 = -45.f;

    f4_H_2 = 200.0f;
    f4_L_2 = -200.0f;

    f4_H_3 = 200.0f;
    f4_L_3 = -200.0f;

    f4_H_4 = 200.0f;
    f4_L_4 = -200.0f;

    f4_H_5 = 200.0f;
    f4_L_5 = -200.0f;

    f4_H_6 = 200.0f;
    f4_L_6 = -200.0f;

    f4_H_7 = 110.f;
    f4_L_7 = -110.0f;

    f4_H_8 = 200.0f;
    f4_L_8 = -200.0f;

    f4_H_9 = 200.0f;
    f4_L_9 = -200.0f;

    f4_H_10 = 200.0f;
    f4_L_10 = -200.0f;

    f4_H_11 = 200.0f;
    f4_L_11 = -200.0f;

    f4_H_12 = 200.0f;
    f4_L_12 = -200.0f;


    s4_cnt_1 = 0;
    s4_cnt_2 = 0;
    s4_cnt_3 = 0;
    s4_cnt_4 = 0;
    s4_cnt_5 = 0;
    s4_cnt_6 = 0;
    s4_cnt_7 = 0;

    s4_cnt_max_1 = 1;
    s4_cnt_max_2 = 1;
    s4_cnt_max_3 = 1;
    s4_cnt_max_4 = 1;
    s4_cnt_max_5 = 1;
    s4_cnt_max_6 = 1;
    s4_cnt_max_7 = 1;
    s4_cnt_max_8 = 1;
    s4_cnt_max_9 = 1;
    s4_cnt_max_10 = 1;
    s4_cnt_max_11 = 1;
    s4_cnt_max_12 = 1;

    f4_Temperature_1 = 80.0f;
    f4_Temperature_2 = 80.0f;
    f4_Temperature_3 = 80.0f;
    f4_Temperature_4 = 80.0f;
    f4_Temperature_i = 80.0f;

    //(CT1)
    N_ConfigCmpss (1 , 0.000001f );              // Hardware protection setup
    N_HardCmpHigh (1, f4g_gainI1,  350.0f );
    N_HardCmpLow  (1, f4g_gainI1, -350.0f );
    N_CMP_CLEAR   (1);

    //(CT2)
    N_ConfigCmpss (2 , 0.000001f );              // Hardware protection setup
    N_HardCmpHigh (2, f4g_gainI2,  200.0f);
    N_HardCmpLow  (2, f4g_gainI2, -200.0f);
    N_CMP_CLEAR   (2);

    //(CT3)
    N_ConfigCmpss (3 , 0.000001f );              // Hardware protection setup
    N_HardCmpHigh (3, f4g_gainI3,  200.0f);
    N_HardCmpLow  (3, f4g_gainI3, -200.0f);
    N_CMP_CLEAR   (3);

    //(CT4)
    N_ConfigCmpss (4 , 0.000001f );              // Hardware protection setup
    N_HardCmpHigh (4, f4g_gainI4, 200.0f);
    N_HardCmpLow  (4, f4g_gainI4,-200.0f);
    N_CMP_CLEAR   (4);

    //(CT5)
    N_ConfigCmpss (5 , 0.000001f );              // Hardware protection setup
    N_HardCmpHigh (5, f4g_gainI5, 200.0f);
    N_HardCmpLow  (5, f4g_gainI5,-200.0f);
    N_CMP_CLEAR   (5);

    //(CT6)
    N_ConfigCmpss (6 , 0.000001f );              // Hardware protection setup
    N_HardCmpHigh (6, f4g_gainI6, 200.0f);
    N_HardCmpLow  (6, f4g_gainI6,-200.0f);
    N_CMP_CLEAR   (6);
}

