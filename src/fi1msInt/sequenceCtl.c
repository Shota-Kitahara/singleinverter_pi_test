/*
 * Sequence control.c
 *
 *  Created on: 2015/05/14
 *      Author: ohnuma
 */

#include "sequenceCtl.h"
#include "pwmProtection.h"
#include "adDetection.h"
#include "iock.h"

s4	s4g_IndSequen;

void sequence(void);		// State pointer A branch

void allOffMode 	(void);
void waitMode 		(void);
void runMode 		(void);
void errorMode   	(void);
void sLedControl 	(void);


// System mode supervisor // 1msec
void sequence(void){
	switch(s4g_IndSequen)
	{
		case C0_allOffMode:
			allOffMode();
		break;

		case C1_waitMode:
			waitMode();
		break;

		case C2_runMode:
			runMode();
		break;

		case C4_errorMode:
			errorMode();
		break;

		default:
		break;
	}
	sLedControl();
}


//	Mode select
void allOffMode(void){
    static s4 wTemp0 = 0;
    N_ALL_PWM_OFF();         //PWM出力停止
    s4g_IndError = 0;       // エラーフラグリセット
    if (wTemp0 >= 500){
		s4g_IndSequen = C1_waitMode;
		wTemp0 =0;
	}
	else{
		wTemp0++;
	}
}

void waitMode(void){
	static s4	s4_wTemp0 = 0;
	if (s4g_IndError != 0){
	    N_ALL_PWM_OFF();
		s4g_IndSequen = C4_errorMode;
		return;
	}
/*    else if (s4g_state_offset == 0){    // オフセット調整
        if(s4g_flg_offset==0){
            s4g_flg_offset = 1;
        }
    }
*/
	else if (u2g_sw1 == 1 && s4_wTemp0 >= 500){
		s4_wTemp0 = 0;
        N_ALL_PWM_ON();
		s4g_IndSequen = C2_runMode;
	}
	else if (u2g_sw1 == 0) {
		s4_wTemp0++;
		if(s4_wTemp0 >= 500){
			s4_wTemp0 = 500;
		}
	}
	else{
		s4_wTemp0 = 0;
	}

}

void runMode(void){
	if (s4g_IndError != 0){
	    N_ALL_PWM_OFF();
		s4g_IndSequen = C4_errorMode;
		return;
	}
	else if (u2g_sw1 == 0){
        N_ALL_PWM_OFF();
		s4g_IndSequen = C1_waitMode;
	}
}


void errorMode(void){
	static s4	s4_wTemp1 = 0;
	if(u2g_sw4 == 1 && s4_wTemp1 >= 500){
		s4_wTemp1 = 0;
		s4g_IndError = 0;
		s4g_IndSequen = C0_allOffMode;

		if (s4g_IndError == 1){
			s4g_IndSequen = C4_errorMode;
			return;
		}
	}
	else if (u2g_sw4 == 0) {
		s4_wTemp1++;
		if(s4_wTemp1 >= 500){
			s4_wTemp1 = 500;
		}
	}
}

void sLedControl(void){
	//Mode LED
	if(s4g_IndSequen == C0_allOffMode){
		N_LED1_ON();
		N_LED2_ON();
		N_LED3_ON();
        N_LED4_OFF();
	}
	else if(s4g_IndSequen == C1_waitMode){
		N_LED2_OFF();
		N_LED3_OFF();
        N_LED4_OFF();
	}

	else if(s4g_IndSequen == C2_runMode){
		N_LED2_ON();
		N_LED3_OFF();
	}

	else{
		N_LED2_OFF();
		N_LED4_ON();
	}
}

void sequenceInit(void){
	// Tasks State-machine init
    s4g_IndSequen = C0_allOffMode;
}


