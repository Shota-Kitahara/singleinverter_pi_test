//###########################################################################
//
// FILE:  fi1msInt.c
//
// TITLE: 1msec Interrupt
//
//###########################################################################
// $TI Release: K17100 Base program ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/


#include "fi1msInt.h"

#include "iock.h"
#include "sequenceCtl.h"
#include "thermistor.h"



void fi1msInt(){

    iock();
	sequence();
    thermistor();

}

void fi1msIntInit(){

	iockInit();
	sequenceInit();
	thermistorInit();
}

