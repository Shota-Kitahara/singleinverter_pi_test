/*
 * VRefCmdCal.c
 *
 *  Created on: 2016/11/17
 *      Author: ohnuma
 */
#include "vRefCmdCal.h"
#include <math.h>

f4 	f4g_vuRef0,f4g_vvRef0,f4g_vwRef0;

f4 	f4_dutyRef;
f4	f4_outFrq;
f4	f4_outTheta;
f4	f4_outTheta0;


void vRefCmdCal(){
        thetaCal();
		f4_dutyRef = LIMIT_f4(f4_dutyRef,0.0f,1.0f);    //リミット処理
		f4g_vuRef0 = f4_dutyRef * __sin( f4_outTheta);
		f4g_vvRef0 = f4_dutyRef * __sin((f4_outTheta - 2.0943951f));
		f4g_vwRef0 = f4_dutyRef * __sin((f4_outTheta + 2.0943951f));
}

static void thetaCal(){
	//位相計算
	f4_outTheta = f4_outTheta0 + (INT_PER * PI(2)*f4_outFrq);
	if(f4_outTheta > (f4)(2*3.1415926f)){
		f4_outTheta = f4_outTheta - (f4)(2*3.1415926f);
	}
	f4_outTheta0 = f4_outTheta;
}


void vRefCmdCalInit(){
	f4_dutyRef = 0.99f;
	f4_outFrq = (f4)50.0f;
}
