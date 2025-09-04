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
float Ti=0.00015625;
float z=1;
float w=12800;
float L=5e-4;
float fsw=20000;
float f=50;
float vdc=100;
float R=37.5;
float Kp=2*z*w*L;
float Ti=2*z/w;
float ki=kp/Ti;
float iLcmd=2.5;
float Yinv;
float Yinvz;
float Xinv;
float Yinv2;
float Yinvz2;
float Xinv2;
float Xinvz2;
float iL;
float Youtput;
float f4g_i1Det;


void vRefCmdCal(){
        thetaCal();
		f4_dutyRef = LIMIT_f4(f4_dutyRef,0.0f,1.0f);    //リミット処理
		// f4g_vuRef0 = f4_dutyRef * __sin( f4_outTheta);
		// f4g_vvRef0 = f4_dutyRef * __sin((f4_outTheta - 2.0943951f));
		// f4g_vwRef0 = f4_dutyRef * __sin((f4_outTheta + 2.0943951f));
		
		iL=f4g_i1Det;
        Xinv=2.5*sin(thetaCal());
		Yinv=(PWM_PER*Xinv+Ti*Yinvz)/(Ti+PWM_PER);
		Yinvz=Yinv;
		Xinvz2=Yinv-iL;
		Yinv2 = (Kp*(PWM_PER+Ti)*Xinv2+Yinvz2*Ti-Kp*Ti*Xinvz2)  / Ti;
        Yinvz2 = Yinv2;
        Xinvz2= Xinv2;
		Youtput=Yinv2/100;
		f4g_vuRef0=Youtput;
		f4g_vvRef0=-Youtput;
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
