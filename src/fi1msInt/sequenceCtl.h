
/*
 * Sequential.h
 *
 *  Created on: 2015/05/14
 *      Author: ohnuma
 */

#ifndef SEQUENTIAL_H_
#define SEQUENTIAL_H_

#include "GlobalParameters.h"

// シーケンシャル番号
#define C0_allOffMode       0
#define C1_waitMode         10
#define C2_runMode          20
#define C4_errorMode        40


extern void sequence(void);		// State pointer A branch
extern void sequenceInit(void);

extern s4	s4g_IndSequen;

#endif /* SEQUENTIAL_H_ */
