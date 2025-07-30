/*
 * iock.c
 *
 *  Created on: 2016/10/17
 *      Author: ohnuma
 */

#include "iock.h"

void iock(void);
void iockInit(void);

u2  u2g_sw1,u2g_sw2,u2g_sw3,u2g_sw4;

void iock(void){
	u2g_sw1 = N_DI1_STATE;	            //基板上のSW1 運転開始
	u2g_sw2 = N_DI2_STATE;	            //基板上のSW2
	u2g_sw3 = N_DI3_STATE;	            //基板上のSW3
	u2g_sw4 = N_DI4_STATE^ 0x01;         //基板上のSW4 エラー解除ボタン

}

void iockInit(void){
	u2g_sw1 = 0;
	u2g_sw2 = 0;
	u2g_sw3 = 0;
	u2g_sw4 = 0;

}
