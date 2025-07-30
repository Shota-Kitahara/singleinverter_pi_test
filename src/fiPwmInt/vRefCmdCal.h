/*
 * VRefCmdCal.h
 *
 *  Created on: 2016/11/17
 *      Author: ohnuma
 */

#ifndef SRC_FI_PWM_INT_VREFCMDCAL_H_
#define SRC_FI_PWM_INT_VREFCMDCAL_H_

#include "GlobalParameters.h"

static void thetaCal(void);

extern void vRefCmdCal(void);
extern void vRefCmdCalInit(void);


extern	f4 	f4g_vuRef0,f4g_vvRef0,f4g_vwRef0;

#endif /* SRC_FI_PWM_INT_VREFCMDCAL_H_ */
