/*
 * AD_det.c
 *
 *  Created on: 2018/12/03
 *  K17100_ver_3_0
 *      Author: ohnuma
 */

#define	GLOBAL_Q 27

#include "adDetection.h"

void adDet(void);
void offset_comp(void);
void adDetInit(void);


s4      s4g_flg_offset;
s4      s4g_offsetError;
s4      s4g_state_offset;   /* オフセット調整状況　0で未実施　1以上が回数*/

// Voltage and curent detection
f4      f4g_v1Det,f4g_v2Det,f4g_v3Det,f4g_v4Det,f4g_v5Det,f4g_v6Det;
f4      f4g_i1Det,f4g_i2Det,f4g_i3Det,f4g_i4Det,f4g_i5Det,f4g_i6Det;
f4      f4g_th1Det,f4g_th2Det,f4g_th3Det,f4g_th4Det;
f4		f4g_tempInternal;

// AD detection data
f4      f4_adca0,f4_adca1,f4_adca2,f4_adca3,f4_adca4,f4_adca5,f4_adca6;
f4      f4_adcb0,f4_adcb1,f4_adcb2,f4_adcb3;
f4      f4_adcc0,f4_adcc1,f4_adcc2,f4_adcc3,f4_adcc4,f4_adcc5;
f4      f4_adcd0,f4_adcd1,f4_adcd2,f4_adcd3,f4_adcd4,f4_adcd5;

f4 		f4_offsetV1,f4_gainV1;
f4 		f4_offsetV2,f4_gainV2;
f4 		f4_offsetV3,f4_gainV3;
f4 		f4_offsetV4,f4_gainV4;
f4 		f4_offsetV5,f4_gainV5;
f4 		f4_offsetV6,f4_gainV6;

f4      f4_offsetI1,f4g_gainI1;
f4      f4_offsetI2,f4g_gainI2;
f4      f4_offsetI3,f4g_gainI3;
f4      f4_offsetI4,f4g_gainI4;
f4      f4_offsetI5,f4g_gainI5;
f4      f4_offsetI6,f4g_gainI6;

f4      f4_offsetT1,f4_offsetT2,f4_offsetT3,f4_offsetT4;
f4      f4_gain3_0;

s4		s4_offsetCnt;
s4		s4_offsetCntMax;


void adDet(void){
	f4_adca0   = (f4)(((s4)ADC_readResult(ADCARESULT_BASE,ADC_SOC_NUMBER0)) - 2048);	// CT1(A2) COMP1
	f4_adca1   = (f4)(((s4)ADC_readResult(ADCARESULT_BASE,ADC_SOC_NUMBER1)) - 2048);	// VT1(14)
	f4_adca2   = (f4)(((s4)ADC_readResult(ADCARESULT_BASE,ADC_SOC_NUMBER2)) - 2048);	// CT4(A4) COMP2
	f4_adca3   = (f4)(((s4)ADC_readResult(ADCARESULT_BASE,ADC_SOC_NUMBER3)) - 2048);	// VT4(A5)
	f4_adca4   = (f4)((s4)ADC_readResult(ADCARESULT_BASE,ADC_SOC_NUMBER4));   	     // TH2(A3)
//	f4_adca5   = (f4)GetTemperatureC((s4)ADC_readResult(ADCA_BASE,ADC_SOC_NUMBER5));	 // TEMP(13)
//ADB
	f4_adcb0   = (f4)(((s4)ADC_readResult(ADCBRESULT_BASE,ADC_SOC_NUMBER0)) - 32768);	// VT6
//ADC
	f4_adcc0   = (f4)(((s4)ADC_readResult(ADCCRESULT_BASE,ADC_SOC_NUMBER0)) - 2048);  // CT2(C2) COMP6
	f4_adcc1   = (f4)(((s4)ADC_readResult(ADCCRESULT_BASE,ADC_SOC_NUMBER1)) - 2048);	// VT2(C14)
	f4_adcc2   = (f4)(((s4)ADC_readResult(ADCCRESULT_BASE,ADC_SOC_NUMBER2)) - 2048);	// CT5(C4) COMP5
	f4_adcc3   = (f4)(((s4)ADC_readResult(ADCCRESULT_BASE,ADC_SOC_NUMBER3)));			// TH3(15)
    f4_adcc4   = (f4)(((s4)ADC_readResult(ADCCRESULT_BASE,ADC_SOC_NUMBER4)));			// TH4(C5)
//ADD
	f4_adcd0   = (f4)(((s4)ADC_readResult(ADCDRESULT_BASE,ADC_SOC_NUMBER0)) - 2048);	// CT3(D0) COMP7
	f4_adcd1   = (f4)(((s4)ADC_readResult(ADCDRESULT_BASE,ADC_SOC_NUMBER1)) - 2048);	// VT3(D1)
	f4_adcd2   = (f4)(((s4)ADC_readResult(ADCDRESULT_BASE,ADC_SOC_NUMBER2)) - 2048);	// CT6(D2) COMP8
	f4_adcd3   = (f4)(((s4)ADC_readResult(ADCDRESULT_BASE,ADC_SOC_NUMBER3)) - 2048);	// VT5(D3)
    f4_adcd4   = (f4)(((s4)ADC_readResult(ADCDRESULT_BASE,ADC_SOC_NUMBER4)));			// TH1(D4)

	// offset compensation
	if(s4g_flg_offset == 1){
		offset_comp();
	}
	else {
		s4_offsetCnt = 0;
	}

	// Adjust Gain and offset
	f4g_v1Det = (f4_adca1 + f4_offsetV1 ) * f4_gainV1;			//V1
	f4g_v2Det = (f4_adcc1 + f4_offsetV2 ) * f4_gainV2;			//V2
	f4g_v3Det = (f4_adcd1 + f4_offsetV3 ) * f4_gainV3;			//V3
	f4g_v4Det = (f4_adca3 + f4_offsetV4 ) * f4_gainV4;			//V4
	f4g_v5Det = (f4_adcd3 + f4_offsetV5 ) * f4_gainV5;			//V5
	f4g_v6Det = (f4_adcb0 + f4_offsetV6 ) * f4_gainV6;			//V6

	f4g_i1Det   = (f4_adca0 + f4_offsetI1 ) * f4g_gainI1; 		//I1
	f4g_i2Det   = (f4_adcc0 + f4_offsetI2 ) * f4g_gainI2; 		//I2
	f4g_i3Det   = (f4_adcd0 + f4_offsetI3 ) * f4g_gainI3; 		//I3
    f4g_i4Det   = (f4_adca2 + f4_offsetI4 ) * f4g_gainI4;        //I4
    f4g_i5Det   = (f4_adcc2 + f4_offsetI5 ) * f4g_gainI5;        //I5
    f4g_i6Det   = (f4_adcd2 + f4_offsetI6 ) * f4g_gainI6;        //I6

    f4g_th1Det  = (f4_adcd4 + f4_offsetT1 ) * f4_gain3_0;       //TH1
    f4g_th2Det  = (f4_adca4 + f4_offsetT2 ) * f4_gain3_0;       //TH2
    f4g_th3Det  = (f4_adcc3 + f4_offsetT3 ) * f4_gain3_0;       //TH3
    f4g_th4Det  = (f4_adcc4 + f4_offsetT4 ) * f4_gain3_0;       //TH4
    f4g_tempInternal = f4_adca5;                                //Internal Temperature Sensor


}

/*****************************************************************************/
/*      検出値オフセット補償                                                                                                                               */
/*      オフセット調整（起動後1秒間の平均値）                                                                                                  */
/*****************************************************************************/
void offset_comp(void){
	static f4	f4_offsetSum1,f4_offsetSum2,f4_offsetSum3,f4_offsetSum4,
				f4_offsetSum5,f4_offsetSum6,f4_offsetSum7,f4_offsetSum8,
                f4_offsetSum9,f4_offsetSum10,f4_offsetSum11,f4_offsetSum12;

	if(s4_offsetCnt == 0){
		f4_offsetSum1 = 0;
		f4_offsetSum2 = 0;
		f4_offsetSum3 = 0;
		f4_offsetSum4 = 0;
		f4_offsetSum5 = 0;
		f4_offsetSum6 = 0;
		f4_offsetSum7 = 0;
		f4_offsetSum8 = 0;
        f4_offsetSum9 = 0;
        f4_offsetSum10 = 0;
        f4_offsetSum11 = 0;
        f4_offsetSum12 = 0;

		s4_offsetCnt++;
	}
	else if(s4_offsetCnt <= s4_offsetCntMax) {
		f4_offsetSum1 += f4_adca1;	//V1
		f4_offsetSum2 += f4_adcc1;	//V2
		f4_offsetSum3 += f4_adcd1;  //V3
		f4_offsetSum4 += f4_adca3;	//V4
		f4_offsetSum5 += f4_adcd3;	//V5
        f4_offsetSum6 += f4_adcb0;  //V6

		f4_offsetSum7 += f4_adca0;	//I1
		f4_offsetSum8 += f4_adcc0;	//I2
		f4_offsetSum9 += f4_adcd0;	//I3
        f4_offsetSum10 += f4_adca2;  //I4
        f4_offsetSum11 += f4_adcc2;  //I5
        f4_offsetSum12 += f4_adcd2;  //I6

		s4_offsetCnt++;
	}
	else {
        f4_offsetV1 = -f4_offsetSum1 / s4_offsetCntMax;
        f4_offsetV2 = -f4_offsetSum2 / s4_offsetCntMax;
        f4_offsetV3 = -f4_offsetSum3 / s4_offsetCntMax;
        f4_offsetV4 = -f4_offsetSum4 / s4_offsetCntMax;
        f4_offsetV5 = -f4_offsetSum5 / s4_offsetCntMax;
        f4_offsetV6 = -f4_offsetSum6 / s4_offsetCntMax;

        f4_offsetI1 = -f4_offsetSum7 / s4_offsetCntMax;
        f4_offsetI2 = -f4_offsetSum8 / s4_offsetCntMax;
        f4_offsetI3 = -f4_offsetSum9 / s4_offsetCntMax;
        f4_offsetI4 = -f4_offsetSum10 / s4_offsetCntMax;
        f4_offsetI5 = -f4_offsetSum11 / s4_offsetCntMax;
        f4_offsetI6 = -f4_offsetSum12 / s4_offsetCntMax;

		s4_offsetCnt = 0;
		s4g_flg_offset = 0;		// Automatically this flag is off
		s4g_state_offset++;		// Counter of the offset_comp
	}
}

void adDetInit(void){
	f4_gainV1		=	0.271268f;		  // 555.556/2048
    f4_gainV2       =   0.271268f;         // 555.556/2048
    f4_gainV3       =   0.271268f;         // 555.556/2048
    f4_gainV4       =   0.271268f;         // 555.556/2048
    f4_gainV5       =   0.271268f;         // 555.556/2048
    f4_gainV6       =   0.016954f;		  // 555.556/32768

    f4g_gainI1       =   0.14648f;         // 300A/2048
    f4g_gainI2       =   0.14648f;         // 300A/2048
    f4g_gainI3       =   0.14648f;         // 300A/2048
    f4g_gainI4       =   0.14648f;         // 300A/2048
    f4g_gainI5       =   0.14648f;         // 300A/2048
    f4g_gainI6       =   0.14648f;         // 300A/2048

    f4_gain3_0      =   3.0f/4096.0f;

    f4g_v1Det       = 0.0f;
    f4g_v2Det       = 0.0f;
    f4g_v3Det       = 0.0f;
    f4g_v4Det       = 0.0f;
    f4g_v5Det       = 0.0f;
    f4g_v6Det       = 0.0f;
    f4g_i1Det       = 0.0f;
    f4g_i2Det       = 0.0f;
    f4g_i3Det       = 0.0f;
    f4g_i4Det       = 0.0f;
    f4g_i5Det       = 0.0f;
    f4g_i6Det       = 0.0f;
    f4g_th1Det      = 0.0f;
    f4g_th2Det      = 0.0f;
    f4g_th3Det      = 0.0f;
    f4g_th4Det      = 0.0f;

	f4_offsetV1		=	0.0f;
	f4_offsetV2		=	0.0f;
	f4_offsetV3		=	0.0f;
	f4_offsetV4		=	0.0f;
	f4_offsetV5     =   0.0f;
    f4_offsetV6     =   0.0f;

	f4_offsetI1		=	0.0f;
	f4_offsetI2		=	0.0f;
	f4_offsetI3		=	0.0f;
	f4_offsetI4		=	0.0f;
    f4_offsetI5     =   0.0f;
    f4_offsetI6     =   0.0f;

    f4_offsetT1     =   0.0f;
    f4_offsetT2     =   0.0f;
    f4_offsetT3     =   0.0f;
    f4_offsetT4     =   0.0f;

    s4_offsetCnt    =   0;
    s4g_state_offset=   0;
    s4g_flg_offset  =   0;
    s4g_offsetError =   0;
    s4_offsetCntMax =   INT_FRQ;
}
