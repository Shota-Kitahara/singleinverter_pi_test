//###########################################################################
//
// FILE:   configuration.h
//
// TITLE: configuration f28379d device
//
//###########################################################################
// $TI Release: K17100 Base program ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "GlobalParameters.h"


extern void configCPUTimer(uint32_t cpuTimer, float freq, float period);
extern void configGPIO(void);
extern void configADC (void);
extern void configEPWM(void);


#endif /* CONFIGURATION_H_ */
