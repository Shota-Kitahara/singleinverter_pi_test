//#############################################################################
//
// FILE:   main.c
//
// TITLE:  K17100_main
//
//
//
// This example is an k17100 base board development.
//
//#############################################################################
// $TI Release: F2837xD Support Library v3.09.00.00 $
// $Release Date: Thu Mar 19 07:35:24 IST 2020 $
// $Copyright:
// Copyright (C) 2013-2020 Texas Instruments Incorporated - http://www.ti.com/
// $TI Release: K17100 Base program ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics co., Ltd.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//

#include "GlobalParameters.h"
#include "NLibrary.h"
#include "F2837xD_Ipc_drivers.h"

#include "configuration.h"
#include "fiPwmInt.h"
#include "fi1msInt.h"

__interrupt void cpu_timer0_isr(void);
__interrupt void adca1_isr(void);

#pragma CODE_SECTION(cpu_timer0_isr, ".TI.ramfunc");
#pragma CODE_SECTION(adca1_isr, ".TI.ramfunc");

#ifdef _PESCOUTER
#include "fiIPCInt.h"
__interrupt void CPU02toCPU01IPC0IntHandler(void);
#pragma CODE_SECTION(CPU02toCPU01IPC0IntHandler, ".TI.ramfunc");
#endif



u4 u4_flg_backGroundCnt;
u4 u4_flg_PWMCnt;
u4 u4_flg_1msCnt;

//
// Main
//
void main(void) {
    Device_init();
#if defined(_FLASH) && defined(_PESCOUTER)
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#endif
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    //stop PWM output
    N_ALL_PWM_OFF();

    //Stop Timer
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Interrupt_register(INT_TIMER0, &cpu_timer0_isr);
    Interrupt_register(INT_ADCA1, &adca1_isr);
#ifdef _PESCOUTER
    Interrupt_register(INT_IPC_0, &CPU02toCPU01IPC0IntHandler);
#endif

    // Configuration
    configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 1000);   // 1msec timer
    configGPIO();
#ifdef _PESCOUTER
    IPC_config();
#endif
    configADC();
    configEPWM();

    // initialization of functions
    fiPwmIntInit();
    fi1msIntInit();
#ifdef _PESCOUTER
    fiIPCIntInit();
#endif

    //Start Timer
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    Interrupt_enable(INT_TIMER0);
    Interrupt_enable(INT_ADCA1);
#ifdef _PESCOUTER
    Interrupt_enable(INT_IPC_0);
    fiIPCSend();
#endif
    EINT;
    ERTM;

    // Background routine
    for (;;) {
        u4_flg_backGroundCnt++;
    }
}

__interrupt void adca1_isr(void) {

    N_LD2_ON();
    fiPwmInt();
#ifdef _PESCOUTER
    fiIPCtimer();
#endif
    u4_flg_PWMCnt++;
    N_LD2_OFF();

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

__interrupt void cpu_timer0_isr(void) {
    // ADC割り込みを受け付けるために?��割り込みを許可
    IER |= M_INT1;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
    EINT;

    //N_LD2_ON();

    fi1msInt();

    u4_flg_1msCnt++;
    //N_LD2_OFF();
}

//
// End of File
//
