//###########################################################################
//
// FILE:  fiIPUInt.h
//
// TITLE: interrupt IPC program for PE Scouter
//
//###########################################################################
// $TI Release: K17100 Base program ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/


#ifndef FIIPCINT_H_
#define FIIPCINT_H_

#include "GlobalParameters.h"
#include "F2837xD_Ipc_drivers.h"

#define CPU02TOCPU01_PASSMSG        0x0003FBF4         //

extern void fiIPCInt(void);
extern void fiIPCIntInit(void);

extern void IPC_config(void);
extern void fiIPCSend(void);
extern void fiIPCtimer(void);


#endif /* FIIPCINT_H_ */
