/*
 * VRefCmdCal.c
 *
 *  Created on: 2016/11/17
 *      Author: ohnuma
 */
#include "vRefCmdCal.h"
#include <math.h>
#include "adDetection.h"

f4 	f4g_vuRef0,f4g_vvRef0,f4g_vwRef0;

f4 	f4_dutyRef;
f4	f4_outFrq;
f4	f4_outTheta;
f4	f4_outTheta0;
#define zeta 1.f
#define wacr 6000.f
#define Lentz 1.5e-3

float Vdc=0.f;
float Kp; 
float Ti; 
float Ki; 
float iLcmd=0.f;
float Yinv;
float Yinvz;
float Xinv;
float Yinv2;
float Yinvz2;
float Xinv2;
float Xinvz2;
float iL;
float Youtput;



void vRefCmdCal(){
        thetaCal();

		iL=f4g_i1Det;
		Vdc=f4g_v1Det;
        Xinv=iLcmd*sin(f4_outTheta);
		Yinv=(PWM_PER*Xinv+Ti*Yinvz)/(Ti+PWM_PER);
		Yinvz=Yinv;
		Xinvz2=Yinv-iL;
		Yinv2 = (Kp*(PWM_PER+Ti)*Xinv2+Yinvz2*Ti-Kp*Ti*Xinvz2)  / Ti;
        Yinvz2 = Yinv2;
        Xinvz2= Xinv2;
		Youtput=Yinv2/Vdc;
		
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
	Kp=2.f*zeta*wacr*Lentz;
	Ti= 2.f*zeta/wacr;
	Ki= Kp/Ti;
}
