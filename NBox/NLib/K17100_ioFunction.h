//###########################################################################
//
// FILE:   K17100_ioFunction.c
//
// TITLE: Digital input and output function to use k17100 board
//
//###########################################################################
// $TI Release: NPE Library ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/

#ifndef K17100_IOFUNCTION_H_
#define K17100_IOFUNCTION_H_

#include "NLibrary.h"


// Digital output
#define N_DO1_ON()       GPIO_writePin(51,1) // DO1
#define N_DO1_OFF()      GPIO_writePin(51,0) // DO1
#define N_DO1_STATE      GPIO_readPin(51)    // DO1
#define N_DO2_ON()       GPIO_writePin(52,1) // DO2
#define N_DO2_OFF()      GPIO_writePin(52,0) // DO2
#define N_DO2_STATE      GPIO_readPin(52)    // DO2
#define N_DO3_ON()       GPIO_writePin(53,1) // DO3
#define N_DO3_OFF()      GPIO_writePin(53,0) // DO3
#define N_DO3_STATE      GPIO_readPin(53)    // DO3
#define N_DO4_ON()       GPIO_writePin(57,1) // DO4
#define N_DO4_OFF()      GPIO_writePin(57,0) // DO4
#define N_DO4_STATE      GPIO_readPin(57)    // DO4
#define N_DO5_ON()       GPIO_writePin(84,1) // DO5
#define N_DO5_OFF()      GPIO_writePin(84,0) // DO5
#define N_DO5_STATE      GPIO_readPin(84)    // DO5
#define N_DO6_ON()       GPIO_writePin(85,1) // DO6
#define N_DO6_OFF()      GPIO_writePin(85,0) // DO6
#define N_DO6_STATE      GPIO_readPin(85)    // DO6
#define N_DO7_ON()       GPIO_writePin(86,1) // DO7
#define N_DO7_OFF()      GPIO_writePin(86,0) // DO7
#define N_DO7_STATE      GPIO_readPin(86)    // DO7
#define N_DO8_ON()       GPIO_writePin(87,1) // DO8
#define N_DO8_OFF()      GPIO_writePin(87,0) // DO8
#define N_DO8_STATE      GPIO_readPin(87)    // DO8
#define N_DO9_ON()       GPIO_writePin(64,1) // DO9
#define N_DO9_OFF()      GPIO_writePin(64,0) // DO9
#define N_DO9_STATE      GPIO_readPin(64)    // DO9
#define N_DO10_ON()      GPIO_writePin(65,1) // DO10
#define N_DO10_OFF()     GPIO_writePin(65,0) // DO10
#define N_DO10_STATE     GPIO_readPin(65)    // DO10
#define N_DO11_ON()      GPIO_writePin(66,1) // DO11
#define N_DO11_OFF()     GPIO_writePin(66,0) // DO11
#define N_DO11_STATE     GPIO_readPin(66)    // DO11
#define N_DO12_ON()      GPIO_writePin(67,1) // DO12
#define N_DO12_OFF()     GPIO_writePin(67,0) // DO12
#define N_DO12_STATE     GPIO_readPin(67)    // DO12

// Control card LED
#define N_LD2_ON()       GPIO_writePin(31,0)
#define N_LD2_OFF()      GPIO_writePin(31,1)
#define N_LD2_Light()    GPIO_togglePin(31)
#define N_LD2_STATE      GPIO_readPin(31)
#define N_LD3_ON()       GPIO_writePin(34,0)
#define N_LD3_OFF()      GPIO_writePin(34,1)
#define N_LD3_Light()    GPIO_togglePin(34)
#define N_LD3_STATE      GPIO_readPin(34)
// Board LED
#define N_LED1_ON()      GPIO_writePin(74,0)
#define N_LED1_OFF()     GPIO_writePin(74,1)
#define N_LED1_Light()   GPIO_togglePin(74)
#define N_LED1_STATE     GPIO_readPin(74)
#define N_LED2_ON()      GPIO_writePin(75,0)
#define N_LED2_OFF()     GPIO_writePin(75,1)
#define N_LED2_Light()   GPIO_togglePin(75)
#define N_LED2_STATE     GPIO_readPin(75)
#define N_LED3_ON()      GPIO_writePin(76,0)
#define N_LED3_OFF()     GPIO_writePin(76,1)
#define N_LED3_Light()   GPIO_togglePin(76)
#define N_LED3_STATE     GPIO_readPin(76)
#define N_LED4_ON()      GPIO_writePin(77,0)
#define N_LED4_OFF()     GPIO_writePin(77,1)
#define N_LED4_Light()   GPIO_togglePin(77)
#define N_LED4_STATE     GPIO_readPin(77)

// Digital input
#define N_DI1_STATE      GPIO_readPin(42)
#define N_DI2_STATE      GPIO_readPin(43)
#define N_DI3_STATE      GPIO_readPin(48)
#define N_DI4_STATE      GPIO_readPin(49)
#define N_DI5_STATE      GPIO_readPin(50)
#define N_DI6_STATE      GPIO_readPin(54)
#define N_DI7_STATE      GPIO_readPin(55)
#define N_DI8_STATE      GPIO_readPin(56)

// Digital input (option pin)
#define N_OP1_STATE      GPIO_readPin(30)// OP1 after ver.4.0
#define N_OP2_STATE      GPIO_readPin(39)// OP2
#define N_OP3_STATE      GPIO_readPin(40)// OP3
#define N_OP4_STATE      GPIO_readPin(41)// OP4
#define N_OP5_STATE      GPIO_readPin(44)// OP5
#define N_OP6_STATE      GPIO_readPin(45)// OP6
#define N_OP7_STATE      GPIO_readPin(46)// OP7
#define N_OP8_STATE      GPIO_readPin(47)// OP8

#endif /* K17100_IOFUNCTION_H_ */
