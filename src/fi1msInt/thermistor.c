/*
 * thermistor.c
 *
 *  Created on: 2018/6/11
 *      Author: ohnuma
 */

#include "thermistor.h"
#include "AdDetection.h"
#include <math.h> 

#define R1      (10000.0f)
#define R2      (200.0f)
#define T0      (25.0f + 273.15f)
#define R0      (10000.0f)
#define VP      (3.3f)
#define BVAL    (3435.0f)
#define DVAL    ((1.0f/23.0f/1000.0f))


f4 f4g_temp1,f4g_temp2,f4g_temp3,f4g_temp4;



void thermistor() {
  f4 Rth1, Rth2, Rth3,Rth4;
  f4 f4_th1,f4_th2,f4_th3,f4_th4;

  Rth1 = (f4g_th1Det*(R1+R2)-VP*R2)/(VP-f4g_th1Det);
  Rth2 = (f4g_th2Det*(R1+R2)-VP*R2)/(VP-f4g_th2Det);
  Rth3 = (f4g_th3Det*(R1+R2)-VP*R2)/(VP-f4g_th3Det);
  Rth4 = (f4g_th4Det*(R1+R2)-VP*R2)/(VP-f4g_th4Det);
  
  if(Rth1<1){
      Rth1 = 1;
    }
  if(Rth2<1){
      Rth2 = 1;
    }
  if(Rth3<1){
      Rth3 = 1;
    }
  if(Rth4<1){
      Rth4 = 1;
    }

  f4_th1 = (1.0f/(1.0f/BVAL*logf(Rth1/R0)+1.0f/T0))-273.15f;
  f4_th2 = (1.0f/(1.0f/BVAL*logf(Rth2/R0)+1.0f/T0))-273.15f;
  f4_th3 = (1.0f/(1.0f/BVAL*logf(Rth3/R0)+1.0f/T0))-273.15f;
  f4_th4 = (1.0f/(1.0f/BVAL*logf(Rth4/R0)+1.0f/T0))-273.15f;

  f4g_temp1 = f4_th1 - (VP/(R1+R2+Rth1))*(VP/(R1+R2+Rth1))*Rth1*DVAL;
  f4g_temp2 = f4_th2 - (VP/(R1+R2+Rth2))*(VP/(R1+R2+Rth2))*Rth2*DVAL;
  f4g_temp3 = f4_th3 - (VP/(R1+R2+Rth3))*(VP/(R1+R2+Rth3))*Rth3*DVAL;
  f4g_temp4 = f4_th4 - (VP/(R1+R2+Rth4))*(VP/(R1+R2+Rth4))*Rth4*DVAL;

  f4g_temp1 = LIMIT(f4g_temp1, -255.0f, 255.0f);
  f4g_temp2 = LIMIT(f4g_temp2, -255.0f, 255.0f);
  f4g_temp3 = LIMIT(f4g_temp3, -255.0f, 255.0f);
  f4g_temp4 = LIMIT(f4g_temp4, -255.0f, 255.0f);

}

void thermistorInit() {

}
